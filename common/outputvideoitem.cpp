#include "outputvideoitem.h"
#include <QBrush>

OutputVideoItem::OutputVideoItem(qreal x, qreal y, qreal w, qreal h)
    :QGraphicsEllipseItem(x,y,w,h)
{
     this->setBrush(* new QBrush(Qt::black));
}

OutputVideoItem::OutputVideoItem(const QRectF &rect)
    :QGraphicsEllipseItem(rect)
{
     this->setBrush(* new QBrush(Qt::black));
}

OutputVideoItem::~OutputVideoItem()
{

}
