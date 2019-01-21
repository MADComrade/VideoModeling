#include "interfaceofmoduleitem.h"

#include <QGraphicsSceneContextMenuEvent>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsScene>
#include <QMenu>

#include "inputvideoitem.h"
#include "inputdataitem.h"
#include "outputdataitem.h"
#include "outputvideoitem.h"
#include "arrowblock.h"
#include "simulationsingleton.h"


InterfaceOfModuleItem::InterfaceOfModuleItem(Param param, QGraphicsItemGroup *parent)
    : QObject(),
      QGraphicsItemGroup(parent),
      m_param(param)
{
    setFlag(QGraphicsItem::ItemIsMovable, true);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges, true);
    m_dInEl=0;
    m_dOutEl=0;
    m_item = new QGraphicsRectItem(0,0,100,150);

    m_textVin  = new QGraphicsTextItem("Vin");
    m_textVout  = new QGraphicsTextItem("Vout");
    m_inEl = new InputVideoItem(0,0,10,10);
    m_outEl = new OutputVideoItem(0,0,10,10);

    QRectF xyz = m_item->boundingRect();
    m_textVin->setPos(3,xyz.height()/2-10);
    m_inEl->setPos(-4,xyz.height()/2-3);
    m_inEl->setBrush(* new QBrush(Qt::black));

    m_textVout->setPos(xyz.width()-40,xyz.height()/2-10);
    m_outEl->setPos(xyz.width()-4,xyz.height()/2-3);
    m_item->setBrush(* new QBrush(Qt::white));

    //item->setBrush(* new QBrush(Qt::red));
    this->addToGroup(m_item);

    this->addToGroup(m_textVin);
    this->addToGroup(m_textVout);
    this->addToGroup(m_inEl);
    this->addToGroup(m_outEl);

    switch (m_param) {
    case oneOutput:
        this->removeFromGroup(m_textVin);
        this->removeFromGroup((QGraphicsItem*)m_inEl);
        break;
    case Vin_Dout:
        this->removeFromGroup(m_textVout);
        this->removeFromGroup((QGraphicsItem*)m_outEl);
        m_textDout  = new QGraphicsTextItem("Dout");
        m_dOutEl = new OutputDataItem(0,0,10,10);
        m_textDout->setPos(xyz.width()-40,xyz.height()/2-10);
        m_dOutEl->setPos(xyz.width()-4,xyz.height()/2-3);
        this->addToGroup(m_textDout);
        this->addToGroup(m_dOutEl);

        break;
    default:
        break;
    }
}

InterfaceOfModuleItem::~InterfaceOfModuleItem()
{
    this->deleteLater();
    m_manager.reset();
}

void InterfaceOfModuleItem::removeArrow(ArrowBlock *arrow)
{
    int index = arrows.indexOf(arrow);

    if (index != -1){
        arrows.at(index)->disconnectBlocks();
        arrows.removeAt(index);
    }
}

void InterfaceOfModuleItem::removeArrows()
{
    foreach (ArrowBlock *arrow, arrows) {
        arrow->startItem()->removeArrow(arrow);
        arrow->endItem()->removeArrow(arrow);
        scene()->removeItem(arrow);
        delete arrow;
    }
}

void InterfaceOfModuleItem::addArrow(ArrowBlock *arrow)
{
    arrows.append(arrow);
}

void InterfaceOfModuleItem::setModuleParameter(const QJsonObject &param)
{
    m_manager->setModuleParameter(param);
}

void InterfaceOfModuleItem::getModuleParameter(QJsonObject &param)
{
    m_manager->getModuleParameter(param);
}

InputDataItem *InterfaceOfModuleItem::getInputDataItem()
{
    return 0;
}

OutputDataItem *InterfaceOfModuleItem::getOutputDataItem()
{
    return 0;
}

InputVideoItem *InterfaceOfModuleItem::getInputVideoItem()
{
    return 0;
}

OutputVideoItem *InterfaceOfModuleItem::getOutputVideoItem()
{
    return 0;
}

int InterfaceOfModuleItem::moduleType() const
{
    return m_moduleType;
//    switch (m_blockProcessing) {
//    case CONFUGUATOR::BlockProcessing::IO:
//    case CONFUGUATOR::BlockProcessing::None:
//        return m_moduleType;
//        break;
//    case CONFUGUATOR::BlockProcessing::Filtering:
//        return (CONFUGUATOR::ModuleType::MedianFil - m_moduleType);
//        break;
//    case CONFUGUATOR::BlockProcessing::Segmentation:
//        return (CONFUGUATOR::ModuleType::MedianFil - m_moduleType);
//        break;
//    default:
//        return -1;
//        break;
//    }
}

int InterfaceOfModuleItem::blockProcessingType() const
{
    return m_blockProcessing;
}

void InterfaceOfModuleItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    scene()->clearSelection();
    setSelected(true);
    m_ContextMenu->exec(event->screenPos());
}

QVariant InterfaceOfModuleItem::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemPositionChange) {
        foreach (ArrowBlock *arrow, arrows) {
            arrow->updatePosition();
        }
    }

    return value;
}

void InterfaceOfModuleItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    m_manager->widgetShow();
    event->accept();
}

void InterfaceOfModuleItem::setCommonManager(CommonManager *manager)
{
    m_manager = QSharedPointer<CommonManager>(manager);
    connect(this,SIGNAL(onInputVideoStream(cv::Mat)),m_manager.data(),SIGNAL(intputVideoStream(cv::Mat)));
    connect(m_manager.data(),SIGNAL(outputVideoStream(cv::Mat)),this,SIGNAL(outputVideoStream(cv::Mat)));
}

CommonManager *InterfaceOfModuleItem::getCommonManager() const
{
    return m_manager.data();
}

QString InterfaceOfModuleItem::getModuleName() const
{
    return m_moduleName;
}

void InterfaceOfModuleItem::setModuleName(const QString &moduleName)
{
    m_moduleName = moduleName;
}

const QList<ArrowBlock *> &InterfaceOfModuleItem::getArrows() const
{
    return arrows;
}

void InterfaceOfModuleItem::setSimulationManager( SimulationSingleton *sim)
{
    m_manager->setSimulationManager(sim);
}
