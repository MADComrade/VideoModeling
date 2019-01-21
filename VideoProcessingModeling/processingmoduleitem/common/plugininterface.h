#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QtPlugin>
#include <QPixmap>
#include <QString>
#include <QMap>
#include "interfaceofmoduleitem.h"
#include "simulationsingleton.h"


class PluginInterface
{
public:
    virtual ~PluginInterface(){}
    virtual InterfaceOfModuleItem* getItemModule(int number, QMenu *contextMenu = 0) = 0; /// фабрика
    virtual QMap<QString,int> getItemsMap() = 0; /// Map с наименованием блока и его id
    virtual QString getPluginName() = 0; /// имя плагина
    virtual QPixmap getModuleImage(int number, bool& ok) = 0; /// картинка блока

    virtual void setSimulationManager(SimulationSingleton* sim){
        m_simulation = sim;
    }

    virtual SimulationSingleton* getSimulationManager() const{
        return m_simulation;
    }

private:
    SimulationSingleton* m_simulation;

};

QT_BEGIN_NAMESPACE

#define PluginInterface_iid "org.qt-project.Qt.PluginInterface"

Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)
QT_END_NAMESPACE


#endif // PLUGININTERFACE_H
