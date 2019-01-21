#include "correlationprocessing.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <QMutexLocker>
#include "blockenums.h"
#include "moduleconfig.h"

CorrelationProcessing::CorrelationProcessing(QObject *parent)
    : CommonProcessing(parent)
{
    setBlockProcessingName("Correlation");
	setBlockProcessing(CONFUGUATOR::BlockProcessing::Filtering);
    setModuleType(BLOCKSTYPE::ModuleType::Correlation);
}

CorrelationProcessing::~CorrelationProcessing()
{
    QMutexLocker lock(&m_mutex);
}

void CorrelationProcessing::intputVideoStream(const cv::Mat &frame)
{
    m_mutex.lock();
    frame.copyTo(m_frame);
	switch (filterType)
	{
		case LINEAR: blur(m_frame, m_outFrame, cv::Size(X, Y)); // �������� ������������ ������
		break;
		case MEDIAN: medianBlur(m_frame, m_outFrame, X); // ��������� ������
		break;
		case SUSPENDED: GaussianBlur(m_frame, m_outFrame, cv::Size(X, Y), 0); // ���������� ������� ������
	}
	
	m_mutex.unlock();
    
	emit outputVideoStream(m_outFrame); 
}

int CorrelationProcessing::getY() const
{
    return Y;
}

int CorrelationProcessing::getX() const
{
    return X;
}

int CorrelationProcessing::getFilterType() const
{
    return filterType;
}

void CorrelationProcessing::setFilterType(FILTER filter)
{
    filterType = filter;
}

void CorrelationProcessing::setX(int value)
{
	X = value;
}

void CorrelationProcessing::setY(int value)
{
	Y = value;
}

