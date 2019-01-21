#include "scaleprocessing.h"
#include <opencv2/opencv.hpp>

#include "moduleconfig.h"
#include "blockenums.h"

using namespace cv;

ScaleProcessing::ScaleProcessing(QObject *parent) : CommonProcessing(parent)
{
    setBlockProcessingName("Scale");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Transformations);
    setModuleType(BLOCKSTYPE::ModuleType::Scale);
}

ScaleProcessing::~ScaleProcessing()
{
    QMutexLocker lock(&m_mutex);
}

double ScaleProcessing::scaleValue() const
{
    return m_scaleValue;
}

void ScaleProcessing::setScaleValue(double scaleValue)
{
    m_scaleValue = scaleValue;
}

void ScaleProcessing::setModuleParameter(const QJsonObject &param)
{
    m_scaleValue = param["scale"].toDouble();
}

void ScaleProcessing::getModuleParameter(QJsonObject &param)
{
    param["scale"] = m_scaleValue;
}

void ScaleProcessing::intputVideoStream(const cv::Mat &frame)
{
    QMutexLocker lock(&m_mutex);
    frame.copyTo(m_frame);
    scale(m_frame,m_outFrame,m_scaleValue);
    emit outputVideoStream(m_outFrame);
}

void ScaleProcessing::scale(const cv::Mat &src, cv::Mat &dst, double f, Scalar intensity)
{
    //check if scale factor is valid
    if (f <= 0.0 || f == 1.0)
    {
        dst = src;
        return;
    }

    scale(src, dst, f, f, intensity);
}

void ScaleProcessing::scale(const cv::Mat &src, cv::Mat &dst, double cx, double cy, Scalar intensity)
{
    assert(cx > 0);
    assert(cy > 0);

    Matx33f m0(static_cast<float>(1 / cx), 0, 0, 0, static_cast<float>(1 / cy), 0, 0, 0, 1);
    Matx33f m1(1, 0, static_cast<float>(-src.cols / 2 * (1 - cx)), 0, 1, static_cast<float>(-src.rows / 2 * (1 - cy)), 0, 0, 1);;

    cv::warpPerspective(
        src,
        dst,
        m0 * m1,
        src.size(),
        cv::INTER_CUBIC | cv::WARP_INVERSE_MAP,
        cv::BORDER_CONSTANT,
        intensity
    );
}
