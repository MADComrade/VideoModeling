#include "inputvideoitem.h"
#include <QBrush>
InputVideoItem::InputVideoItem(qreal x, qreal y, qreal w, qreal h)
    :QGraphicsEllipseItem(x,y,w,h)
{
     this->setBrush(* new QBrush(Qt::black));
}

InputVideoItem::InputVideoItem(const QRectF &rect)
    :QGraphicsEllipseItem(rect)
{
     this->setBrush(* new QBrush(Qt::black));
}

InputVideoItem::~InputVideoItem()
{

}
