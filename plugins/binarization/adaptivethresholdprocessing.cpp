#include "adaptivethresholdprocessing.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <QMutexLocker>
#include "blockenums.h"
#include "moduleconfig.h"

AdaptiveThresholdProcessing::AdaptiveThresholdProcessing(QObject *parent)
    : CommonProcessing(parent)
{
    m_kernelList<<"3"<<"5"<<"7"<<"9";
    m_kernelValueList<<3<<5<<7<<9;

    m_adaptiveTypesList<<"ADAPTIVE_MEAN"<<"ADAPTIVE_GAUSSIAN";
    m_adaptiveTypeValues<<cv::ADAPTIVE_THRESH_MEAN_C<<cv::ADAPTIVE_THRESH_GAUSSIAN_C;

    m_thresholTypesList<<"THRESH_BINARY"<<"THRESH_BINARY_INV";
    m_thresholTypeValues<<cv::THRESH_BINARY<<cv::THRESH_BINARY_INV;

    setBlockProcessingName("AThreshold");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Binarization);
    setModuleType(BLOCKSTYPE::ModuleType::AThresholdBin);
}

AdaptiveThresholdProcessing::~AdaptiveThresholdProcessing()
{
    QMutexLocker lock(&m_mutex);
}

int AdaptiveThresholdProcessing::maxThreshold() const
{
    return m_maxThreshold;
}

void AdaptiveThresholdProcessing::setMaxThreshold(int maxThreshold)
{
    QMutexLocker lock(&m_mutex);
    m_maxThreshold = maxThreshold;
}

int AdaptiveThresholdProcessing::getIdThresholdType() const
{
    return m_idThresholdType;
}

void AdaptiveThresholdProcessing::setIdThresholdType(int idThresholdType)
{
    QMutexLocker lock(&m_mutex);
    m_idThresholdType = idThresholdType;
}

QStringList AdaptiveThresholdProcessing::getThresholTypesList() const
{
    return m_thresholTypesList;
}

int AdaptiveThresholdProcessing::getIdAdaptiveType() const
{
    return m_idAdaptiveType;
}

void AdaptiveThresholdProcessing::setIdAdaptiveType(int value)
{
    QMutexLocker lock(&m_mutex);
    m_idAdaptiveType = value;
}

QStringList AdaptiveThresholdProcessing::getAdaptiveTypesList() const
{
    return m_adaptiveTypesList;
}

int AdaptiveThresholdProcessing::getKernelIndex() const
{
    return m_kernelIndex;
}

void AdaptiveThresholdProcessing::setKernelIndex(int kernelIndex)
{
    QMutexLocker lock(&m_mutex);
    m_kernelIndex = kernelIndex;
}

QStringList AdaptiveThresholdProcessing::getKernelList() const
{
    return m_kernelList;
}

void AdaptiveThresholdProcessing::intputVideoStream(const cv::Mat &frame)
{
    frame.copyTo(m_frame);
    //m_mutex.lock();
    cv::adaptiveThreshold(m_frame,m_outFrame,m_maxThreshold,m_adaptiveTypeValues[m_idAdaptiveType],
                          m_thresholTypeValues[m_idThresholdType],m_kernelValueList[m_kernelIndex],
                          m_paramConstant);
    //m_mutex.unlock();
    emit outputVideoStream(m_outFrame);
}

double AdaptiveThresholdProcessing::getParamConstant() const
{
    return m_paramConstant;
}

void AdaptiveThresholdProcessing::setParamConstant(double paramConstant)
{
    QMutexLocker lock(&m_mutex);
    m_paramConstant = paramConstant;
}

void AdaptiveThresholdProcessing::setModuleParameter(const QJsonObject &param)
{
    m_maxThreshold = param["maxThreshold"].toInt();
    m_idAdaptiveType = param["idAdaptiveType"].toInt();
    m_idThresholdType = param["idThresholdType"].toInt();
    m_kernelIndex = param["kernelIndex"].toInt();
    m_paramConstant = param["paramConstant"].toDouble();
}

void AdaptiveThresholdProcessing::getModuleParameter(QJsonObject &param)
{
    param["maxThreshold"] = m_maxThreshold;
    param["idAdaptiveType"] = m_idAdaptiveType;
    param["idThresholdType"] = m_idThresholdType;
    param["kernelIndex"] = m_kernelIndex;
    param["paramConstant"] = m_paramConstant;

}
