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

#ifndef DIAGRAMSCENE_H
#define DIAGRAMSCENE_H

#include "processingmoduleitem/generatorofmodules.h"
#include "diagramtextitem.h"
#include "moduleparameter.h"
#include "itemsonworkspace.h"

#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QMenu;
class QPointF;
class QGraphicsLineItem;
class QFont;
class QGraphicsTextItem;
class QColor;
class QFile;
class QJsonObject;
QT_END_NAMESPACE

/*!
 * \brief Класс сцены бля отрисовки цепочки обработки видео
 * \author Chernyshev S.A.
 * \version 1.3
 */
class DiagramScene : public QGraphicsScene
{
    Q_OBJECT

public:
    /// Возможные действия на сцене
    enum Mode {
        InsertItem, /// вставить новый блок обработки
        InsertLine, /// нарисовать соединяющую линию
        InsertText, /// вставить текстовый блок
        MoveItem  /// переместить выделенный блок
    };

    /*!
     * \brief Конструктор
     * \param itemMenu - указатель на меню работы с блоками
     * \param parent - родитель по умолчанию
     */
    explicit DiagramScene(QMenu *itemMenu, QObject *parent = 0);
    ~DiagramScene();
    /*!
     * \brief Возврашает текущий установленный шрифт
     * \return QFont
     */
    QFont font() const { return myFont; }
    /*!
     * \brief Возвращает текущий цвет текста
     * \return QColor
     */
    QColor textColor() const { return myTextColor; }
    /*!
     * \brief Возвращает текущий соединяющей линии
     * \return QColor
     */
    QColor lineColor() const { return myLineColor; }
    /*!
     * \brief Установка цвета соединяющей линии
     * \param color - цвет линии
     */
    void setLineColor(const QColor &color);
    /*!
     * \brief Установка цвета текста
     * \param color - цвет текста
     */
    void setTextColor(const QColor &color);
    /*!
     * \brief Установка шрифта текста
     * \param font - шрифт текста
     */
    void setFont(const QFont &font);

    void deleteItem(const QString& itemName);

    void saveProject(QFile& saveFile);
    void openProject(QFile &openFile);

    QString projectName() const;
    void setProjectName(const QString &projectName);

    void saveWorkSpace(QJsonObject &json) const;
    void readWorkSpace(const QJsonObject &json);

    void closeScene();

public slots:
    /*!
     * \brief Установка режима действий на сцене
     * \param mode - см. enum Mode
     */
    void setMode(Mode mode);
    /*!
     * \brief Установка типа блока для помещения на сцену
     * \param type - тип помещаемого на сцену блока.
     */
    void setItemType(int type);
    /*!
     * \brief Редактирование текстового блока
     * \param item - веделенный текстовый блок
     */
    void editorLostFocus(DiagramTextItem *item);

signals:
    void itemInserted(InterfaceOfModuleItem *item); /// Сигнал об успешной установки блока на сцену
    void textInserted(QGraphicsTextItem *item); /// сигнал от успешной установки текстового блока на сцену
    void itemSelected(QGraphicsItem *item); /// сигнал с указателем на выделяемый на сцене элемент
    void errorSimulation(const QString& error);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) Q_DECL_OVERRIDE;

private:
    bool isItemChange(int type);

    int myItemType;
    QMenu *myItemMenu;
    Mode myMode;
    bool leftButtonDown;
    QPointF startPoint;
    QGraphicsLineItem *line;
    QFont myFont;
    DiagramTextItem *textItem;
    QColor myTextColor;
    QColor myLineColor;
    GeneratorOfModules* m_generatorModules;
    QMap<QString,int> m_itemsMap;
    int m_itemsCount=0;

    QString m_projectName;
    ModuleParameter m_project;
    QList<ItemsOnWorkSpace> m_modules;
};

#endif // DIAGRAMSCENE_H
