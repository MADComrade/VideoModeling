#ifndef OTHERBLOCKSPLUGIN_H
#define OTHERBLOCKSPLUGIN_H

#include <QObject>
#include "../../VideoProcessingModeling/processingmoduleitem/common/plugininterface.h"
QT_BEGIN_NAMESPACE
class QPixmap;
class QMenu;
class QWidget;
QT_END_NAMESPACE

class OtherBlocksPlugin : public QObject, public PluginInterface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID PluginInterface_iid FILE "otherblocks.json")
#endif // QT_VERSION >= 0x050000
    Q_INTERFACES(PluginInterface)
public:
    OtherBlocksPlugin(QObject *parent = 0);
    ~OtherBlocksPlugin();
    virtual InterfaceOfModuleItem* getItemModule(int number, QMenu *contextMenu = 0) override;
    virtual QMap<QString,int> getItemsMap() override;
    virtual QString getPluginName() override;
    virtual QPixmap getModuleImage(int number, bool& ok) override;
};

#endif // OTHERBLOCKSPLUGIN_H
