#include "histogrammaprocessing.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <QMutexLocker>
#include "blockenums.h"
#include "moduleconfig.h"

HistogrammaProcessing::HistogrammaProcessing(QObject *parent)
    : CommonProcessing(parent)
{
    setBlockProcessingName("Histogramma");
	setBlockProcessing(CONFUGUATOR::BlockProcessing::Filtering);
    setModuleType(BLOCKSTYPE::ModuleType::Histogramma);
}

HistogrammaProcessing::~HistogrammaProcessing()
{
    QMutexLocker lock(&m_mutex);
}

void HistogrammaProcessing::intputVideoStream(const cv::Mat &frame)
{
    QMutexLocker lock(&m_mutex);
    frame.copyTo(m_frame);
    cv::equalizeHist(m_frame, m_outFrame);
    
	emit outputVideoStream(m_outFrame); 
}

