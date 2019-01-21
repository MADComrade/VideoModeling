#ifndef VIDEOOUTWIDGET_H
#define VIDEOOUTWIDGET_H

#include "commonwidget.h"
#include <opencv2/core/core.hpp>

namespace Ui {
class VideoOutWidget;
}

class VideoOutWidget : public CommonWidget
{
    Q_OBJECT

public:
    explicit VideoOutWidget(QWidget *parent = 0);
    ~VideoOutWidget();

public slots:
    void setVideoFrame(const cv::Mat& frame);

private:
    Ui::VideoOutWidget *ui;
};

#endif // VIDEOOUTWIDGET_H
