#include "gammawidget.h"
#include "gammaprocessing.h"
#include "ui_gammaprocessingwidget.h"

GammaWidget::GammaWidget(GammaProcessing *processing, QWidget *parent)
	: BaseProcessingWidget(parent)
{
	QWidget* itemWidget = new QWidget;
	Ui::GammaProcessingWidget* ui = new Ui::GammaProcessingWidget;
	ui->setupUi(itemWidget);
	setSettingsWidget(itemWidget); /// устанавливаем виджет на лайаут в BaseProcessingWidget
	connect(ui->doubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(onValueChangedConstant(double)));
	connect(ui->doubleSpinBox_1, SIGNAL(valueChanged(double)), this, SLOT(onValueChangedConstantPow(double)));
	m_processing = processing;
    ui->doubleSpinBox->setValue(m_processing->getConstant()); /// устанавливаем значение по умолчанию для константы степенного преобразования изображения
    ui->doubleSpinBox_1->setValue(m_processing->getConstantPow()); /// устанавливаем значение по умолчанию для  степенной константы преобразования изображения
	
	connect(m_processing, SIGNAL(outputVideoStream(cv::Mat)), this, SLOT(setVideoFrame(cv::Mat)));
	
	setWindowTitle(tr("ПК Гамма"));
}

GammaWidget::~GammaWidget()
{

}

void GammaWidget::onValueChangedConstant(double value)
{
	m_processing->setConstant(value);
}

void GammaWidget::onValueChangedConstantPow(double value)
{
	m_processing->setConstantPow(value);
}
