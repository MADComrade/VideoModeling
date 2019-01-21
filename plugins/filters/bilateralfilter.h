#ifndef BILATERALFILTER_H
#define BILATERALFILTER_H

#include "filterwithkernel.h"
#include <opencv2/core/core.hpp>

class BilateralFilter : public FilterWithKernel
{
    Q_OBJECT
public:
    BilateralFilter(QObject *parent = 0);
    ~BilateralFilter();

    void setModuleParameter(const QJsonObject &param);
    void getModuleParameter(QJsonObject &param);
public slots:
    void intputVideoStream(const cv::Mat& frame);

};

#endif // BILATERALFILTER_H
