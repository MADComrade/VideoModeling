#ifndef DELAYPROCESSING_H
#define DELAYPROCESSING_H
#include<deque>
#include "opencv2/imgproc/imgproc.hpp"
#include "commonprocessing.h"
#include <QTimer>

class DelayProcessing : public CommonProcessing
{
    Q_OBJECT
    enum class STATE_DELAY{
        Start = 0,
        Stop = 0
    } m_state;
public:
    DelayProcessing(QObject *parent = 0);
    ~DelayProcessing();
    virtual void setModuleParameter(const QJsonObject &param);
    virtual void getModuleParameter(QJsonObject &param);

    int getDelayImageTick() const;

public slots:
    void intputVideoStream(const cv::Mat& frame);
    void setDelayImageTick(int delayImageTick);
private slots:
    void timerTick();

private:
    int m_delay = 500;
    std::deque<cv::Mat> m_temp;
    bool isDelayed = false;
    QTimer* m_timeDelay;
};

#endif // DELAYPROCESSING_H
