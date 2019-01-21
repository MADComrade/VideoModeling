#include "commonprocessing.h"
#include "simulationsingleton.h"

#include <QDebug>

CommonProcessing::CommonProcessing(QObject *parent) : QObject(parent)
{

}

CommonProcessing::~CommonProcessing()
{    
}

void CommonProcessing::intputVideoStream(const cv::Mat &frame)
{
    Q_UNUSED(frame)

}

QString CommonProcessing::getBlockProcessingName() const
{
    return m_name;
}

void CommonProcessing::setBlockProcessingName(const QString &name)
{
    m_name = name;
}

int CommonProcessing::getModuleType() const
{
    return m_moduleType;
}

void CommonProcessing::setModuleType(const int &moduleType)
{
    m_moduleType = moduleType;
}

int CommonProcessing::getBlockProcessing() const
{
    return m_blockProcessing;
}

void CommonProcessing::setModuleParameter(const QJsonObject &param)
{
    Q_UNUSED(param)
}

void CommonProcessing::getModuleParameter(QJsonObject &param)
{
    Q_UNUSED(param)
}

void CommonProcessing::setSimulationManager(SimulationSingleton *sim)
{
    m_simulation = sim;    
    startInit();
}

SimulationSingleton *CommonProcessing::getSimulationManager() const
{
    return m_simulation;
}

void CommonProcessing::setBlockProcessing(const int &blockProcessing)
{
    m_blockProcessing = blockProcessing;
}

void CommonProcessing::startInit()
{
    connect(this,SIGNAL(stopSim()),getSimulationManager(),SLOT(SimulationStop()));
    connect(this,SIGNAL(errorSim(QString)),getSimulationManager(),SLOT(SimulationError(QString)));
}
