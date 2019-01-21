#ifndef MODULEPARAMETER_H
#define MODULEPARAMETER_H

#include <QJsonObject>
#include <QString>
#include <QStringList>
#include <QPointF>

class ModuleParameter
{    
public:
    enum ClassType {
        Processing=1, Text=2
    };

    ModuleParameter();
    ModuleParameter(const QString& name, ClassType type=ClassType::Processing);

    QString name() const;
    void setName(const QString &name);

    QPointF position() const;
    void setPosition(const QPointF &position);

    int moduleType() const;
    void setModuleType(const int &moduleType);

    QStringList connectDataModule() const;
    void addConnectDataModule(const QString &connectDataModule);

    QStringList connectVideoModule() const;
    void addConnectVideoModule(const QString &connectVideoModule);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    int moduleID() const;
    void setModuleID(int moduleID);

    QJsonObject moduleParameter() const;
    void setModuleParameter(const QJsonObject &moduleParameter);

private:
    QString m_name;
    QPointF m_position;
    QStringList m_connectVideoModule;
    QStringList m_connectDataModule;
    ClassType m_moduleType;
    QJsonObject m_moduleParameter;
    int m_moduleID;
};

#endif // MODULEPARAMETER_H
