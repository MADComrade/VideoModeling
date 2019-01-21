#include "bilateralfilter.h"
#include <opencv2/imgproc/imgproc.hpp>
#include "blockenums.h"
#include "moduleconfig.h"
#include <QMutexLocker>

BilateralFilter::BilateralFilter(QObject *parent)
    : FilterWithKernel(parent)
{
    setBlockProcessingName("Bilateral");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Filtering);
    setModuleType(BLOCKSTYPE::ModuleType::BilateralFil);
}

BilateralFilter::~BilateralFilter(){
    QMutexLocker lock(&m_mutex);
}

void BilateralFilter::setModuleParameter(const QJsonObject &param)
{
    m_kernelValue = param["kernelValue"].toInt();
}

void BilateralFilter::getModuleParameter(QJsonObject &param)
{
   param["kernelValue"] = m_kernelValue;
}

void BilateralFilter::intputVideoStream(const cv::Mat &frame)
{
    QMutexLocker lock(&m_mutex);
    frame.copyTo(m_frame);
    cv::bilateralFilter(m_frame,m_outFrame,m_kernelValue,m_kernelValue*2,m_kernelValue*2);
    emit outputVideoStream(m_outFrame);
}
