#ifndef GAUSSIANFITER_H
#define GAUSSIANFITER_H

#include "filterwithkernel.h"
#include <opencv2/core/core.hpp>

class GaussianFiter : public FilterWithKernel
{
    Q_OBJECT
public:
    GaussianFiter(QObject *parent = 0);
    ~GaussianFiter();

    virtual void setModuleParameter(const QJsonObject &param);
    virtual void getModuleParameter(QJsonObject &param);
public slots:
    void intputVideoStream(const cv::Mat& frame);
};

#endif // GAUSSIANFITER_H
