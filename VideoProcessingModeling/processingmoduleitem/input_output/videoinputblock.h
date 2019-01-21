#ifndef VIDEOINPUTBLOCK_H
#define VIDEOINPUTBLOCK_H

#include "interfaceofmoduleitem.h"
#include <QSharedPointer>

class VideoInputBlock : public InterfaceOfModuleItem
{
    Q_OBJECT
public:
    VideoInputBlock(QGraphicsItemGroup *parent = 0);
    VideoInputBlock(QMenu* menu,QGraphicsItemGroup *parent = 0);
    ~VideoInputBlock();

    virtual OutputVideoItem* getOutputVideoItem();
};

#endif // VIDEOINPUTBLOCK_H
