#ifndef SPNOISEPROCESSING_H
#define SPNOISEPROCESSING_H

#include "opencv2/imgproc/imgproc.hpp"
#include "commonprocessing.h"

class SPNoiseProcessing : public CommonProcessing
{
    Q_OBJECT
public:
    SPNoiseProcessing(QObject *parent = 0);
    ~SPNoiseProcessing();
    virtual void setModuleParameter(const QJsonObject &param);
    virtual void getModuleParameter(QJsonObject &param);
    float getBlack() const;
    void setBlack(float black);

    float getWhite() const;
    void setWhite(float white);

public slots:
    void intputVideoStream(const cv::Mat& frame);

private:
    float m_black = 0.02;
    float m_white = 0.08;
    cv::RNG m_rand;
};

#endif // SPNOISEPROCESSING_H
