#ifndef GAUSSIANNOISEPROCESSING_H
#define GAUSSIANNOISEPROCESSING_H

#include "opencv2/imgproc/imgproc.hpp"
#include "commonprocessing.h"

class GaussianNoiseProcessing : public CommonProcessing
{
    Q_OBJECT
public:
    GaussianNoiseProcessing(QObject *parent = 0);
    ~GaussianNoiseProcessing();
    virtual void setModuleParameter(const QJsonObject &param);
    virtual void getModuleParameter(QJsonObject &param);
    float getMean() const;
    void setMean(float mean);

    float getSigma() const;
    void setSigma(float sigma);

public slots:
    void intputVideoStream(const cv::Mat& frame);

private:
    float m_mean = 128;
    float m_sigma = 30;
    cv::RNG m_rand;
};

#endif // GAUSSIANNOISEPROCESSING_H
