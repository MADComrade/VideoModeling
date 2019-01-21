#include "arrowblock.h"

#include <math.h>

#include <QPen>
#include <QPainter>
#include <QDebug>

#include "inputdataitem.h"
#include "inputvideoitem.h"
#include "outputdataitem.h"
#include "outputvideoitem.h"


const qreal Pi = 3.14;

ArrowBlock::ArrowBlock(InterfaceOfModuleItem* startItem,
                       InterfaceOfModuleItem* endItem,
                       TypeConnection type,
                       QGraphicsItem *parent)
    : QObject(),
      QGraphicsLineItem(parent)

{
    myStartItem = startItem;
    myEndItem = endItem;
    m_typeConnection = type;
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    myColor = Qt::black;
    setPen(QPen(myColor, 2, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));

    if(m_typeConnection == Video){
        connect(myStartItem,SIGNAL(outputVideoStream(cv::Mat)),myEndItem,SIGNAL(onInputVideoStream(cv::Mat)));
    }
    else {
        connect(myStartItem,SIGNAL(outputDataStream()),myEndItem,SIGNAL(onInputDataStream()));
    }
}

void ArrowBlock::disconnectBlocks()
{
    if(m_typeConnection == Video){
        disconnect(myStartItem,SIGNAL(outputVideoStream(cv::Mat)),myEndItem,SIGNAL(onInputVideoStream(cv::Mat)));
    }
    else {
        disconnect(myStartItem,SIGNAL(outputDataStream()),myEndItem,SIGNAL(onInputDataStream()));
    }
}

ArrowBlock::~ArrowBlock()
{
}

QRectF ArrowBlock::boundingRect() const
{
    qreal extra = (pen().width() + 20) / 2.0;

    return QRectF(line().p1(), QSizeF(line().p2().x() - line().p1().x(),
                                      line().p2().y() - line().p1().y()))
            .normalized()
            .adjusted(-extra, -extra, extra, extra);
}

QPainterPath ArrowBlock::shape() const
{
    QPainterPath path = QGraphicsLineItem::shape();
    path.addPolygon(arrowHead);
    return path;
}

void ArrowBlock::updatePosition()
{
    QLineF line;
    if(m_typeConnection == TypeConnection::Video){
        line = QLineF(mapFromItem(myStartItem->getOutputVideoItem(),QPointF(0, 0)),
                      mapFromItem(myEndItem->getInputVideoItem(), QPointF(0, 0)));
    }
    else if(m_typeConnection == TypeConnection::Data){
        line = QLineF(mapFromItem(myStartItem->getOutputDataItem(), 0, 0),
                      mapFromItem(myEndItem->getInputDataItem(), 0, 0));
    }
    setLine(line);

}

void ArrowBlock::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if (myStartItem->collidesWithItem(myEndItem))
        return;

    QPen myPen = pen();
    myPen.setColor(myColor);
    qreal arrowSize = 20;
    painter->setPen(myPen);
    painter->setBrush(myColor);

    QPointF p1, p2;
    if(m_typeConnection == TypeConnection::Video){
        p1 = mapFromItem(myStartItem->getOutputVideoItem(),QPointF(5, 5));
        p2 = mapFromItem(myEndItem->getInputVideoItem(), QPointF(5, 5));
    }
    else{
        p1 = mapFromItem(myStartItem->getOutputDataItem(), 5, 5);
        p2 = mapFromItem(myEndItem->getInputDataItem(), 5, 5);
    }

    setLine(QLineF(p2, p1));

    double angle = ::acos(line().dx() / line().length());
    if (line().dy() >= 0)
        angle = (Pi * 2) - angle;

    QPointF arrowP1 = line().p1() + QPointF(sin(angle + Pi / 3) * arrowSize,
                                            cos(angle + Pi / 3) * arrowSize);
    QPointF arrowP2 = line().p1() + QPointF(sin(angle + Pi - Pi / 3) * arrowSize,
                                            cos(angle + Pi - Pi / 3) * arrowSize);

    arrowHead.clear();
    arrowHead << line().p1() << arrowP1 << arrowP2;
    //! [6] //! [7]
    painter->drawLine(line());
    painter->drawPolygon(arrowHead);
    if (isSelected()) {
        painter->setPen(QPen(myColor, 1, Qt::DashLine));
        QLineF myLine = line();
        myLine.translate(0, 4.0);
        painter->drawLine(myLine);
        myLine.translate(0,-8.0);
        painter->drawLine(myLine);
    }

}
