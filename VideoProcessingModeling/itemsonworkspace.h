#ifndef ITEMSONWORKSPACE_H
#define ITEMSONWORKSPACE_H

#include <QList>
#include <QJsonObject>

#include "moduleparameter.h"

class ItemsOnWorkSpace
{
public:
     ItemsOnWorkSpace();

     const QList<ModuleParameter> &modules() const;
     void setModulList(const QList<ModuleParameter> &modules);

     void read(const QJsonObject &json);
     void write(QJsonObject &json) const;
 private:
     QList<ModuleParameter> m_moduleList;
};

#endif // ITEMSONWORKSPACE_H
