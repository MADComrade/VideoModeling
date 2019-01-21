#include "translateprocessing.h"
#include <opencv2/opencv.hpp>

#include "moduleconfig.h"
#include "blockenums.h"

TranslateProcessing::TranslateProcessing(QObject *parent) : CommonProcessing(parent)
{
    m_inputImageSize.width = 0;
    m_inputImageSize.height = 0;

    setBlockProcessingName("Translate");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Transformations);
    setModuleType(BLOCKSTYPE::ModuleType::Translate);
}

TranslateProcessing::~TranslateProcessing()
{
    QMutexLocker lock(&m_mutex);
}

void TranslateProcessing::intputVideoStream(const cv::Mat &frame)
{
    QMutexLocker lock(&m_mutex);
    frame.copyTo(m_frame);
    if(m_frame.size() != m_inputImageSize){
        m_inputImageSize = m_frame.size();
        m_dX = 0;
        m_dY = 0;
        emit onChangedWidth(m_inputImageSize.width);
        emit onChangedHeight(m_inputImageSize.height);
    }
    translate(m_frame, m_outFrame, m_dX, m_dY);
    emit outputVideoStream(m_outFrame);
}

void TranslateProcessing::translate(const cv::Mat &src, cv::Mat &dst, float dx, float dy, cv::Scalar intensity)
{
    cv::Matx33f mtx(1, 0, -dx, 0, 1, -dy, 0, 0, 1);

    cv::warpPerspective(
                src,
                dst,
                mtx,
                src.size(),
                cv::INTER_CUBIC | cv::WARP_INVERSE_MAP,
                cv::BORDER_CONSTANT,
                intensity
                );
}

cv::Size TranslateProcessing::inputImageSize() const
{
    return m_inputImageSize;
}

void TranslateProcessing::setModuleParameter(const QJsonObject &param)
{
    m_dY = param["dY"].toInt();
    m_dX = param["dX"].toInt();
    m_inputImageSize.height = param["ImageHeight"].toInt();
    m_inputImageSize.width = param["ImageWidth"].toInt();
}

void TranslateProcessing::getModuleParameter(QJsonObject &param)
{
    param["dY"] = m_dY;
    param["dX"] = m_dX;
    param["ImageHeight"] = m_inputImageSize.height;
    param["ImageWidth"] =m_inputImageSize.width;
}

int TranslateProcessing::dY() const
{
    return m_dY;
}

void TranslateProcessing::setDY(int dY)
{
    m_dY = dY;
}

int TranslateProcessing::dX() const
{
    return m_dX;
}

void TranslateProcessing::setDX(int dX)
{
    m_dX = dX;
}
