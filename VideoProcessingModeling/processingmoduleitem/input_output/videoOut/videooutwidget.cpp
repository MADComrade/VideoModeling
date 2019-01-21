#include "videooutwidget.h"
#include "ui_videooutwidget.h"


VideoOutWidget::VideoOutWidget(QWidget *parent) :
    CommonWidget(parent),
    ui(new Ui::VideoOutWidget)
{
    ui->setupUi(this);
    this->setOutputImageLable(ui->outVideoImage);
}

VideoOutWidget::~VideoOutWidget()
{
    this->deleteLater();
    delete ui;
}

void VideoOutWidget::setVideoFrame(const cv::Mat &frame)
{
    CommonWidget::setVideoFrame(frame);
}
