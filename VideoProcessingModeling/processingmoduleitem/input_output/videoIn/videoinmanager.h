#ifndef VIDEOINMANAGER_H
#define VIDEOINMANAGER_H

#include <QObject>
#include <opencv2/core/core.hpp>
#include "commonmanager.h"

class VideoImagePlayer;

/*!
 * \brief Класс отвечающий за управление жц
 * проигрывателя и его виджета настройки
 */
class VideoInManager: public CommonManager
{
    Q_OBJECT
public:
    VideoInManager(QObject *parent=0);
    ~VideoInManager();

    void widgetShow();

    virtual void setModuleParameter(const QJsonObject& param);
    virtual void getModuleParameter(QJsonObject& param);

private:
    VideoImagePlayer* m_videoImagePlayer;
};

#endif // VIDEOINMANAGER_H
