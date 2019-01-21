#ifndef VIDEOOUTMANAGER_H
#define VIDEOOUTMANAGER_H

#include <QObject>
#include "commonmanager.h"

class VideoOutWidget;

class VideoOutManager : public CommonManager
{
    Q_OBJECT
public:
    VideoOutManager(QObject *parent = 0);
    ~VideoOutManager();

    void widgetShow();

    virtual void setModuleParameter(const QJsonObject& param);
    virtual void getModuleParameter(QJsonObject& param);
private slots:
    void widgetClose();

private:
    VideoOutWidget* m_videoOutWidget;
};

#endif // VIDEOOUTMANAGER_H
