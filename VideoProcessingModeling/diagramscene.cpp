/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "diagramscene.h"
#include "arrowblock.h"

#include <QTextCursor>
#include <QGraphicsSceneMouseEvent>
#include <QString>
#include <QDebug>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFileInfo>

#include "moduleconfig.h"
#include "interfaceofmoduleitem.h"
#include "inputdataitem.h"
#include "inputvideoitem.h"
#include "outputdataitem.h"
#include "outputvideoitem.h"

#include "simulationsingleton.h"
#include "singletonthread.h"
#include "processingmoduleitem/common/plugininterface.h"
#include "pluginmanager.h"

DiagramScene::DiagramScene(QMenu *itemMenu, QObject *parent)
    : QGraphicsScene(parent)
{
    myItemMenu = itemMenu;
    myMode = MoveItem;
    myItemType = CONFUGUATOR::ClearBlock;
    line = 0;
    textItem = 0;
    myTextColor = Qt::black;
    myLineColor = Qt::black;
    m_generatorModules = new GeneratorOfModules();
    connect(this, SIGNAL(errorSimulation(QString)),SimulationSingleton::getInstance(),SLOT(SimulationError(QString)));
    connect(SimulationSingleton::getInstance(),&SimulationSingleton::startSimulation,this, [this](){
       if(this->items().isEmpty()){
           emit errorSimulation(tr("Нет модулей на рабочей области!"));
       }
    });
}

DiagramScene::~DiagramScene()
{
    //SingletonThread::drop();
    delete m_generatorModules;
}

void DiagramScene::setLineColor(const QColor &color)
{
    myLineColor = color;
    if (isItemChange(ArrowBlock::Type)) {
        ArrowBlock *item = qgraphicsitem_cast<ArrowBlock *>(selectedItems().first());
        item->setColor(myLineColor);
        update();
    }
}

void DiagramScene::setTextColor(const QColor &color)
{
    myTextColor = color;
    if (isItemChange(DiagramTextItem::Type)) {
        DiagramTextItem *item = qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
        item->setDefaultTextColor(myTextColor);
    }
}

void DiagramScene::setFont(const QFont &font)
{
    myFont = font;

    if (isItemChange(DiagramTextItem::Type)) {
        QGraphicsTextItem *item = qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
        //At this point the selection can change so the first selected item might not be a DiagramTextItem
        if (item)
            item->setFont(myFont);
    }
}

void DiagramScene::deleteItem(const QString &itemName)
{
    m_itemsMap.remove(itemName);
    qDebug()<<"delete";
    qDebug()<<m_itemsMap;
}

void DiagramScene::saveProject(QFile &saveFile)
{
    QFileInfo fileInfo(saveFile.fileName());
    QString filename(fileInfo.fileName());
    qDebug()<<saveFile.fileName()<<filename;

    m_project.setName(filename.split(".").at(0));
    QList<QGraphicsItem *> m_items= this->items();
    InterfaceOfModuleItem* currentModule=0;
    m_modules.clear();
    ItemsOnWorkSpace work;
    QList<ModuleParameter> m_moduleList;
    for(auto it : m_items){
        currentModule = qgraphicsitem_cast<InterfaceOfModuleItem *>(it);
        if(currentModule != 0){
            QJsonObject settings;
            ModuleParameter param(currentModule->objectName());
            param.setPosition(currentModule->pos());
            param.setModuleID(currentModule->moduleType());
            currentModule->getModuleParameter(settings);
            param.setModuleParameter(settings);
            if(!currentModule->getArrows().empty()){
                for(ArrowBlock* arrow : currentModule->getArrows()){
                    if(arrow->endItem()->objectName() != currentModule->objectName()){
                        if(arrow->getTypeConnection() == ArrowBlock::Video){
                            param.addConnectVideoModule(arrow->endItem()->objectName());
                        }else{
                            param.addConnectDataModule(arrow->endItem()->objectName());
                        }
                    }
                }

            }
            m_moduleList.append(param);
        }
    }
    work.setModulList(m_moduleList);
    m_modules.append(work);

    QJsonObject projectObject;
    saveWorkSpace(projectObject);
    QJsonDocument saveDoc(projectObject);
    saveFile.write(saveDoc.toJson());
}

void DiagramScene::openProject(QFile &openFile)
{
    QFileInfo fileInfo(openFile.fileName());
    QString filename(fileInfo.fileName());
    qDebug()<<openFile.fileName()<<filename;

    this->clear();
    this->update();
    m_project.setName(filename.split(".").at(0));
    m_modules.clear();

    QByteArray loadData = openFile.readAll();
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadData));
    readWorkSpace(loadDoc.object());

    m_itemsCount = 0;
    m_itemsMap.clear();
    QMap<QString,QStringList> elemVideoconnect;
    QMap<QString,QStringList> elemDataconnect;
    QMap<QString,InterfaceOfModuleItem*> readModules;
    if(m_modules.empty())
        return;

    InterfaceOfModuleItem* block=0;
    QList<ModuleParameter> m_moduleList = m_modules.at(0).modules();
    for(ModuleParameter param : m_moduleList){
        m_itemsMap[param.name()] = 0;
        elemVideoconnect[param.name()] = param.connectVideoModule();
        elemDataconnect[param.name()] = param.connectDataModule();

        block = m_generatorModules->geterate(param.moduleID(),myItemMenu);
        if(block){
            addItem(block);
        }else{
            QMap<QString, PluginInterface *> pluginsMap = PluginManager::getInstance()->getPluginsMap();
            foreach (QString name, pluginsMap.keys()) {
                block = pluginsMap[name]->getItemModule(param.moduleID(),myItemMenu);
                if(block)
                    break;
            }
            addItem(block);
        }
        readModules[param.name()] = block;
        block->setObjectName(param.name());
        block->setPos(param.position());
        block->setModuleParameter(param.moduleParameter());
    }

    InterfaceOfModuleItem* startBlock=0;
    InterfaceOfModuleItem* finishBlock=0;

    ArrowBlock::TypeConnection conectBlock = ArrowBlock::Video;
    foreach (QString name, readModules.keys()) {
        startBlock = readModules.value(name);
        if(elemVideoconnect.empty())
            break;
        QStringList list = elemVideoconnect.value(name);
        for(QString opLine : list){
            finishBlock = readModules.value(opLine);
            if(startBlock && finishBlock){
                ArrowBlock* arrow = new ArrowBlock(startBlock,finishBlock,conectBlock);
                arrow->setColor(myLineColor);
                arrow->setZValue(-1000.0);
                startBlock->addArrow(arrow);
                finishBlock->addArrow(arrow);
                addItem(arrow);
                arrow->updatePosition();
            }
        }
    }

    conectBlock = ArrowBlock::Data;
    foreach (QString name, readModules.keys()) {
        startBlock = readModules.value(name);
        if(elemDataconnect.empty())
            break;
        QStringList list = elemDataconnect.value(name);
        for(QString opLine : list){
            finishBlock = readModules[opLine];
            if(startBlock && finishBlock){
                ArrowBlock* arrow = new ArrowBlock(startBlock,finishBlock,conectBlock);
                arrow->setColor(myLineColor);
                arrow->setZValue(-1000.0);
                startBlock->addArrow(arrow);
                finishBlock->addArrow(arrow);
                addItem(arrow);
                arrow->updatePosition();
            }
        }
    }
}


void DiagramScene::setMode(Mode mode)
{
    myMode = mode;
}

void DiagramScene::setItemType(int type)
{
    myItemType = type;
}

void DiagramScene::editorLostFocus(DiagramTextItem *item)
{
    QTextCursor cursor = item->textCursor();
    cursor.clearSelection();
    item->setTextCursor(cursor);

    if (item->toPlainText().isEmpty()) {
        removeItem(item);
        item->deleteLater();
    }
}

void DiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button() != Qt::LeftButton)
        return;
    InterfaceOfModuleItem* block=0;
    switch (myMode) {
    case InsertItem:{

        QString my_key ("inst"+QString::number(++m_itemsCount));
        while (m_itemsMap.contains(my_key)) {
            my_key = "inst"+QString::number(++m_itemsCount);
        }
        m_itemsMap[my_key]=m_itemsCount;

        block = m_generatorModules->geterate(myItemType,myItemMenu);
        if(block){
            addItem(block);
        }else{
            QMap<QString, PluginInterface *> pluginsMap = PluginManager::getInstance()->getPluginsMap();
            foreach (QString name, pluginsMap.keys()) {
                block = pluginsMap[name]->getItemModule(myItemType,myItemMenu);
                if(block)
                    break;
            }
            addItem(block);
        }

        block->setObjectName(my_key);
        block->setPos(mouseEvent->scenePos());
        emit itemInserted(block);
        qDebug()<<"Add";
        qDebug()<<m_itemsMap;
    }
        break;

    case InsertLine:
        line = new QGraphicsLineItem(QLineF(mouseEvent->scenePos(),
                                            mouseEvent->scenePos()));
        line->setPen(QPen(myLineColor, 2));
        addItem(line);
        break;
    case InsertText:
        textItem = new DiagramTextItem();
        textItem->setFont(myFont);
        textItem->setTextInteractionFlags(Qt::TextEditorInteraction);
        textItem->setZValue(1000.0);
        connect(textItem, SIGNAL(lostFocus(DiagramTextItem*)),
                this, SLOT(editorLostFocus(DiagramTextItem*)));
        connect(textItem, SIGNAL(selectedChange(QGraphicsItem*)),
                this, SIGNAL(itemSelected(QGraphicsItem*)));
        addItem(textItem);
        textItem->setDefaultTextColor(myTextColor);
        textItem->setPos(mouseEvent->scenePos());
        emit textInserted(textItem);
        //! [8] //! [9]
    default:
        ;
    }
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void DiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (myMode == InsertLine && line != 0) {
        QLineF newLine(line->line().p1(), mouseEvent->scenePos());
        line->setLine(newLine);
    } else if (myMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
}

void DiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (line != 0 && myMode == InsertLine) {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;

        ArrowBlock::TypeConnection conectBlock = ArrowBlock::None;
        if (startItems.count() > 0 && endItems.count() > 0 &&
                startItems.first()->type() == OutputVideoItem::Type &&
                endItems.first()->type() == InputVideoItem::Type &&
                startItems.first() != endItems.first()) {
            conectBlock = ArrowBlock::Video;
        }

        if (startItems.count() > 0 && endItems.count() > 0 &&
                startItems.first()->type() == OutputDataItem::Type &&
                endItems.first()->type() == InputDataItem::Type &&
                startItems.first() != endItems.first()) {
            conectBlock = ArrowBlock::Data;
        }

        if(conectBlock != ArrowBlock::None){
            InterfaceOfModuleItem* startBlock=0;
            InterfaceOfModuleItem* finishBlock=0;

            for(auto a: startItems){
                startBlock = qgraphicsitem_cast<InterfaceOfModuleItem *>(a);
                if(startBlock != 0)
                    break;
            }

            for(auto a: endItems){
                finishBlock = qgraphicsitem_cast<InterfaceOfModuleItem *>(a);
                if(finishBlock != 0)
                    break;
            }

            ArrowBlock* arrow = new ArrowBlock(startBlock,finishBlock,conectBlock);
            arrow->setColor(myLineColor);
            arrow->setZValue(-1000.0);
            startBlock->addArrow(arrow);
            finishBlock->addArrow(arrow);
            addItem(arrow);
            arrow->updatePosition();
        }



        //            QGraphicsEllipseItem *startItemBlock = qgraphicsitem_cast<QGraphicsEllipseItem *>(startItems.first());
        //            QGraphicsEllipseItem *endItemBlock = qgraphicsitem_cast<QGraphicsEllipseItem *>(endItems.first());
        //            DiagramItem *startItem = qgraphicsitem_cast<DiagramItem *>(startItems.first());
        //            DiagramItem *endItem = qgraphicsitem_cast<DiagramItem *>(endItems.first());
        //            Arrow *arrow = new Arrow(startItem, endItem);
        //            arrow->setColor(myLineColor);
        //            //            startItem->addArrow(arrow);
        //            //            endItem->addArrow(arrow);
        //            arrow->setZValue(-1000.0);
        //            addItem(arrow);
        //            arrow->updatePosition();
        //        }
    }
    line = 0;
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

bool DiagramScene::isItemChange(int type)
{
    foreach (QGraphicsItem *item, selectedItems()) {
        if (item->type() == type)
            return true;
    }
    return false;
}

QString DiagramScene::projectName() const
{
    return m_projectName;
}

void DiagramScene::setProjectName(const QString &projectName)
{
    m_projectName = projectName;
}

void DiagramScene::saveWorkSpace(QJsonObject &json) const
{
    QJsonObject projectObject;
    m_project.write(projectObject);
    json["project"] = projectObject;

    QJsonArray modulesArray;
    foreach (const ItemsOnWorkSpace items, m_modules) {
        QJsonObject modulObject;
        items.write(modulObject);
        modulesArray.append(modulObject);
    }
    json["modules"] = modulesArray;
}

void DiagramScene::readWorkSpace(const QJsonObject &json)
{
    m_project.read(json["project"].toObject());

    m_modules.clear();
    QJsonArray modulesArray = json["modules"].toArray();
    for (int moduleIndex = 0; moduleIndex < modulesArray.size(); ++moduleIndex) {
        QJsonObject moduleObject = modulesArray[moduleIndex].toObject();
        ItemsOnWorkSpace myItems;
        myItems.read(moduleObject);
        m_modules.append(myItems);
    }
}

void DiagramScene::closeScene()
{
    this->clear();
    this->update();
}

