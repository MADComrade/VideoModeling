#ifndef COMMONTEMPLATEBLOCK_H
#define COMMONTEMPLATEBLOCK_H
#include <QRectF>
#include <QBrush>
#include <QSharedPointer>

#include "interfaceofmoduleitem.h"
#include "outputvideoitem.h"
#include "inputvideoitem.h"
#include "commontemplatemanager.h"
#include "simulationsingleton.h"


/*!
 * \brief Шаблонный класс блока обработки видео
 * \tparam T - класс обработки видео
 * \tparam W - класс виджета настройки обработки видео
 */
template <typename T, typename W>
class CommonTemplateBlock : public InterfaceOfModuleItem
{

public:


    CommonTemplateBlock(QMenu *menu, Param param=In1Out1, QGraphicsItemGroup *parent=0)
        :InterfaceOfModuleItem(param,parent)
    {
        m_ContextMenu = menu;
        setCommonManager(new CommonTemplateManager<T,W>());
        m_blockProcessing = getCommonManager()->getBlockProcessing();
        m_moduleType = getCommonManager()->getModuleType();
        m_itemText  = new QGraphicsTextItem(getCommonManager()->getBlockName());
        QRectF xyz = m_item->boundingRect();
        m_itemText->setPos(22,xyz.height()+4);
        this->addToGroup(m_itemText);
    }
    ~CommonTemplateBlock(){}


    virtual OutputVideoItem* getOutputVideoItem(){return m_outEl;}
    virtual InputVideoItem* getInputVideoItem() {
        if(m_param == oneOutput)
            return 0;
        else
            return m_inEl;
    }

    virtual InputDataItem* getInputDataItem(){
        return m_dInEl;
    }

    virtual OutputDataItem* getOutputDataItem(){
        return m_dOutEl;
    }


};


#endif // COMMONTEMPLATEBLOCK_H
