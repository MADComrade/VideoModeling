#include "videooutputblock.h"

#include "inputvideoitem.h"
#include "videoOut/videooutmanager.h"
#include <QRectF>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>

VideoOutputBlock::VideoOutputBlock(QGraphicsItemGroup *parent)
    : InterfaceOfModuleItem(In1Out1,parent)
{
    /////////////////////////
    m_blockProcessing = CONFUGUATOR::BlockProcessing::IO;
    m_moduleType = CONFUGUATOR::ModuleType::VideoOutput;
    this->removeFromGroup(m_textVout);
    this->removeFromGroup((QGraphicsItem*)m_outEl);
}

VideoOutputBlock::VideoOutputBlock(QMenu *menu, QGraphicsItemGroup *parent)
    : VideoOutputBlock(parent)
{
    m_ContextMenu = menu;
    m_itemText  = new QGraphicsTextItem("Output");
    QRectF xyz = m_item->boundingRect();
    m_itemText->setPos(25,xyz.height()+4);
    this->addToGroup(m_itemText);   

    setCommonManager(new VideoOutManager());
    connect(this,SIGNAL(onInputVideoStream(cv::Mat)),getCommonManager(),SIGNAL(outputVideoStream(cv::Mat)));
}

VideoOutputBlock::~VideoOutputBlock()
{
}


InputVideoItem *VideoOutputBlock::getInputVideoItem()
{
    return m_inEl;
}
