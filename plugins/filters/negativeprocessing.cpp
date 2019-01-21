#include "negativeprocessing.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <QMutexLocker>
#include "blockenums.h"
#include "moduleconfig.h"

NegativeProcessing::NegativeProcessing(QObject *parent)
    : CommonProcessing(parent)
{
    setBlockProcessingName("Negative");
	setBlockProcessing(CONFUGUATOR::BlockProcessing::Filtering);
    setModuleType(BLOCKSTYPE::ModuleType::Negative);
}

NegativeProcessing::~NegativeProcessing()
{
    QMutexLocker lock(&m_mutex);
}

void NegativeProcessing::intputVideoStream(const cv::Mat &frame)
{
    QMutexLocker lock(&m_mutex);
    frame.copyTo(m_frame);
    cv::bitwise_not(m_frame,m_outFrame);
    
	emit outputVideoStream(m_outFrame); 
}

