#include "gammaprocessing.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <QMutexLocker>
#include "blockenums.h"
#include "moduleconfig.h"

GammaProcessing::GammaProcessing(QObject *parent)
    : CommonProcessing(parent)
{
    setBlockProcessingName("Gamma");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Filtering);
    setModuleType(BLOCKSTYPE::ModuleType::Gamma);
}

GammaProcessing::~GammaProcessing()
{
    QMutexLocker lock(&m_mutex);
}

void GammaProcessing::intputVideoStream(const cv::Mat &frame)
{
    frame.copyTo(m_frame);
    m_mutex.lock();

    for (int i = 0; i < m_frame.rows; i++)
        for (int j = 0; j < m_frame.cols; j++)
        {
            m_frame.at<uchar>(i, j) = constant * (pow(m_frame.at<uchar>(i, j)/255.0, constantPow)*255);
        }

    m_frame.copyTo(m_outFrame);
    m_mutex.unlock();
    
    emit outputVideoStream(m_outFrame);
}

double GammaProcessing::getConstantPow() const
{
    return constantPow;
}

void GammaProcessing::setModuleParameter(const QJsonObject &param)
{
    constantPow = param["constantPow"].toDouble();
    constant = param["constant"].toDouble();
}

void GammaProcessing::getModuleParameter(QJsonObject &param)
{
    param["constantPow"] = constantPow;
    param["constant"] = constant;
}

double GammaProcessing::getConstant() const
{
    return constant;
}

void GammaProcessing::setConstant(double value)
{
    constant = value;
}

void GammaProcessing::setConstantPow(double value)
{
    constantPow = value;
}

