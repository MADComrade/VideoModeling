#include "gaussianfiter.h"
#include <QString>
#include <opencv2/imgproc/imgproc.hpp>
#include "blockenums.h"
#include "moduleconfig.h"

GaussianFiter::GaussianFiter(QObject *parent)
    : FilterWithKernel(parent)
{
    setBlockProcessingName("Gaussian");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Filtering);
    setModuleType(BLOCKSTYPE::ModuleType::Gaussian);
}

GaussianFiter::~GaussianFiter(){
    QMutexLocker lock(&m_mutex);
}

void GaussianFiter::setModuleParameter(const QJsonObject &param)
{
    m_kernelValue = param["kernelValue"].toInt();
}

void GaussianFiter::getModuleParameter(QJsonObject &param)
{
    param["kernelValue"] = m_kernelValue;
}

void GaussianFiter::intputVideoStream(const cv::Mat &frame)
{
    QMutexLocker lock(&m_mutex);
    frame.copyTo(m_frame);
    cv::GaussianBlur(m_frame,m_outFrame,cv::Size(m_kernelValue,m_kernelValue),0,0);
    emit outputVideoStream(m_outFrame);
}
