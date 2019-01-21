#ifndef BINARIZATIONPLUGIN_H
#define BINARIZATIONPLUGIN_H

#include <QObject>
#include "../../VideoProcessingModeling/processingmoduleitem/common/plugininterface.h"
#include "interfaceofmoduleitem.h"
QT_BEGIN_NAMESPACE
class QPixmap;
class QMenu;
class QWidget;
QT_END_NAMESPACE

class BinarizationPlugin : public QObject, PluginInterface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID PluginInterface_iid FILE "binarization.json")
#endif // QT_VERSION >= 0x050000
    Q_INTERFACES(PluginInterface)

public:
    BinarizationPlugin(QObject *parent = 0);
    ~BinarizationPlugin();
    virtual InterfaceOfModuleItem* getItemModule(int number, QMenu *contextMenu = 0) override;
    virtual QMap<QString,int> getItemsMap() override;
    virtual QString getPluginName() override;
    virtual QPixmap getModuleImage(int number, bool& ok) override;
};

#endif // BINARIZATIONPLUGIN_H
