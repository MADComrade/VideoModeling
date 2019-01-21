#include "gaussiannoiseprocessing.h"
#include "blockenums.h"
#include "moduleconfig.h"

GaussianNoiseProcessing::GaussianNoiseProcessing(QObject *parent)
    : CommonProcessing(parent)
{
    setBlockProcessingName("Noise(G)");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Transformations);
    setModuleType(BLOCKSTYPE::ModuleType::GaussianNoise);
}

GaussianNoiseProcessing::~GaussianNoiseProcessing()
{
QMutexLocker lock(&m_mutex);
}

void GaussianNoiseProcessing::setModuleParameter(const QJsonObject &param)
{
    m_sigma = param["sigma"].toDouble();
    m_mean = param["mean"].toDouble();
}

void GaussianNoiseProcessing::getModuleParameter(QJsonObject &param)
{
   param["sigma"] = m_sigma;
   param["mean"] = m_mean;
}

void GaussianNoiseProcessing::intputVideoStream(const cv::Mat &frame)
{
    QMutexLocker lock(&m_mutex);
    frame.copyTo(m_frame);
    m_rand.fill(m_frame, cv::RNG::NORMAL, m_mean,m_sigma);
    cv::add(m_frame,frame,m_frame);
    emit outputVideoStream(m_frame);
}

float GaussianNoiseProcessing::getSigma() const
{
    return m_sigma;
}

void GaussianNoiseProcessing::setSigma(float sigma)
{
    QMutexLocker lock(&m_mutex);
    m_sigma = sigma;
}

float GaussianNoiseProcessing::getMean() const
{
    return m_mean;
}

void GaussianNoiseProcessing::setMean(float mean)
{
    QMutexLocker lock(&m_mutex);
    m_mean = mean;
}
