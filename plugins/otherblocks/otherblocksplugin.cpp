#include "otherblocksplugin.h"
#include <QGraphicsScene>
#include <QPainter>


#include "commontemplateblock.h"
#include "singletonthread.h"
#include "blockenums.h"

#include "affinetransformations.h"
#include "affinewidget.h"
#include "perspectivetransformations.h"
#include "perspectivewidget.h"
#include "scaleprocessing.h"
#include "scalewidget.h"
#include "rotateprocessing.h"
#include "rotatewidget.h"
#include "translateprocessing.h"
#include "translatewidget.h"
#include "roiprocessing.h"
#include "roiwidget.h"
#include "delayprocessing.h"
#include "delaywidget.h"
#include "gaussiannoiseprocessing.h"
#include "gaussiannoisewidget.h"
#include "spnoiseprocessing.h"
#include "spnoisewidget.h"

#include <QDebug>

OtherBlocksPlugin::OtherBlocksPlugin(QObject *parent) :
    QObject(parent)
{
    SingletonThread::getInstance()->start();
}

OtherBlocksPlugin::~OtherBlocksPlugin()
{
    SingletonThread::drop();
}

InterfaceOfModuleItem *OtherBlocksPlugin::getItemModule(int number, QMenu *contextMenu)
{
    InterfaceOfModuleItem* block;
    switch (number) {
    case BLOCKSTYPE::ModuleType::AffineTr:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<AffineTransformations,AffineWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::PerspectiveTr:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<PerspectiveTransformations,PerspectiveWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::Scale:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<ScaleProcessing,ScaleWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::Rotate:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<RotateProcessing,RotateWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::Translate:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<TranslateProcessing,TranslateWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::ROI:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<ROIProcessing,ROIWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::Delay:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<DelayProcessing,DelayWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::GaussianNoise:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<GaussianNoiseProcessing,GaussianNoiseWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::SaltAndPaperNoise:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<SPNoiseProcessing,SPNoiseWidget>(contextMenu));
        break;
    default:
        return 0;
        break;
    }
    block->setSimulationManager(getSimulationManager());
    qDebug()<<"OtherBlocksPlugin"<<getSimulationManager();
    return block;
}

QMap<QString, int> OtherBlocksPlugin::getItemsMap()
{
    QMap<QString, int> bloks;
    bloks["AffineTr"]=BLOCKSTYPE::AffineTr;
    bloks["Pers-veTr"]=BLOCKSTYPE::PerspectiveTr;
    bloks["Scale"]=BLOCKSTYPE::Scale;
    bloks["Rotate"]=BLOCKSTYPE::Rotate;
    bloks["Translate"]=BLOCKSTYPE::Translate;
    bloks["ROI"]=BLOCKSTYPE::ROI;
    bloks["Delay"]=BLOCKSTYPE::Delay;
    bloks["Noise(G)"]=BLOCKSTYPE::GaussianNoise;
    bloks["Noise(S&P)"]=BLOCKSTYPE::SaltAndPaperNoise;

    return bloks;
}

QString OtherBlocksPlugin::getPluginName()
{
    return QString("Other blocks");
}

QPixmap OtherBlocksPlugin::getModuleImage(int number, bool &ok)
{
    ok = false;
    InterfaceOfModuleItem* block;
    QPixmap pixmap(90, 125);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8));

    switch (number) {
    case BLOCKSTYPE::ModuleType::AffineTr:
    case BLOCKSTYPE::ModuleType::PerspectiveTr:

    case BLOCKSTYPE::ModuleType::Scale:
    case BLOCKSTYPE::ModuleType::Rotate:
    case BLOCKSTYPE::ModuleType::Translate:
    case BLOCKSTYPE::ModuleType::GaussianNoise:
    case BLOCKSTYPE::ModuleType::SaltAndPaperNoise:
    case BLOCKSTYPE::ModuleType::Delay:
    case BLOCKSTYPE::ModuleType::ROI:
        block = new InterfaceOfModuleItem();
        break;
    default:
    case BLOCKSTYPE::ModuleType::Povod:
        block = new InterfaceOfModuleItem(Vin_Dout);
        break;
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
Q_EXPORT_PLUGIN2(otherblocks, OtherBlocksPlugin)
#endif // QT_VERSION < 0x050000
