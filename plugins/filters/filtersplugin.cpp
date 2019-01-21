#include "filtersplugin.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>

#include "commontemplateblock.h"
#include "singletonthread.h"
#include "blockenums.h"

#include "bilateralfilter.h"
#include "gaussianfiter.h"
#include "medianfilter.h"
#include "filterwithkernelwidget.h"
#include "correlationprocessing.h"
#include "correlationwidget.h"
#include "gammaprocessing.h"
#include "gammawidget.h"
#include "histogrammaprocessing.h"
#include "histogrammawidget.h"
#include "logarithmprocessing.h"
#include "logarithmwidget.h"
#include "negativeprocessing.h"
#include "negativewidget.h"
#include "fgaussianprocessing.h"
#include "fgaussianwidget.h"
#include "fidealfilter.h"
#include "fidealfilterwidget.h"
#include "fbutterworthfilter.h"
#include "fbutterworthwidget.h"

FiltersPlugin::FiltersPlugin(QObject *parent) :
    QObject(parent)
{
    SingletonThread::getInstance()->start();
}

FiltersPlugin::~FiltersPlugin()
{
    SingletonThread::drop();
}

InterfaceOfModuleItem *FiltersPlugin::getItemModule(int number, QMenu *contextMenu)
{
    InterfaceOfModuleItem* block;
    switch (number) {
    case BLOCKSTYPE::ModuleType::MedianFil:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<MedianFilter,FilterWithKernelWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::Gaussian:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<GaussianFiter,FilterWithKernelWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::BilateralFil:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<BilateralFilter,FilterWithKernelWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::Correlation:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<CorrelationProcessing,CorrelationWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::Gamma:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<GammaProcessing,GammaWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::Histogramma:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<HistogrammaProcessing,HistogrammaWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::Logarithm:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<LogarithmProcessing,LogarithmWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::Negative:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<NegativeProcessing,NegativeWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::FGaussian:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<FGaussianProcessing,FGaussianWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::FIdeal:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<FIdealFilter,FIdealFilterWidget>(contextMenu));
        break;
    case BLOCKSTYPE::ModuleType::FButterworth:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<FButterworthFilter,FButterworthWidget>(contextMenu));
        break;
    default:
        return 0;
        break;
    }
    block->setSimulationManager(getSimulationManager());
    qDebug()<<"FiltersPlugin"<<getSimulationManager();
    return block;
}

QMap<QString, int> FiltersPlugin::getItemsMap()
{
    QMap<QString, int> bloks;
    bloks["Median"]=BLOCKSTYPE::MedianFil;
    bloks["Gaussian"]=BLOCKSTYPE::Gaussian;
    bloks["FGaussian"] = BLOCKSTYPE::FGaussian;
    bloks["FIdeal"] = BLOCKSTYPE::FIdeal;
    bloks["FButterworth"] = BLOCKSTYPE::FButterworth;
    bloks["Bilateral"]=BLOCKSTYPE::BilateralFil;
    bloks["Gamma"]=BLOCKSTYPE::Gamma;
    bloks["Correlation"] = BLOCKSTYPE::Correlation;
    bloks["Histogramma"] = BLOCKSTYPE::Histogramma;
    bloks["Logarithm"] = BLOCKSTYPE::Logarithm;
    bloks["Negative"] = BLOCKSTYPE::Negative;

    return bloks;
}

QString FiltersPlugin::getPluginName()
{
    return QString("Filter blocks");
}

QPixmap FiltersPlugin::getModuleImage(int number, bool &ok)
{
    ok = false;
    InterfaceOfModuleItem* block;
    QPixmap pixmap(90, 125);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8));

    switch (number) {
    case BLOCKSTYPE::ModuleType::BilateralFil:
    case BLOCKSTYPE::ModuleType::Correlation:
    case BLOCKSTYPE::ModuleType::FButterworth:
    case BLOCKSTYPE::ModuleType::FGaussian:
    case BLOCKSTYPE::ModuleType::FIdeal:
    case BLOCKSTYPE::ModuleType::Gamma:
    case BLOCKSTYPE::ModuleType::Gaussian:
    case BLOCKSTYPE::ModuleType::Histogramma:
    case BLOCKSTYPE::ModuleType::Logarithm:
    case BLOCKSTYPE::ModuleType::MedianFil:
    case BLOCKSTYPE::ModuleType::Negative:
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
Q_EXPORT_PLUGIN2(filters, FiltersPlugin)
#endif // QT_VERSION < 0x050000
