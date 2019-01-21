#include "cannywidget.h"
#include "ui_cannywidget.h"

#include "cannyprocessing.h"

CannyWidget::CannyWidget(CannyProcessing *processing, QWidget *parent)
    : BaseProcessingWidget(parent)
{
    QWidget* itemWidget = new QWidget(this);
    m_processing = processing;
    m_settingWidget = new Ui::CannyWidget;
    m_settingWidget->setupUi(itemWidget);
    setSettingsWidget(itemWidget);

    m_settingWidget->horizontalSlider->setValue(m_processing->minThreshold());
    m_settingWidget->label_2->setText(QString::number(m_processing->minThreshold()));

    connect(m_settingWidget->horizontalSlider, static_cast<void(QSlider::*)(int)>(&QSlider::valueChanged),
        [=](int d){
        m_processing->setMinThreshold(d);
         m_settingWidget->label_2->setText(QString::number(d));
    });
    connect(m_processing, SIGNAL(outputVideoStream(cv::Mat)), this, SLOT(setVideoFrame(cv::Mat)));

    setWindowTitle(tr("Детектор границ Канни"));
}
