#ifndef VIDEOOUTPUTBLOCK_H
#define VIDEOOUTPUTBLOCK_H
#include "interfaceofmoduleitem.h"

#include <QSharedPointer>

class VideoOutputBlock : public InterfaceOfModuleItem
{
    Q_OBJECT
public:
    VideoOutputBlock(QGraphicsItemGroup *parent = 0);
    VideoOutputBlock(QMenu* menu,QGraphicsItemGroup *parent = 0);
    ~VideoOutputBlock();

    virtual InputVideoItem* getInputVideoItem();
};

#endif // VIDEOOUTPUTBLOCK_H
