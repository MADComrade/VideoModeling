#include "moduleparameter.h"
#include <QJsonArray>

ModuleParameter::ModuleParameter()
    : m_moduleType(ModuleParameter::Processing)
{

}

ModuleParameter::ModuleParameter(const QString& name, ClassType type):
    m_moduleType(type)
{
    m_name = name;
}

QString ModuleParameter::name() const
{
    return m_name;
}

void ModuleParameter::setName(const QString &name)
{
    m_name = name;
}

QPointF ModuleParameter::position() const
{
    return m_position;
}

void ModuleParameter::setPosition(const QPointF &position)
{
    m_position = position;
}

int ModuleParameter::moduleType() const
{
    return m_moduleType;
}

void ModuleParameter::setModuleType(const int &moduleType)
{
    m_moduleType = (ClassType) moduleType;
}

QStringList ModuleParameter::connectDataModule() const
{
    return m_connectDataModule;
}

void ModuleParameter::addConnectDataModule(const QString &connectDataModule)
{
    m_connectDataModule.append(connectDataModule);
}

QStringList ModuleParameter::connectVideoModule() const
{
    return m_connectVideoModule;
}

void ModuleParameter::addConnectVideoModule(const QString &connectVideoModule)
{
    m_connectVideoModule<<connectVideoModule;
}

int ModuleParameter::moduleID() const
{
    return m_moduleID;
}

void ModuleParameter::setModuleID(int moduleID)
{
    m_moduleID = moduleID;
}

QJsonObject ModuleParameter::moduleParameter() const
{
    return m_moduleParameter;
}

void ModuleParameter::setModuleParameter(const QJsonObject &moduleParameter)
{
    m_moduleParameter = moduleParameter;
}

void ModuleParameter::read(const QJsonObject &json)
{
    m_name = json["name"].toString();
    m_moduleID = json["id"].toInt();
    m_position.setX(json["pos_x"].toDouble());
    m_position.setY(json["pos_y"].toDouble());
    m_moduleType = (ClassType)(json["classType"].toInt());
    QJsonArray array = json["connectVideoTo"].toArray();
    for (int i = 0; i < array.size(); ++i) {
        m_connectVideoModule.append(array.at(i).toString());
    }
    array = json["connetDataTo"].toArray();
    for (int i = 0; i < array.size(); ++i) {
        m_connectVideoModule.append(array.at(i).toString());
    }
    m_moduleParameter = json["moduleParam"].toObject();
}

void ModuleParameter::write(QJsonObject &json) const
{
    json["name"] = m_name;
    json["id"] = m_moduleID;
    json["pos_x"] = m_position.x();
    json["pos_y"] = m_position.y();
    json["connectVideoTo"] = QJsonArray::fromStringList(m_connectVideoModule);
    json["connetDataTo"] = QJsonArray::fromStringList(m_connectDataModule);
    json["classType"] = (int)m_moduleType;
    json["moduleParam"] = m_moduleParameter;
}


