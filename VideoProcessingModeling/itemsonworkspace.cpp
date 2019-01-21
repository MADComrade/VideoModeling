#include "itemsonworkspace.h"
#include <QJsonArray>

ItemsOnWorkSpace::ItemsOnWorkSpace()
{

}

const QList<ModuleParameter> &ItemsOnWorkSpace::modules() const
{
    return m_moduleList;
}

void ItemsOnWorkSpace::setModulList(const QList<ModuleParameter> &modules)
{
    m_moduleList = modules;
}

void ItemsOnWorkSpace::read(const QJsonObject &json)
{
    m_moduleList.clear();
    QJsonArray modulesArray = json["Processing"].toArray();
    for (int moduleIndex = 0; moduleIndex < modulesArray.size(); ++moduleIndex) {
        QJsonObject moduleObject = modulesArray[moduleIndex].toObject();
        ModuleParameter module;
        module.read(moduleObject);
        m_moduleList.append(module);
    }
}

void ItemsOnWorkSpace::write(QJsonObject &json) const
{
    QJsonArray modulesArray;
    foreach (const ModuleParameter module, m_moduleList) {
        QJsonObject moduleObject;
        module.write(moduleObject);
        modulesArray.append(moduleObject);
    }
    json["Processing"] = modulesArray;
}
