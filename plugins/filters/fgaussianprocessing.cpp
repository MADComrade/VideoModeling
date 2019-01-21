#include "fgaussianprocessing.h"
#include "additionmethods.h"
#include "blockenums.h"
#include "moduleconfig.h"
using namespace cv;

FGaussianProcessing::FGaussianProcessing(QObject *parent)
    : CommonProcessing(parent)
{
    setBlockProcessingName("FGaussian");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Filtering);
    setModuleType(BLOCKSTYPE::ModuleType::FGaussian);
}

FGaussianProcessing::~FGaussianProcessing()
{
    QMutexLocker lock(&m_mutex);
}

void FGaussianProcessing::intputVideoStream(const cv::Mat &frame)
{
    QMutexLocker lock(&m_mutex);
    m_frame = computeDFT(frame);
    Mat kernel = getGaussianFilter(m_frame.size(), m_sigma, m_inverseFlag);

    Mat planes2[] = { Mat::zeros(m_frame.size(), CV_32F), Mat::zeros(m_frame.size(), CV_32F) };
    planes2[0] = kernel; // real
    //planes2[1] = kernel; // imaginary

    Mat kernel_spec;
    merge(planes2, 2, kernel_spec);

    mulSpectrums(m_frame, kernel_spec, m_frame, 0);
    m_outFrame = computeIDFT(m_frame);
    emit outputVideoStream(m_outFrame);
}

cv::Mat FGaussianProcessing::applyGaussianFilter(cv::Mat src, double sigma)
{
    // create Gaussian kernels
    Mat kernelX = getGaussianKernel(src.size().width, sigma, CV_32F);
    Mat kernelY = getGaussianKernel(src.size().height, sigma, CV_32F);

    Mat dst;
    sepFilter2D(src, dst, -1, kernelX, kernelY);

    return dst;
}

bool FGaussianProcessing::getInverseFlag() const
{
    return m_inverseFlag;
}

void FGaussianProcessing::setInverseFlag(bool inverseFlag)
{
    m_inverseFlag = inverseFlag;
}

void FGaussianProcessing::setModuleParameter(const QJsonObject &param)
{
    m_sigma = param["sigma"].toDouble();
    m_inverseFlag = param["inverseFlag"].toBool();
}

void FGaussianProcessing::getModuleParameter(QJsonObject &param)
{
    param["sigma"] = m_sigma;
    param["inverseFlag"] = m_inverseFlag;
}

double FGaussianProcessing::getSigma() const
{
    return m_sigma;
}

void FGaussianProcessing::setSigma(double sigma)
{
    m_sigma = sigma;
}
