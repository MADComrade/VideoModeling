#include "logarithmwidget.h"
#include "logarithmprocessing.h"
#include "ui_logarithmprocessingwidget.h"

LogarithmWidget::LogarithmWidget(LogarithmProcessing *processing, QWidget *parent)
	: BaseProcessingWidget(parent)
{
//	QWidget* itemWidget = new QWidget;
//	Ui::LogarithmProcessingWidget* ui = new Ui::LogarithmProcessingWidget;
//	ui->setupUi(itemWidget);
//	setSettingsWidget(itemWidget); /// устанавливаем виджет на лайаут в BaseProcessingWidget
//	connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(onValueChangedConstant(double)));
	m_processing = processing;
//    ui->doubleSpinBox->setValue(m_processing->getConstant()); /// устанавливаем значение по умолчанию для константы логарифмического преобразования изображения
	
	connect(m_processing, SIGNAL(outputVideoStream(cv::Mat)), this, SLOT(setVideoFrame(cv::Mat)));
	
	setWindowTitle(tr("ПК Логарифм"));
}

LogarithmWidget::~LogarithmWidget()
{

}

void LogarithmWidget::onValueChangedConstant(double value)
{
	m_processing->setConstant(value);
}
