#ifndef GENERATOROFMODULES_H
#define GENERATOROFMODULES_H

#include <QObject>
#include "moduleconfig.h"
#include "interfaceofmoduleitem.h"
//#include <QMenu>

QT_BEGIN_NAMESPACE
class QPixmap;
class QMenu;
class QWidget;
QT_END_NAMESPACE


class GeneratorOfModules : public QObject
{
    Q_OBJECT
public:

    GeneratorOfModules(QObject *parent = 0);
    ~GeneratorOfModules();
    InterfaceOfModuleItem* geterate(int moduleType, CONFUGUATOR::BlockProcessing blockProcessing = CONFUGUATOR::None, QMenu *contextMenu = 0);
    InterfaceOfModuleItem* geterate(int moduleType, QMenu *contextMenu = 0);
    QPixmap imageModule(int moduleType, CONFUGUATOR::BlockProcessing blockProcessing = CONFUGUATOR::None) const;


signals:

public slots:
};

#endif // GENERATOROFMODULES_H
