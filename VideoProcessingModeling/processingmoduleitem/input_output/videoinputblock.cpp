#include "videoinputblock.h"

#include "outputvideoitem.h"
#include "videoIn/videoinmanager.h"
#include <QRectF>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItemGroup>

VideoInputBlock::VideoInputBlock(QGraphicsItemGroup *parent)
    : InterfaceOfModuleItem(oneOutput,parent)
{
    ////////////////////////
    m_blockProcessing = CONFUGUATOR::BlockProcessing::IO;
    m_moduleType = CONFUGUATOR::ModuleType::VideoInput;

    this->removeFromGroup(m_textVin);
    this->removeFromGroup((QGraphicsItem*)m_inEl);
}

VideoInputBlock::VideoInputBlock(QMenu *menu, QGraphicsItemGroup *parent)
    : VideoInputBlock(parent)
{
    m_ContextMenu = menu;
    m_itemText  = new QGraphicsTextItem("Input");
    QRectF xyz = m_item->boundingRect();
    m_itemText->setPos(25,xyz.height()+4);
    this->addToGroup(m_itemText);

    setCommonManager(new VideoInManager());
    //connect(getCommonManager(),SIGNAL(outputVideoStream(cv::Mat)),this,SIGNAL(outputVideoStream(cv::Mat)));
}

VideoInputBlock::~VideoInputBlock()
{
}


OutputVideoItem *VideoInputBlock::getOutputVideoItem()
{
    return m_outEl;
}
