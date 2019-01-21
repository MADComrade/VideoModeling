#ifndef PLUGINMANAGER_H
#define PLUGINMANAGER_H

#include <QObject>
#include <QMutex>
#include <QMap>
#include <QList>

class PluginInterface;
class PluginManager : public QObject
{
    Q_OBJECT
public:
    static PluginManager* getInstance();
    static void drop();
    void loadPlugins();
    int amountPlugins();
    QMap<QString,PluginInterface*> getPluginsMap();

private:
    PluginManager(QObject *parent = 0): QObject(parent){}
    ~PluginManager();

     PluginManager(PluginManager const&) = delete;
     PluginManager& operator= (PluginManager const&) = delete;


private:
     static QMutex m_mutex;
     static PluginManager* m_instance;
     static int m_amountPlugins;
     QMap<QString,PluginInterface*> m_pluginsList;
};

#endif // PLUGINMANAGER_H
