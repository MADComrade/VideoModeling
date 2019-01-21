#ifndef INOUTBLOCKLIST_H
#define INOUTBLOCKLIST_H

#include <QString>
#include <QMap>
#include "moduleconfig.h"

class InOutBlockList
{
public:

     static QMap<QString, int> getBlocks();
     static QString getBlockGroupName();

private:
     InOutBlockList() = delete;
     InOutBlockList(const InOutBlockList&) = delete;
     void operator =(const InOutBlockList&) = delete;
};

#endif // INOUTBLOCKLIST_H
