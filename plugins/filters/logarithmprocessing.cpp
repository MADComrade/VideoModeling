#include "logarithmprocessing.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <QMutexLocker>
#include "blockenums.h"
#include "moduleconfig.h"

LogarithmProcessing::LogarithmProcessing(QObject *parent)
    : CommonProcessing(parent)
{
    setBlockProcessingName("Logarithm");
	setBlockProcessing(CONFUGUATOR::BlockProcessing::Filtering);
    setModuleType(BLOCKSTYPE::ModuleType::Logarithm);
}

LogarithmProcessing::~LogarithmProcessing()
{
    QMutexLocker lock(&m_mutex);
}

void LogarithmProcessing::intputVideoStream(const cv::Mat &frame)
{
    QMutexLocker lock(&m_mutex);
    frame.convertTo(m_frame,CV_32F);
    m_frame +=1;
    cv::log(m_frame,m_frame);
    m_frame *=constant;
    cv::normalize(m_frame,m_frame,0,255,cv::NORM_MINMAX);
    cv::convertScaleAbs(m_frame,m_frame);
    m_frame.convertTo(m_outFrame,CV_8U);
    
	emit outputVideoStream(m_outFrame); 
}

double LogarithmProcessing::getConstant() const
{
    return constant;
}

void LogarithmProcessing::setModuleParameter(const QJsonObject &param)
{
    constant = param["constant"].toDouble();
}

void LogarithmProcessing::getModuleParameter(QJsonObject &param)
{
    param["constant"] = constant;
}

void LogarithmProcessing::setConstant(double value)
{
    constant = value;
}

