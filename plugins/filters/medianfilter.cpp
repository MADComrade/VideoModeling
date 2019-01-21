#include "medianfilter.h"
#include <QString>
#include <opencv2/imgproc/imgproc.hpp>
#include "blockenums.h"
#include "moduleconfig.h"

MedianFilter::MedianFilter(QObject *parent)
    : FilterWithKernel(parent)
{
    setBlockProcessingName("Median");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Filtering);
    setModuleType(BLOCKSTYPE::ModuleType::MedianFil);
}

MedianFilter::~MedianFilter(){
    QMutexLocker lock(&m_mutex);
}

void MedianFilter::setModuleParameter(const QJsonObject &param)
{
    m_kernelValue = param["kernelValue"].toInt();
}

void MedianFilter::getModuleParameter(QJsonObject &param)
{
    param["kernelValue"] = m_kernelValue;
}

void MedianFilter::intputVideoStream(const cv::Mat &frame)
{
    QMutexLocker lock(&m_mutex);
    frame.copyTo(m_frame);
    cv::medianBlur(m_frame,m_outFrame,m_kernelValue);
    emit outputVideoStream(m_outFrame);
}
