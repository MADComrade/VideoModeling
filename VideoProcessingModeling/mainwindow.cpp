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
#include "diagramtextitem.h"
#include "mainwindow.h"

#include "processingmoduleitem/generatorofmodules.h"
#include "interfaceofmoduleitem.h"
#include "arrowblock.h"

#include "processingmoduleitem/input_output/inoutblocklist.h"

#include <QtWidgets>
#include <QFileDialog>
#include <QDebug>
#include "pluginmanager.h"
#include "processingmoduleitem/common/plugininterface.h"
#include "simulationsingleton.h"

const int InsertTextButton = 99;

//! [0]
MainWindow::MainWindow()
{

    m_simSingleton = SimulationSingleton::getInstance();
    qDebug()<<"MainWindow"<<m_simSingleton;
    connect(m_simSingleton,SIGNAL(error(QString)),this,SLOT(simulationError(QString)));
    PluginManager::getInstance()->loadPlugins();

    createActions();
    createToolBox();
    createMenus();

    scene = new DiagramScene(itemMenu, this);
    scene->setSceneRect(QRectF(0, 0, 5000, 5000));
    connect(scene, SIGNAL(itemInserted(InterfaceOfModuleItem*)),
            this, SLOT(itemInserted(InterfaceOfModuleItem*)));
    connect(scene, SIGNAL(textInserted(QGraphicsTextItem*)),
            this, SLOT(textInserted(QGraphicsTextItem*)));
    connect(scene, SIGNAL(itemSelected(QGraphicsItem*)),
            this, SLOT(itemSelected(QGraphicsItem*)));
    createToolbars();

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(toolBox);
    view = new QGraphicsView(scene);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);

    setCentralWidget(widget);
    setWindowTitle(tr("Video Processing Modeling"));
    setUnifiedTitleAndToolBarOnMac(true);
}

MainWindow::~MainWindow()
{

    PluginManager::drop();
    SimulationSingleton::drop();
}

void MainWindow::buttonGroupClicked(int id)
{
    QList<QAbstractButton *> buttons = buttonGroup->buttons();
    foreach (QAbstractButton *button, buttons) {
        if (buttonGroup->button(id) != button)
            button->setChecked(false);
    }
    if (id == InsertTextButton) {
        scene->setMode(DiagramScene::InsertText);
    } else {
        scene->setItemType(id);
        scene->setMode(DiagramScene::InsertItem);
    }
}

void MainWindow::deleteItem()
{
    foreach (QGraphicsItem *item, scene->selectedItems()) {
        if (item->type() == ArrowBlock::Type) {
            scene->removeItem(item);
            ArrowBlock *arrow = qgraphicsitem_cast<ArrowBlock *>(item);
            arrow->startItem()->removeArrow(arrow);
            arrow->endItem()->removeArrow(arrow);
            delete item;
        }
    }

    foreach (QGraphicsItem *item, scene->selectedItems()) {
        InterfaceOfModuleItem* test = qgraphicsitem_cast<InterfaceOfModuleItem *>(item);
        if (test != 0)
            test->removeArrows();
        scene->removeItem(item);
        scene->deleteItem(test->objectName());
        delete item;
    }
}

void MainWindow::pointerGroupClicked(int)
{
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow::itemInserted(InterfaceOfModuleItem *item)
{
    pointerTypeGroup->button(int(DiagramScene::MoveItem))->setChecked(true);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
    buttonGroup->button(int(item->moduleType()))->setChecked(false);
}

void MainWindow::textInserted(QGraphicsTextItem *)
{
    buttonGroup->button(InsertTextButton)->setChecked(false);
    scene->setMode(DiagramScene::Mode(pointerTypeGroup->checkedId()));
}

void MainWindow::currentFontChanged(const QFont &)
{
    handleFontChange();
}

void MainWindow::fontSizeChanged(const QString &)
{
    handleFontChange();
}

void MainWindow::sceneScaleChanged(const QString &scale)
{
    double newScale = scale.left(scale.indexOf(tr("%"))).toDouble() / 100.0;
    QMatrix oldMatrix = view->matrix();
    view->resetMatrix();
    view->translate(oldMatrix.dx(), oldMatrix.dy());
    view->scale(newScale, newScale);
}

void MainWindow::textColorChanged()
{
    textAction = qobject_cast<QAction *>(sender());
    fontColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/textpointer.png",
                                     qvariant_cast<QColor>(textAction->data())));
    textButtonTriggered();
}

void MainWindow::lineColorChanged()
{
    lineAction = qobject_cast<QAction *>(sender());
    lineColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/linecolor.png",
                                     qvariant_cast<QColor>(lineAction->data())));
    lineButtonTriggered();
}

void MainWindow::textButtonTriggered()
{
    scene->setTextColor(qvariant_cast<QColor>(textAction->data()));
}

void MainWindow::lineButtonTriggered()
{
    scene->setLineColor(qvariant_cast<QColor>(lineAction->data()));
}

void MainWindow::handleFontChange()
{
    QFont font = fontCombo->currentFont();
    font.setPointSize(fontSizeCombo->currentText().toInt());
    font.setWeight(boldAction->isChecked() ? QFont::Bold : QFont::Normal);
    font.setItalic(italicAction->isChecked());
    font.setUnderline(underlineAction->isChecked());

    scene->setFont(font);
}

void MainWindow::itemSelected(QGraphicsItem *item)
{
    DiagramTextItem *textItem =
            qgraphicsitem_cast<DiagramTextItem *>(item);

    QFont font = textItem->font();
    fontCombo->setCurrentFont(font);
    fontSizeCombo->setEditText(QString().setNum(font.pointSize()));
    boldAction->setChecked(font.weight() == QFont::Bold);
    italicAction->setChecked(font.italic());
    underlineAction->setChecked(font.underline());
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("О программе"),
                       tr("Программа предназначена для моделирования этапов обработки видео или фото изображений."));
}

void MainWindow::saveProject()
{
    QString fileName = QFileDialog::getSaveFileName(this,
            tr("Save project"), "",
            tr("Project name (*.vpm);;All Files (*)"));
    if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::WriteOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
            }
            scene->saveProject(file);
    }
}

void MainWindow::openProject()
{
    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open project"), "",
            tr("Project name (*.vpm);;All Files (*)"));
    if (fileName.isEmpty())
            return;
        else {
            QFile file(fileName);
            if (!file.open(QIODevice::ReadOnly)) {
                QMessageBox::information(this, tr("Unable to open file"),
                    file.errorString());
                return;
            }

            scene->openProject(file);
    }
}

void MainWindow::simulationError(const QString &error)
{
    simulationAction->setIcon(QIcon(":/images/start.png"));
    QMessageBox::critical(this,tr("Simulation Error"), error);
}

void MainWindow::startSumulation()
{
    if(!m_simSingleton->isRun()){
        simulationAction->setIcon(QIcon(":/images/stop.png"));
        m_simSingleton->simulationRun();
    }else{
        simulationAction->setIcon(QIcon(":/images/start.png"));
        m_simSingleton->SimulationStop();
    }
}

void MainWindow::createToolBox()
{
    buttonGroup = new QButtonGroup(this);
    buttonGroup->setExclusive(false);
    connect(buttonGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(buttonGroupClicked(int)));
    QGridLayout *layout = new QGridLayout;
    QMap<QString, int> blocks = InOutBlockList::getBlocks();
    configLayout(layout,blocks);

    QToolButton *textButton = new QToolButton;
    textButton->setCheckable(true);
    buttonGroup->addButton(textButton, InsertTextButton);
    textButton->setIcon(QIcon(QPixmap(":/images/textpointer.png")));
    textButton->setIconSize(QSize(50, 50));
    QGridLayout *textLayout = new QGridLayout;
    textLayout->addWidget(textButton, 0, 0, Qt::AlignHCenter);
    textLayout->addWidget(new QLabel(tr("Text")), 1, 0, Qt::AlignCenter);
    QWidget *textWidget = new QWidget;
    textWidget->setLayout(textLayout);
    layout->addWidget(textWidget, 2, 1); /// TODO: вынести блоки входных изображений в отдельный плагин

    layout->setRowStretch(blocks.size()/2+blocks.size()%2+1, 10);
    layout->setColumnStretch(2, 10);

    QWidget *itemInOutWidget = new QWidget;
    itemInOutWidget->setLayout(layout);

    QMap<QString,QWidget*> m_listPluginsWidget;
    if(PluginManager::getInstance()->amountPlugins()>0){
        QMap<QString, PluginInterface *> pluginsMap = PluginManager::getInstance()->getPluginsMap();
        foreach (QString name, pluginsMap.keys()) {
            QGridLayout *pluginLayout = new QGridLayout;
            blocks = pluginsMap[name]->getItemsMap();
            m_currentPlugins = pluginsMap[name];
            configLayout(pluginLayout,blocks,true);
            pluginLayout->setRowStretch(blocks.size()/2+blocks.size()%2, 10);
            pluginLayout->setColumnStretch(2, 10);
            QWidget *pluginWidget = new QWidget;
            pluginWidget->setLayout(pluginLayout);
            m_listPluginsWidget[m_currentPlugins->getPluginName()] = pluginWidget;
        }


    }


    toolBox = new QToolBox;
    toolBox->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Ignored));
    toolBox->setMinimumWidth(itemInOutWidget->sizeHint().width()+10);

    toolBox->addItem(itemInOutWidget, tr(InOutBlockList::getBlockGroupName().toStdString().c_str()));
    foreach (QString name, m_listPluginsWidget.keys()) {
            toolBox->addItem(m_listPluginsWidget[name],tr(name.toStdString().c_str()));
    }
}

void MainWindow::createActions()
{

    deleteAction = new QAction(QIcon(":/images/delete.png"), tr("&Delete"), this);
    deleteAction->setShortcut(tr("Delete"));
    deleteAction->setStatusTip(tr("Delete item from diagram"));
    connect(deleteAction, SIGNAL(triggered()), this, SLOT(deleteItem()));

    saveAction = new QAction(QIcon(":/images/save.png"), tr("&Save"), this);
    saveAction->setShortcut(tr("Save"));
    saveAction->setStatusTip(tr("Save project to file"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveProject()));

    openAction = new QAction(QIcon(":/images/open.png"), tr("&Open"), this);
    openAction->setShortcut(tr("Open"));
    openAction->setStatusTip(tr("Open project from file"));
    connect(openAction, SIGNAL(triggered()), this, SLOT(openProject()));

    simulationAction = new QAction(QIcon(":/images/start.png"), tr("&Simulation"), this);
    simulationAction->setShortcut(tr("Simulation"));
    simulationAction->setStatusTip(tr("Simulation project"));
    connect(simulationAction, SIGNAL(triggered()), this, SLOT(startSumulation()));

    exitAction = new QAction(tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Quit Scenediagram example"));
    connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));

    boldAction = new QAction(tr("Bold"), this);
    boldAction->setCheckable(true);
    QPixmap pixmap(":/images/bold.png");
    boldAction->setIcon(QIcon(pixmap));
    boldAction->setShortcut(tr("Ctrl+B"));
    connect(boldAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    italicAction = new QAction(QIcon(":/images/italic.png"), tr("Italic"), this);
    italicAction->setCheckable(true);
    italicAction->setShortcut(tr("Ctrl+I"));
    connect(italicAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    underlineAction = new QAction(QIcon(":/images/underline.png"), tr("Underline"), this);
    underlineAction->setCheckable(true);
    underlineAction->setShortcut(tr("Ctrl+U"));
    connect(underlineAction, SIGNAL(triggered()), this, SLOT(handleFontChange()));

    aboutAction = new QAction(tr("A&bout"), this);
    aboutAction->setShortcut(tr("F1"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(about()));
}


void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(saveAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(exitAction);

    itemMenu = menuBar()->addMenu(tr("&Item"));

    itemMenu->addAction(deleteAction);
    itemMenu->addSeparator();

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);
}

void MainWindow::createToolbars()
{

    editToolBar = addToolBar(tr("Edit"));
    editToolBar->addAction(saveAction);
    editToolBar->addAction(openAction);
    editToolBar->addAction(deleteAction);


    fontCombo = new QFontComboBox();
    connect(fontCombo, SIGNAL(currentFontChanged(QFont)),
            this, SLOT(currentFontChanged(QFont)));

    fontSizeCombo = new QComboBox;
    fontSizeCombo->setEditable(true);
    for (int i = 8; i < 30; i = i + 2)
        fontSizeCombo->addItem(QString().setNum(i));
    QIntValidator *validator = new QIntValidator(2, 64, this);
    fontSizeCombo->setValidator(validator);
    connect(fontSizeCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(fontSizeChanged(QString)));

    fontColorToolButton = new QToolButton;
    fontColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    fontColorToolButton->setMenu(createColorMenu(SLOT(textColorChanged()), Qt::black));
    textAction = fontColorToolButton->menu()->defaultAction();
    fontColorToolButton->setIcon(createColorToolButtonIcon(":/images/textpointer.png", Qt::black));
    fontColorToolButton->setAutoFillBackground(true);
    connect(fontColorToolButton, SIGNAL(clicked()),
            this, SLOT(textButtonTriggered()));


    lineColorToolButton = new QToolButton;
    lineColorToolButton->setPopupMode(QToolButton::MenuButtonPopup);
    lineColorToolButton->setMenu(createColorMenu(SLOT(lineColorChanged()), Qt::black));
    lineAction = lineColorToolButton->menu()->defaultAction();
    lineColorToolButton->setIcon(createColorToolButtonIcon(
                                     ":/images/linecolor.png", Qt::black));
    connect(lineColorToolButton, SIGNAL(clicked()),
            this, SLOT(lineButtonTriggered()));

    textToolBar = addToolBar(tr("Font"));
    textToolBar->addWidget(fontCombo);
    textToolBar->addWidget(fontSizeCombo);
    textToolBar->addAction(boldAction);
    textToolBar->addAction(italicAction);
    textToolBar->addAction(underlineAction);

    colorToolBar = addToolBar(tr("Color"));
    colorToolBar->addWidget(fontColorToolButton);
    //    colorToolBar->addWidget(fillColorToolButton);
    colorToolBar->addWidget(lineColorToolButton);

    QToolButton *pointerButton = new QToolButton;
    pointerButton->setCheckable(true);
    pointerButton->setChecked(true);
    pointerButton->setIcon(QIcon(":/images/pointer.png"));
    QToolButton *linePointerButton = new QToolButton;
    linePointerButton->setCheckable(true);
    linePointerButton->setIcon(QIcon(":/images/linepointer.png"));

    pointerTypeGroup = new QButtonGroup(this);
    pointerTypeGroup->addButton(pointerButton, int(DiagramScene::MoveItem));
    pointerTypeGroup->addButton(linePointerButton, int(DiagramScene::InsertLine));
    connect(pointerTypeGroup, SIGNAL(buttonClicked(int)),
            this, SLOT(pointerGroupClicked(int)));

    sceneScaleCombo = new QComboBox;
    QStringList scales;
    scales << tr("50%") << tr("75%") << tr("100%") << tr("125%") << tr("150%");
    sceneScaleCombo->addItems(scales);
    sceneScaleCombo->setCurrentIndex(2);
    connect(sceneScaleCombo, SIGNAL(currentIndexChanged(QString)),
            this, SLOT(sceneScaleChanged(QString)));

    pointerToolbar = addToolBar(tr("Pointer type"));
    pointerToolbar->addWidget(pointerButton);
    pointerToolbar->addWidget(linePointerButton);
    pointerToolbar->addWidget(sceneScaleCombo);

    simulationToolbar = addToolBar(tr("Simulation"));
    simulationToolbar->addAction(simulationAction);



}

void MainWindow::configLayout(QGridLayout *layoutBlocks, QMap<QString, int> blocks, bool plugins)
{
    QList<QString> list = blocks.keys();
    int count = blocks.size();
    if(count<=2){
        int index=0;
        for(int i=0;i<count;i++){
            layoutBlocks->addWidget(createCellWidget(list.at(index), blocks[list.at(index)],plugins), 0, i);
            index++;
        }
    }else{
        int index=0;
        int jSize=2;
        int step = count/2 + count%2;
        for(int i=0; i<step;i++){
            if(i+1 == step)
                jSize=(count%2 == 0)?2:count%2;
            for(int j=0; j<jSize;j++){
                layoutBlocks->addWidget(createCellWidget(list.at(index), blocks[list.at(index)],plugins), i, j);
                index++;
            }
        }
    }
}




QWidget *MainWindow::createCellWidget(const QString &text, int type, bool plugins)
{
    if(!plugins){
        GeneratorOfModules genMod;
        QIcon icon(genMod.imageModule(type));

        QToolButton *button = new QToolButton;
        button->setIcon(icon);
        button->setIconSize(QSize(50, 50));
        button->setCheckable(true);
        buttonGroup->addButton(button, int(type));


        QGridLayout *layout = new QGridLayout;
        layout->addWidget(button, 0, 0, Qt::AlignHCenter);
        layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

        QWidget *widget = new QWidget;
        widget->setLayout(layout);

        return widget;
    }
    else{
        bool ok;
        QIcon icon(m_currentPlugins->getModuleImage(type,ok));

        QToolButton *button = new QToolButton;
        button->setIcon(icon);
        button->setIconSize(QSize(50, 50));
        button->setCheckable(true);
        buttonGroup->addButton(button, int(type));


        QGridLayout *layout = new QGridLayout;
        layout->addWidget(button, 0, 0, Qt::AlignHCenter);
        layout->addWidget(new QLabel(text), 1, 0, Qt::AlignCenter);

        QWidget *widget = new QWidget;
        widget->setLayout(layout);

        return widget;
    }
}

QMenu *MainWindow::createColorMenu(const char *slot, QColor defaultColor)
{
    QList<QColor> colors;
    colors << Qt::black  << Qt::red << Qt::blue << Qt::yellow;
    QStringList names;
    names << tr("black") << tr("red") << tr("blue")
          << tr("yellow");

    QMenu *colorMenu = new QMenu(this);
    for (int i = 0; i < colors.count(); ++i) {
        QAction *action = new QAction(names.at(i), this);
        action->setData(colors.at(i));
        action->setIcon(createColorIcon(colors.at(i)));
        connect(action, SIGNAL(triggered()), this, slot);
        colorMenu->addAction(action);
        if (colors.at(i) == defaultColor)
            colorMenu->setDefaultAction(action);
    }
    return colorMenu;
}

QIcon MainWindow::createColorToolButtonIcon(const QString &imageFile, QColor color)
{
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(imageFile);
    // Draw icon centred horizontally on button.
    QRect target(4, 0, 42, 43);
    QRect source(0, 0, 42, 43);
    painter.fillRect(QRect(0, 60, 50, 80), color);
    painter.drawPixmap(target, image, source);

    return QIcon(pixmap);
}

QIcon MainWindow::createColorIcon(QColor color)
{
    QPixmap pixmap(20, 20);
    QPainter painter(&pixmap);
    painter.setPen(Qt::NoPen);
    painter.fillRect(QRect(0, 0, 20, 20), color);

    return QIcon(pixmap);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(SimulationSingleton::getInstance()->isRun()){
        SimulationSingleton::getInstance()->SimulationStop();
        Sleep(3000);
    }
    scene->closeScene();
    emit onCloseMainWindow();
    event->accept();
}

