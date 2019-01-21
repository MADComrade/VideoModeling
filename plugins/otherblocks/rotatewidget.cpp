#include "rotatewidget.h"
#include "rotateprocessing.h"
#include "ui_rotateui.h"
#include <opencv2/opencv.hpp>

RotateWidget::RotateWidget(RotateProcessing *processing, QWidget *parent)
    : BaseProcessingWidget(parent),
      m_processing(processing)
{
    QWidget* itemWidget = new QWidget;
    ui = new Ui::RotateUI;
    ui->setupUi(itemWidget);
    setSettingsWidget(itemWidget); /// устанавливаем виджет на лайаут в BaseProcessingWidget

    ui->angleSpinBox->setValue(m_processing->angle());
    ui->scaleSpinBox->setValue(m_processing->scale());


    ui->xCenterSlider->setMaximum(m_processing->inputImageSize().width);
    ui->yCenterSlider->setMaximum(m_processing->inputImageSize().height);
    ui->xCenterSlider->setMinimum(0);
    ui->yCenterSlider->setMinimum(0);
    ui->xCenterSlider->setValue(m_processing->xCenter());
    ui->yCenterSlider->setValue(m_processing->yCenter());
    ui->xCenter->setText(QString::number(m_processing->xCenter()));
    ui->yCenter->setText(QString::number(m_processing->yCenter()));


    connect(ui->scaleSpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_processing->setScale(d); });
    connect(ui->angleSpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_processing->setAngle(d); });

    connect(ui->xCenterSlider,SIGNAL(valueChanged(int)),this,SLOT(onXChanged(int)));
    connect(ui->yCenterSlider,SIGNAL(valueChanged(int)),this,SLOT(onYChanged(int)));
    connect(m_processing,SIGNAL(onChangedWidth(int)),this,SLOT(onChangedWidth(int)));
    connect(m_processing,SIGNAL(onChangedHeight(int)),this,SLOT(onChangedHeight(int)));

    connect(m_processing,SIGNAL(outputVideoStream(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));
    setTitleWidget("Rotate");
}

void RotateWidget::onXChanged(int x)
{
    m_processing->setXCenter(x);
    ui->xCenter->setText(QString::number(x));
}

void RotateWidget::onYChanged(int y)
{
    m_processing->setYCenter(y);
     ui->yCenter->setText(QString::number(y));
}

void RotateWidget::onChangedWidth(int w)
{
    ui->xCenterSlider->setMaximum(w);
    ui->xCenterSlider->setValue(m_processing->xCenter());
    ui->xCenter->setText(QString::number(m_processing->xCenter()));
}

void RotateWidget::onChangedHeight(int h)
{
    ui->yCenterSlider->setMaximum(h);
    ui->yCenterSlider->setValue(m_processing->yCenter());
    ui->yCenter->setText(QString::number(m_processing->yCenter()));
}
