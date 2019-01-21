#include "videoinmanager.h"

#include "commonprocessing.h"
#include "commonwidget.h"
#include "videoinwidget.h"
#include "videoimageplayer.h"

VideoInManager::VideoInManager(QObject *parent)
    :CommonManager(parent)
{
    m_videoImagePlayer = new VideoImagePlayer();
    connect(m_videoImagePlayer,SIGNAL(outputVideoStream(cv::Mat)),this,SIGNAL(outputVideoStream(cv::Mat)));
}

VideoInManager::~VideoInManager()
{
    disconnect(m_videoImagePlayer,SIGNAL(outputVideoStream(cv::Mat)),this,SIGNAL(outputVideoStream(cv::Mat)));
    delete m_videoImagePlayer;
}

void VideoInManager::widgetShow()
{
    if(!isWidgetShow()){
        setVisualizationLevel(new VideoInWidget(m_videoImagePlayer));
        CommonManager::widgetShow();
    }
}

void VideoInManager::setModuleParameter(const QJsonObject &param)
{
    Q_UNUSED(param)

}

void VideoInManager::getModuleParameter(QJsonObject &param)
{
    Q_UNUSED(param)
}


