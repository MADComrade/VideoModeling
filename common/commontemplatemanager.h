#ifndef COMMONTEMPLATEMANAGER_H
#define COMMONTEMPLATEMANAGER_H
#include "commonmanager.h"
#include "commonprocessing.h"
#include "commonwidget.h"
#include "moduleconfig.h"
#include "singletonthread.h"
#include "simulationsingleton.h"
/*!
 * \brief Шаблонный класс менеджера блока обработки
 * \tparam T - класс обработки видео
 * \tparam W - класс виджета настройки обработки видео
 */
template <typename T, typename W>
class CommonTemplateManager : public CommonManager
{    
public:
    CommonTemplateManager(QObject *parent = 0) :CommonManager(parent)
    {
        T* processing = new T();
        if(CONFUGUATOR::BlockProcessing::IO != CONFUGUATOR::BlockProcessing(processing->getBlockProcessing()))
            processing->moveToThread(SingletonThread::getInstance());
        setProcessingLevel(processing);
    }

    ~CommonTemplateManager(){}

    void widgetShow(){
        if(!isWidgetShow()){
            setVisualizationLevel(new W((T*)processingLevel()));
            CommonManager::widgetShow();
        }
    }
};

#endif // COMMONTEMPLATEMANAGER_H
