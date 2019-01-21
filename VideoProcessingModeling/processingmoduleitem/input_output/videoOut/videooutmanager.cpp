#include "videooutmanager.h"

#include "videooutwidget.h"

VideoOutManager::VideoOutManager(QObject *parent)
    : CommonManager(parent),
      m_videoOutWidget(0)
{

}

VideoOutManager::~VideoOutManager()
{
    if(m_videoOutWidget!=0){
        delete m_videoOutWidget;
    }
}

void VideoOutManager::widgetShow()
{
    if(!m_show){
        m_videoOutWidget = new VideoOutWidget();
        //m_videoOutWidget->setAttribute(Qt::WA_DeleteOnClose);
        connect(m_videoOutWidget,SIGNAL(onCloseWidget()),this,SLOT(widgetClose()));
        connect(this,SIGNAL(outputVideoStream(cv::Mat)),m_videoOutWidget,SLOT(setVideoFrame(cv::Mat)));
        m_videoOutWidget->show();
        m_show = true;
    }
}

void VideoOutManager::setModuleParameter(const QJsonObject &param)
{
    Q_UNUSED(param)
}

void VideoOutManager::getModuleParameter(QJsonObject &param)
{
    Q_UNUSED(param)
}

void VideoOutManager::widgetClose()
{
    if(m_videoOutWidget!=0){
        disconnect(m_videoOutWidget,SIGNAL(onCloseWidget()),this,SLOT(widgetClose()));
        disconnect(this,SIGNAL(outputVideoStream(cv::Mat)),m_videoOutWidget,SLOT(setVideoFrame(cv::Mat)));
        delete m_videoOutWidget;
        m_videoOutWidget = 0;
    }
    m_show = false;
}
