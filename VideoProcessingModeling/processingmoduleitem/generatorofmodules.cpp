#include "generatorofmodules.h"
#include <QGraphicsScene>
#include <QPainter>

#include "commontemplateblock.h"
#include "input_output/videoIn/imageplayer.h"
#include "input_output/videoIn/imageplayerwidget.h"
#include "input_output/videoIn/paramvideoinput.h"
#include "input_output/videoIn/paramvideoinwidget.h"
#include "input_output/videoinputblock.h"
#include "input_output/videooutputblock.h"
#include "input_output/videoIn/webcamplayer.h"
#include "input_output/videoIn/webcamwidget.h"

#include "simulationsingleton.h"

GeneratorOfModules::GeneratorOfModules(QObject *parent) : QObject(parent)
{

}

GeneratorOfModules::~GeneratorOfModules()
{

}

InterfaceOfModuleItem *GeneratorOfModules::geterate(int moduleType, CONFUGUATOR::BlockProcessing blockProcessing, QMenu *contextMenu)
{
    Q_UNUSED(blockProcessing)

    InterfaceOfModuleItem* block;
    switch (moduleType) {
    case CONFUGUATOR::ModuleType::VideoInput:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new VideoInputBlock(contextMenu));
        break;
    case CONFUGUATOR::ModuleType::VideoOutput:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new VideoOutputBlock(contextMenu));
        break;   
    case CONFUGUATOR::ModuleType::ImageInput:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<ImagePlayer,ImagePlayerWidget>(contextMenu,oneOutput));
        block->setSimulationManager(SimulationSingleton::getInstance());
        break;
    case CONFUGUATOR::ModuleType::VideoParamIn:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<ParamVideoInput,ParamVideoInWidget>(contextMenu,oneOutput));
        block->setSimulationManager(SimulationSingleton::getInstance());
        break;
    case CONFUGUATOR::ModuleType::WebCam:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new CommonTemplateBlock<WebCamPlayer,WebCamWidget>(contextMenu,oneOutput));
        block->setSimulationManager(SimulationSingleton::getInstance());
        break;
    default:
        return 0;
        break;
    }
    return block;
}

InterfaceOfModuleItem *GeneratorOfModules::geterate(int moduleType, QMenu *contextMenu)
{
    return geterate(moduleType,CONFUGUATOR::BlockProcessing::None,contextMenu);
}

QPixmap GeneratorOfModules::imageModule(int moduleType, CONFUGUATOR::BlockProcessing blockProcessing) const
{
    Q_UNUSED(blockProcessing)

    InterfaceOfModuleItem* block;
    QPixmap pixmap(90, 125);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setPen(QPen(Qt::black, 8));

    switch (moduleType) {
    case CONFUGUATOR::ModuleType::VideoInput:
    case CONFUGUATOR::ModuleType::VideoParamIn:
    case CONFUGUATOR::ModuleType::WebCam:
    case CONFUGUATOR::ModuleType::ImageInput:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new VideoInputBlock());
        break;
    case CONFUGUATOR::ModuleType::VideoOutput:
        block = qgraphicsitem_cast<InterfaceOfModuleItem*>(new VideoOutputBlock());
        break;
    default:
        return pixmap;
        break;
    }

    QGraphicsScene st;
    st.addItem(block);
    st.render(&painter);

    return pixmap;
}
