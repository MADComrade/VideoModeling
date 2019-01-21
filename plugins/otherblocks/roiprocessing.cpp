#include "roiprocessing.h"
#include <opencv2/opencv.hpp>
#include <QMutexLocker>
#include <QDebug>
#include "moduleconfig.h"
#include "blockenums.h"

ROIProcessing::ROIProcessing(QObject *parent)
    : CommonProcessing(parent)
{
    m_topAngle = std::pair<int,int>(0,0);
    m_bottomAngle = std::pair<int,int>(0,0);
    m_inputImageSize = cv::Size(0,0);

    setBlockProcessingName("ROI");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Transformations);
    setModuleType(BLOCKSTYPE::ModuleType::ROI);
}

ROIProcessing::~ROIProcessing()
{
    QMutexLocker lock(&m_mutex);
}

std::pair<int, int> ROIProcessing::topAngle() const
{
    return m_topAngle;
}

std::pair<int, int> ROIProcessing::bottomAngle() const
{
    return m_bottomAngle;
}

void ROIProcessing::setTopX(int x)
{
    QMutexLocker lock(&m_mutex);
    m_topAngle.first = x;
}

void ROIProcessing::setTopY(int y)
{
    QMutexLocker lock(&m_mutex);
    m_topAngle.second = y;
}

void ROIProcessing::setBottomX(int x)
{
    QMutexLocker lock(&m_mutex);
    m_bottomAngle.first = x;
}

void ROIProcessing::setBottomY(int y)
{
    QMutexLocker lock(&m_mutex);
    m_bottomAngle.second = y;
}

void ROIProcessing::setModuleParameter(const QJsonObject &param)
{
    m_bottomAngle.first = param["bottomX"].toInt();
    m_bottomAngle.second = param["bottomY"].toInt();
    m_topAngle.first = param["topX"].toInt();
    m_topAngle.second = param["topY"].toInt();
    m_inputImageSize.height = param["ImageHeight"].toInt();
    m_inputImageSize.width = param["ImageWidth"].toInt();
}

void ROIProcessing::getModuleParameter(QJsonObject &param)
{
    param["bottomX"] = m_bottomAngle.first;
    param["bottomY"] = m_bottomAngle.second;
    param["topX"] = m_topAngle.first;
    param["topY"] = m_topAngle.second;
    param["ImageHeight"] = m_inputImageSize.height;
    param["ImageWidth"] =m_inputImageSize.width;
}

void ROIProcessing::intputVideoStream(const cv::Mat &frame)
{
    QMutexLocker lock(&m_mutex);
    frame.copyTo(m_frame);
    if(m_frame.size() != m_inputImageSize){
        m_inputImageSize = m_frame.size();
        m_topAngle = std::pair<int,int>(0,0);
        m_bottomAngle.first = m_inputImageSize.width;
        m_bottomAngle.second = m_inputImageSize.height;
        emit onChangedSizeImage();
    }
    int w = m_bottomAngle.first - m_topAngle.first;
    int h = m_bottomAngle.second - m_topAngle.second;
        m_frame(cv::Rect(m_topAngle.first,
                                      m_topAngle.second,
                                      w,
                                      h
                         )
                ).copyTo(m_outFrame);
    emit outputVideoStream(m_outFrame);
}
