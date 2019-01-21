#include "rotateprocessing.h"
#include <opencv2/opencv.hpp>

#include "moduleconfig.h"
#include "blockenums.h"

RotateProcessing::RotateProcessing(QObject *parent) : CommonProcessing(parent)
{
    m_inputImageSize.width = 0;
    m_inputImageSize.height = 0;

    setBlockProcessingName("Rotate");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Transformations);
    setModuleType(BLOCKSTYPE::ModuleType::Rotate);
}

RotateProcessing::~RotateProcessing()
{
    QMutexLocker lock(&m_mutex);
}

int RotateProcessing::xCenter() const
{
    return m_xCenter;
}

void RotateProcessing::setXCenter(int xCenter)
{
    m_xCenter = xCenter;
}

int RotateProcessing::yCenter() const
{
    return m_yCenter;
}

void RotateProcessing::setYCenter(int yCenter)
{
    m_yCenter = yCenter;
}

double RotateProcessing::scale() const
{
    return m_scale;
}

void RotateProcessing::setScale(double scale)
{
    m_scale = scale;
}

double RotateProcessing::angle() const
{
    return m_angle;
}

void RotateProcessing::setAngle(double angle)
{
    m_angle = angle;
}

void RotateProcessing::intputVideoStream(const cv::Mat &frame)
{
    QMutexLocker lock(&m_mutex);
    frame.copyTo(m_frame);
    if(m_frame.size() != m_inputImageSize){
        m_inputImageSize = m_frame.size();
        m_xCenter = m_inputImageSize.width/2;
        m_yCenter = m_inputImageSize.height/2;
        emit onChangedWidth(m_inputImageSize.width);
        emit onChangedHeight(m_inputImageSize.height);
    }
    rotate(m_frame, m_outFrame, m_angle, cv::Point2f(m_xCenter, m_yCenter),m_scale);
    emit outputVideoStream(m_outFrame);
}

void RotateProcessing::rotate(const cv::Mat &src, cv::Mat &dst, double angle, cv::Point2f center, double scale, cv::Scalar intensity)
{
    cv::Mat rot_mat = cv::getRotationMatrix2D(center, angle, 1 / scale);

    cv::warpAffine(
                src,
                dst,
                rot_mat,
                src.size(),
                cv::INTER_CUBIC | cv::WARP_INVERSE_MAP,
                cv::BORDER_CONSTANT,
                intensity);
}

cv::Size RotateProcessing::inputImageSize() const
{
    return m_inputImageSize;
}

void RotateProcessing::setInputImageSize(const cv::Size &inputImageSize)
{
    m_inputImageSize = inputImageSize;
}

void RotateProcessing::setModuleParameter(const QJsonObject &param)
{
    m_xCenter =  param["xCenter"].toInt();
    m_yCenter = param["yCenter"].toInt();
    m_angle = param["angle"].toDouble();
    m_scale = param["scale"].toDouble();
    m_inputImageSize.height = param["ImageHeight"].toInt();
    m_inputImageSize.width = param["ImageWidth"].toInt();
}

void RotateProcessing::getModuleParameter(QJsonObject &param)
{
    param["xCenter"] = m_xCenter;
    param["yCenter"] = m_yCenter;
    param["angle"] = m_angle;
    param["scale"] = m_scale;
    param["ImageHeight"] = m_inputImageSize.height;
    param["ImageWidth"] =m_inputImageSize.width;
}
