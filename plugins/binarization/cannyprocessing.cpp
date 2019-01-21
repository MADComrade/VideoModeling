#include "cannyprocessing.h"
#include <opencv2/imgproc/imgproc.hpp>
#include <QMutexLocker>
#include "blockenums.h"
#include "moduleconfig.h"
#include <QJsonObject>

using namespace cv;
CannyProcessing::CannyProcessing(QObject *parent)
    : CommonProcessing(parent)
{
    setBlockProcessingName("Canny");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Binarization);
    setModuleType(BLOCKSTYPE::ModuleType::Canny);
}

CannyProcessing::~CannyProcessing()
{
    QMutexLocker lock(&m_mutex);
}

int CannyProcessing::minThreshold() const
{
    return m_minThreshold;
}

void CannyProcessing::setMinThreshold(int minThreshold)
{
    m_minThreshold = minThreshold;
}

void CannyProcessing::setModuleParameter(const QJsonObject &param)
{
    m_minThreshold = param["threshold"].toInt();
}

void CannyProcessing::getModuleParameter(QJsonObject &param)
{
    param["threshold"] = m_minThreshold;
}

void CannyProcessing::intputVideoStream(const cv::Mat &frame)
{
    QMutexLocker lock(&m_mutex);
    frame.copyTo(m_frame);
    Canny(m_frame,m_outFrame,m_minThreshold,m_minThreshold*m_ratio,m_kernelSize);
    emit outputVideoStream(m_outFrame);
}
