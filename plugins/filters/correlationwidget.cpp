#include "correlationwidget.h"
#include "correlationprocessing.h"
#include "ui_correlationprocessingwidget.h"

CorrelationWidget::CorrelationWidget(CorrelationProcessing *processing, QWidget *parent)
	: BaseProcessingWidget(parent)
{
	QWidget* itemWidget = new QWidget;
	ui = new Ui::CorrelationProcessingWidget;
	ui->setupUi(itemWidget);
	setSettingsWidget(itemWidget); /// устанавливаем виджет на лайаут в BaseProcessingWidget
	
	m_processing = processing;
    ui->spinBox->setValue(m_processing->getX());
    ui->spinBox_1->setValue(m_processing->getY());
    ui->comboBox->setCurrentIndex(m_processing->getFilterType());
    onFilterTypeChanged(ui->comboBox->currentIndex());

	connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(onValueChangedX(int)));
	connect(ui->spinBox_1, SIGNAL(valueChanged(int)), this, SLOT(onValueChangedY(int)));
	connect(ui->comboBox, SIGNAL(activated(int)), this, SLOT(onFilterTypeChanged(int)));
	
	connect(m_processing, SIGNAL(outputVideoStream(cv::Mat)), this, SLOT(setVideoFrame(cv::Mat)));
	
	setWindowTitle(tr("ПК Корреляция (верстка)"));
}

CorrelationWidget::~CorrelationWidget()
{

}

void CorrelationWidget::onValueChangedX(int value)
{
	m_processing->setX(value);
}

void CorrelationWidget::onValueChangedY(int value)
{
	m_processing->setY(value);
}

void CorrelationWidget::onFilterTypeChanged(int value)
{
	CorrelationProcessing::FILTER filterType = CorrelationProcessing::FILTER(value);
	if (CorrelationProcessing::MEDIAN == filterType)
	{
		ui->spinBox_1->setEnabled(false);
		ui->groupBox->setTitle(tr("Апертура"));

		int valueX = ui->spinBox->value(); /// значение должно быть нечетным
		if (!(valueX % 2))
			ui->spinBox->setValue(++valueX);
		ui->spinBox->setSingleStep(2);
	}
	else if (CorrelationProcessing::SUSPENDED == filterType)
	{
		ui->spinBox_1->setEnabled(true);
		ui->groupBox->setTitle(tr("Размер фильтра"));
		int valueX = ui->spinBox->value(); /// значение должно быть нечетным
		if (!(valueX % 2))
			ui->spinBox->setValue(++valueX);
		ui->spinBox->setSingleStep(2);
		int valueY = ui->spinBox_1->value(); /// значение должно быть нечетным
		if (!(valueY % 2))
			ui->spinBox_1->setValue(++valueY);
		ui->spinBox_1->setSingleStep(2);
	} 
	else
	{
		ui->spinBox_1->setEnabled(true);
		ui->spinBox->setSingleStep(1);
		ui->spinBox_1->setSingleStep(1);
		ui->groupBox->setTitle(tr("Размер фильтра"));
	}

	m_processing->setFilterType(CorrelationProcessing::FILTER(filterType));
}
