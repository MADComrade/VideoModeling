#ifndef MEDIANFILTER_H
#define MEDIANFILTER_H

#include "filterwithkernel.h"
#include <opencv2/core/core.hpp>

/*!
 * \brief Класс реализации медианного фильтра
 */
class MedianFilter : public FilterWithKernel
{
    Q_OBJECT
public:
    MedianFilter(QObject *parent = 0);
    ~MedianFilter();

    virtual void setModuleParameter(const QJsonObject &param);
    virtual void getModuleParameter(QJsonObject &param);
public slots:
    void intputVideoStream(const cv::Mat& frame);
};

#endif // MEDIANFILTER_H
