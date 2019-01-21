#include "thresholdprocessing.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <QMutexLocker>
#include "blockenums.h"
#include "moduleconfig.h"

ThresholdProcessing::ThresholdProcessing(QObject *parent)
    : CommonProcessing(parent)
{
    m_processingTypesList<<"BINARY"<<"BINARY_INV"<<"TRUNC"<<"TOZERO"<<"TOZERO_INV";
    m_TypesValue<<cv::THRESH_BINARY<<cv::THRESH_BINARY_INV<<cv::THRESH_TRUNC<<cv::THRESH_TOZERO<<cv::THRESH_TOZERO_INV;
    setBlockProcessingName("Threshold");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Binarization);
    setModuleType(BLOCKSTYPE::ModuleType::ThresholdBin);
}

ThresholdProcessing::~ThresholdProcessing()
{
    QMutexLocker lock(&m_mutex);
}

void ThresholdProcessing::intputVideoStream(const cv::Mat &frame)
{
    m_mutex.lock();
    frame.copyTo(m_frame);
    cv::threshold(m_frame,m_outFrame,m_minThreshold,m_maxThreshold,m_TypesValue[m_typeIndex]);
    m_mutex.unlock();
    emit outputVideoStream(m_outFrame);
}

int ThresholdProcessing::typeIndex() const
{
    return m_typeIndex;
}

void ThresholdProcessing::setTypeIndex(int typeIndex)
{
    QMutexLocker lock(&m_mutex);
    m_typeIndex = typeIndex;
}

void ThresholdProcessing::setModuleParameter(const QJsonObject &param)
{
    m_minThreshold = param["minThreshold"].toInt();
    m_maxThreshold = param["maxThreshold"].toInt();
    m_typeIndex = param["typeIndex"].toInt();
}

void ThresholdProcessing::getModuleParameter(QJsonObject &param)
{
    param["minThreshold"] = m_minThreshold;
    param["maxThreshold"] = m_maxThreshold;
    param["typeIndex"] = m_typeIndex;
}

QStringList ThresholdProcessing::processingTypesList() const
{
    return m_processingTypesList;
}

int ThresholdProcessing::minThreshold() const
{
    return m_minThreshold;
}

void ThresholdProcessing::setMinThreshold(int minThreshold)
{
    QMutexLocker lock(&m_mutex);
    m_minThreshold = minThreshold;
}

int ThresholdProcessing::maxThreshold() const
{
    return m_maxThreshold;
}

void ThresholdProcessing::setMaxThreshold(int maxThreshold)
{
    QMutexLocker lock(&m_mutex);
    m_maxThreshold = maxThreshold;
}
