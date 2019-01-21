#include "inputdataitem.h"
#include <QBrush>

InputDataItem::InputDataItem(qreal x, qreal y, qreal w, qreal h)
    :QGraphicsEllipseItem(x,y,w,h)
{
    this->setBrush(* new QBrush(Qt::black));
}

InputDataItem::InputDataItem(const QRectF &rect)
    :QGraphicsEllipseItem(rect)
{
     this->setBrush(* new QBrush(Qt::black));
}

InputDataItem::~InputDataItem()
{

}
