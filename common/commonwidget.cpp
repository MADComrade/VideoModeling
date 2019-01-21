#include "commonwidget.h"

#include <QCloseEvent>
#include <QLabel>
#include <QDebug>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/opencv.hpp>

CommonWidget::CommonWidget(QWidget *parent) : QWidget(parent)
{

}

CommonWidget::~CommonWidget()
{

}

void CommonWidget::setVideoFrame(const cv::Mat &frame)
{
    if(frame.channels()== 3){
        m_outputImage = QImage(frame.data,frame.cols,frame.rows,static_cast<int>(frame.step),QImage::Format_RGB888);
    }
    else{        
            m_outputImage = QImage(frame.data, frame.cols,frame.rows, static_cast<int>(frame.step),QImage::Format_Indexed8);
    }
    if (!m_outputImage.isNull())
    {

       m_outputImageLable->setAlignment(Qt::AlignCenter);
       m_outputImageLable->setPixmap(QPixmap::fromImage(m_outputImage).scaled(m_outputImageLable->size(),
                                                                              Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void CommonWidget::closeEvent(QCloseEvent *event)
{
    emit onCloseWidget();
    event->accept();
}

bool CommonWidget::isInit() const
{
    return m_init;
}

void CommonWidget::setInit(bool init)
{
    m_init = init;
}

void CommonWidget::setOutputImageLable(QLabel *outputImageLable)
{
    m_outputImageLable = outputImageLable;
}

