#include "translatewidget.h"
#include "ui_translateui.h"
#include "translateprocessing.h"

TranslateWidget::TranslateWidget(TranslateProcessing *processing, QWidget *parent)
    : BaseProcessingWidget(parent),
      m_processing(processing)
{
    QWidget* itemWidget = new QWidget;
    ui = new Ui::TranslateUI;
    ui->setupUi(itemWidget);
    setSettingsWidget(itemWidget); /// устанавливаем виджет на лайаут в BaseProcessingWidget



    ui->xCenterSlider->setMaximum(m_processing->inputImageSize().width);
    ui->yCenterSlider->setMaximum(m_processing->inputImageSize().height);
    ui->xCenterSlider->setMinimum(-1*m_processing->inputImageSize().width);
    ui->yCenterSlider->setMinimum(-1*m_processing->inputImageSize().height);
    ui->xCenterSlider->setValue(m_processing->dX());
    ui->yCenterSlider->setValue(m_processing->dY());
    ui->xCenter->setText(QString::number(m_processing->dX()));
    ui->yCenter->setText(QString::number(m_processing->dY()));

    connect(ui->xCenterSlider,SIGNAL(valueChanged(int)),this,SLOT(onXChanged(int)));
    connect(ui->yCenterSlider,SIGNAL(valueChanged(int)),this,SLOT(onYChanged(int)));
    connect(m_processing,SIGNAL(onChangedWidth(int)),this,SLOT(onChangedWidth(int)));
    connect(m_processing,SIGNAL(onChangedHeight(int)),this,SLOT(onChangedHeight(int)));

    connect(m_processing,SIGNAL(outputVideoStream(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));
}

void TranslateWidget::onChangedWidth(int w)
{
    ui->xCenterSlider->setMaximum(w);
    ui->xCenterSlider->setMinimum(-1*w);
    ui->xCenterSlider->setValue(m_processing->dX());
    ui->xCenter->setText(QString::number(m_processing->dX()));
}

void TranslateWidget::onChangedHeight(int h)
{
    ui->yCenterSlider->setMaximum(h);
    ui->yCenterSlider->setMinimum(-1*h);
    ui->yCenterSlider->setValue(m_processing->dY());
    ui->yCenter->setText(QString::number(m_processing->dY()));
}

void TranslateWidget::onXChanged(int x)
{
    m_processing->setDX(x);
    ui->xCenter->setText(QString::number(x));
}

void TranslateWidget::onYChanged(int y)
{
    m_processing->setDY(y);
    ui->yCenter->setText(QString::number(y));
}
