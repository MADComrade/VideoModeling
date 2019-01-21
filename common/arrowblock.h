#ifndef ARROWBLOCK_H
#define ARROWBLOCK_H

#include <QGraphicsLineItem>
#include <QObject>
#include "interfaceofmoduleitem.h"


QT_BEGIN_NAMESPACE
class QGraphicsPolygonItem;
class QGraphicsLineItem;
class QGraphicsScene;
class QRectF;
class QGraphicsSceneMouseEvent;
class QPainterPath;
QT_END_NAMESPACE
/*!
 * \brief Класс отрисовки линий и настройки соединений между блоками обработки
 */
class ArrowBlock: public QObject, public QGraphicsLineItem
{        
    Q_OBJECT
public:
    enum { Type = UserType + 8 }; /// Тип линии соединения
    /// Тип соединения
    enum TypeConnection{ None, ///нет
                         Video, ///видео
                         Data /// данные
                       };
    /*!
     * \brief Конструктор класса
     * \param startItem - блок, который генерирует видеокадр и от которого будет осуществляться отрисовка линии
     * \param endItem - блок, принимающий видеокадр для его последующей обработки и выдачи результирующего кадра
     * \param type - тип соединения
     * \param parent
     */
    ArrowBlock(InterfaceOfModuleItem* startItem, InterfaceOfModuleItem* endItem, TypeConnection type, QGraphicsItem *parent = 0);
    ~ArrowBlock();
    void disconnectBlocks(); /// удалить соединения между блоками
    int type() const Q_DECL_OVERRIDE { return Type; }
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void setColor(const QColor &color) { myColor = color; } /// установить цвет линии
    InterfaceOfModuleItem* startItem() const { return myStartItem; }
    InterfaceOfModuleItem* endItem() const { return myEndItem; }

    TypeConnection getTypeConnection() const {return m_typeConnection;}

    void updatePosition();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) Q_DECL_OVERRIDE;

private:
    InterfaceOfModuleItem* myStartItem;
    InterfaceOfModuleItem* myEndItem;
    QColor myColor;
    QPolygonF arrowHead;
    TypeConnection m_typeConnection;
};

#endif // ARROWBLOCK_H
