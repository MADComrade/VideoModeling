#include "outputdataitem.h"
#include <QBrush>

OutputDataItem::OutputDataItem(qreal x, qreal y, qreal w, qreal h)
    :QGraphicsEllipseItem(x,y,w,h)
{
     this->setBrush(* new QBrush(Qt::black));
}

OutputDataItem::OutputDataItem(const QRectF &rect)
    :QGraphicsEllipseItem(rect)
{
     this->setBrush(* new QBrush(Qt::black));
}

OutputDataItem::~OutputDataItem()
{

}
