#include "simulationsingleton.h"
#include <QMutexLocker>
#include <QDebug>

SimulationSingleton*  SimulationSingleton::m_instance = nullptr;
QMutex SimulationSingleton::m_mutex;
//bool SimulationSingleton::m_isRun = false;

SimulationSingleton *SimulationSingleton::getInstance()
{
    QMutexLocker lock(&m_mutex);
    if(!m_instance){
        m_instance = new SimulationSingleton();
    }
    return m_instance;
}

void SimulationSingleton::drop()
{
    QMutexLocker lock(&m_mutex);
    delete m_instance;
    m_instance = nullptr;
}

bool SimulationSingleton::isRun() const
{
    return m_isRun;
}

void SimulationSingleton::simulationRun()
{
    m_isRun = true;
    emit startSimulation();
}

void SimulationSingleton::SimulationStop()
{
    m_isRun = false;
    emit stopSimulation();
}

void SimulationSingleton::SimulationError(const QString &simError)
{
    QMutexLocker lock(&m_mutex);
    m_isRun = false;
    emit error(simError);
}

SimulationSingleton::SimulationSingleton(QObject *parent) : QObject(parent)
{

}
