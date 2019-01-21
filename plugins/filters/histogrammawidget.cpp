#include "histogrammawidget.h"
#include "histogrammaprocessing.h"

HistogrammaWidget::HistogrammaWidget(HistogrammaProcessing *processing, QWidget *parent)
	: BaseProcessingWidget(parent)
{
	m_processing = processing;
	connect(m_processing, SIGNAL(outputVideoStream(cv::Mat)), this, SLOT(setVideoFrame(cv::Mat)));

	setWindowTitle(tr("ПК Гистограмма"));
}

HistogrammaWidget::~HistogrammaWidget()
{

}
