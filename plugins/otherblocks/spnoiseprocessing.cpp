#include "spnoiseprocessing.h"
#include "blockenums.h"
#include "moduleconfig.h"
#include "omp.h"

SPNoiseProcessing::SPNoiseProcessing(QObject *parent)
    : CommonProcessing(parent)
{
    setBlockProcessingName("Noise(S&P)");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Transformations);
    setModuleType(BLOCKSTYPE::ModuleType::SaltAndPaperNoise);
}

SPNoiseProcessing::~SPNoiseProcessing()
{
    QMutexLocker lock(&m_mutex);
}

void SPNoiseProcessing::setModuleParameter(const QJsonObject &param)
{
    m_black = param["black"].toDouble();
    m_white = param["white"].toDouble();
}

void SPNoiseProcessing::getModuleParameter(QJsonObject &param)
{
    param["black"] = m_black;
    param["white"] = m_white;
}

void SPNoiseProcessing::intputVideoStream(const cv::Mat &frame)
{
    QMutexLocker lock(&m_mutex);
    int amount1=frame.rows*frame.cols*m_black;
    int amount2=frame.rows*frame.cols*m_white;
    m_frame = frame.clone();

    #pragma omp parallel for
    for(int counter=0; counter<amount1; ++counter)
    {
        m_frame.at<uchar>(m_rand.uniform( 0,m_frame.rows), m_rand.uniform(0, m_frame.cols)) =0;

    }

    #pragma omp parallel for
    for (int counter=0; counter<amount2; ++counter)
    {
        m_frame.at<uchar>(m_rand.uniform(0,m_frame.rows), m_rand.uniform(0,m_frame.cols)) = 255;
    }

    emit outputVideoStream(m_frame);
}

float SPNoiseProcessing::getWhite() const
{
    return m_white;
}

void SPNoiseProcessing::setWhite(float white)
{
    QMutexLocker lock(&m_mutex);
    m_white = white;
}

float SPNoiseProcessing::getBlack() const
{
    return m_black;
}

void SPNoiseProcessing::setBlack(float black)
{
    QMutexLocker lock(&m_mutex);
    m_black = black;
}
