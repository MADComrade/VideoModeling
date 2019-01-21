#include "binarizationplugin.h"
#include <QGraphicsScene>
#include <QPainter>

#include "commontemplateblock.h"
#include "singletonthread.h"
#include "blockenums.h"

#include "thresholdprocessing.h"
#include "thresholdwidget.h"
#include "adaptivethresholdprocessing.h"
#include "adaptivethresholdwidget.h"
#include "flaplaciandetector.h"
#include "flaplacianwidget.h"
#include "cannyprocessing.h"
#include "cannywidget.h"

#include <QDebug>

BinarizationPlugin::BinarizationPlugin(QObject *parent) :
    QObject(parent)
{
    SingletonThread::getInstance()->start();
}

BinarizationPlugin::~BinarizationPlugin()
{
    SingletonThread::drop();
}

InterfaceOfModuleItem *BinarizationPlugin::getItemModule(int number, QMenu *contextMenu)
{
    InterfaceOfModuleItem* block;
    switch (number) {
    case BLOCKSTYPE::ModuleType::ThresholdBin:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<ThresholdProcessing,ThresholdWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::AThresholdBin:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<AdaptiveThresholdProcessing,AdaptiveThresholdWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::Laplacian:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<FLaplacianDetector,FLaplacianWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::Canny:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<CannyProcessing,CannyWidget>(contextMenu));
        break;
    default:
        return 0;
        break;
    }
    block->setSimulationManager(getSimulationManager());
    qDebug()<<"BinarizationPlugin"<<getSimulationManager();
    return block;
}

QMap<QString, int> BinarizationPlugin::getItemsMap()
{
    QMap<QString, int> bloks;
    bloks["Threshold"]=BLOCKSTYPE::ThresholdBin;
    bloks["AThreshold"]=BLOCKSTYPE::AThresholdBin;
    bloks["Laplacian"]=BLOCKSTYPE::Laplacian;
    bloks["Canny"]=BLOCKSTYPE::Canny;

    return bloks;
}

QString BinarizationPlugin::getPluginName()
{
    return QString("Binarization/edge detector");
}

QPixmap BinarizationPlugin::getModuleImage(int number, bool &ok)
{
    ok = false;
    InterfaceOfModuleItem* block;
    QPixmap pixmap(90, 125);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8));

    switch (number) {
    case BLOCKSTYPE::ModuleType::AThresholdBin:
    case BLOCKSTYPE::ModuleType::Canny:
    case BLOCKSTYPE::ModuleType::Laplacian:
    case BLOCKSTYPE::ModuleType::ThresholdBin:
        block = new InterfaceOfModuleItem();
        break;
    default:
        return pixmap;
        break;
    }

    QGraphicsScene st;
    st.addItem(block);
    st.render(&painter);
    ok = true;
    return pixmap;
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(binarization, BinarizationPlugin)
#endif // QT_VERSION < 0x050000
