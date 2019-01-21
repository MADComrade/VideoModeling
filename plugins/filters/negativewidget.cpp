#include "negativewidget.h"
#include "negativeprocessing.h"

NegativeWidget::NegativeWidget(NegativeProcessing *processing, QWidget *parent)
	: BaseProcessingWidget(parent)
{
	m_processing = processing;
	connect(m_processing, SIGNAL(outputVideoStream(cv::Mat)), this, SLOT(setVideoFrame(cv::Mat)));

	setWindowTitle(tr("ПК Негатив"));
}

NegativeWidget::~NegativeWidget()
{

}
