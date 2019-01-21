#include "commonmanager.h"

#include "commonprocessing.h"
#include "commonwidget.h"
#include "simulationsingleton.h"

CommonManager::CommonManager(QObject *parent)
    :QObject(parent),
      m_processingLevel(nullptr),
      m_visualizationLevel(nullptr)
{

}

CommonManager::~CommonManager()
{
    if(m_processingLevel!=nullptr){
        delete m_processingLevel;
    }

    if(m_visualizationLevel!=nullptr){
        delete m_visualizationLevel;
    }
}

void CommonManager::widgetShow()
{
    connect(m_visualizationLevel,SIGNAL(onCloseWidget()),this,SLOT(widgetClose()));
    m_visualizationLevel->show();
    m_show= true;
}

int CommonManager::getModuleType() const
{
    return m_processingLevel->getModuleType();
}

int CommonManager::getBlockProcessing() const
{
    return m_processingLevel->getBlockProcessing();
}

QString CommonManager::getBlockName()
{
    return m_processingLevel->getBlockProcessingName();
}

void CommonManager::setModuleParameter(const QJsonObject &param)
{
    if(m_processingLevel!=nullptr)
        m_processingLevel->setModuleParameter(param);
}

void CommonManager::getModuleParameter(QJsonObject &param)
{
    if(m_processingLevel!=nullptr)
        m_processingLevel->getModuleParameter(param);
}

void CommonManager::setSimulationManager(SimulationSingleton *sim)
{
    processingLevel()->setSimulationManager(sim);
}

void CommonManager::widgetClose()
{
//    if(m_visualizationLevel!=nullptr){
//        disconnect(m_visualizationLevel,SIGNAL(onCloseWidget()),this,SLOT(widgetClose()));
//        delete m_visualizationLevel;
//        m_visualizationLevel = nullptr;
//    }
    m_show = false;
}

void CommonManager::setVisualizationLevel(CommonWidget *visualizationLevel)
{
    if(m_visualizationLevel!=nullptr)
        delete m_visualizationLevel;
    m_visualizationLevel = visualizationLevel;
}

void CommonManager::initConnectionProcLevel()
{
    connect(this,SIGNAL(intputVideoStream(cv::Mat)),m_processingLevel,SLOT(intputVideoStream(cv::Mat)));
    connect(m_processingLevel,SIGNAL(outputVideoStream(cv::Mat)),this,SIGNAL(outputVideoStream(cv::Mat)));
}

bool CommonManager::isWidgetShow() const
{
    return m_show;
}

CommonProcessing *CommonManager::processingLevel() const
{
    return m_processingLevel;
}

void CommonManager::setProcessingLevel(CommonProcessing *processingLevel)
{
    m_processingLevel = processingLevel;
    initConnectionProcLevel();
}
