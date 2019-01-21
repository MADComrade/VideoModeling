#include "pluginmanager.h"
#include <QDir>
#include <QtWidgets>
#include <QDebug>
#include "processingmoduleitem/common/plugininterface.h"
#include "simulationsingleton.h"

PluginManager* PluginManager::m_instance=0;
QMutex PluginManager::m_mutex;
int PluginManager::m_amountPlugins=0;

PluginManager *PluginManager::getInstance()
{
    m_mutex.lock();
    if(!m_instance){
        m_instance = new PluginManager();
    }
    m_mutex.unlock();
    return m_instance;
}

void PluginManager::drop()
{
    m_mutex.lock();
    delete m_instance;
    m_instance = 0;
    m_mutex.unlock();
}

void PluginManager::loadPlugins()
{
    m_amountPlugins = 0;
    if(m_pluginsList.count()>0){
        foreach (QString name, m_pluginsList.keys()) {
            delete m_pluginsList[name];
            m_pluginsList.remove(name);
        }
    }
    QDir pluginsDir(qApp->applicationDirPath());
    foreach (QString fileName, pluginsDir.entryList(QDir::Files)) {
        QPluginLoader pluginLoader(pluginsDir.absoluteFilePath(fileName));
        qDebug()<<fileName;
        QObject *plugin = pluginLoader.instance();
        qDebug()<<plugin;
        if (plugin) {
            PluginInterface* m_interface = qobject_cast<PluginInterface *>(plugin);
            if (m_interface){
                m_interface->setSimulationManager(SimulationSingleton::getInstance());
                m_pluginsList[plugin->metaObject()->className()] = m_interface;
                m_amountPlugins++;
            }
        }
    }
}

int PluginManager::amountPlugins()
{
    return m_amountPlugins;
}

QMap<QString, PluginInterface *> PluginManager::getPluginsMap()
{
    return m_pluginsList;
}

PluginManager::~PluginManager()
{
    for(auto a: m_pluginsList.keys()){
        delete m_pluginsList[a];
        m_pluginsList.remove(a);
    }
}
