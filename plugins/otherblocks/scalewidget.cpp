#include "scalewidget.h"
#include "ui_scaleui.h"

#include "scaleprocessing.h"

ScaleWidget::ScaleWidget(ScaleProcessing *processing, QWidget *parent)
    : BaseProcessingWidget(parent),
      m_processing(processing)
{
    QWidget* itemWidget = new QWidget;
    Ui::ScaleUI* ui = new Ui::ScaleUI;
    ui->setupUi(itemWidget);
    setSettingsWidget(itemWidget); /// устанавливаем виджет на лайаут в BaseProcessingWidget
    ui->scaleSpinBox->setValue(m_processing->scaleValue());

    connect(ui->scaleSpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_processing->setScaleValue(d); });

    connect(m_processing,SIGNAL(outputVideoStream(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));

}
