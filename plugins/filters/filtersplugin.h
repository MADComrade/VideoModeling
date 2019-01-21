#ifndef FILTERSPLUGIN_H
#define FILTERSPLUGIN_H

#include <QObject>
#include "../../VideoProcessingModeling/processingmoduleitem/common/plugininterface.h"
#include "interfaceofmoduleitem.h"
QT_BEGIN_NAMESPACE
class QPixmap;
class QMenu;
class QWidget;
QT_END_NAMESPACE

class FiltersPlugin : public QObject, public PluginInterface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID PluginInterface_iid FILE "filters.json")
#endif // QT_VERSION >= 0x050000
    Q_INTERFACES(PluginInterface)
public:
    FiltersPlugin(QObject *parent = 0);
    ~FiltersPlugin();

    virtual InterfaceOfModuleItem* getItemModule(int number, QMenu *contextMenu = 0) override;
    virtual QMap<QString,int> getItemsMap() override;
    virtual QString getPluginName() override;
    virtual QPixmap getModuleImage(int number, bool& ok) override;
};

#endif // FILTERSPLUGIN_H
