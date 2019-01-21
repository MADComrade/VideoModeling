#include "roiwidget.h"
#include "roiprocessing.h"
#include "ui_roiform.h"

ROIWidget::ROIWidget(ROIProcessing *processing, QWidget *parent)
    : BaseProcessingWidget(parent),
      m_processing(processing)
{
    QWidget* itemWidget = new QWidget;
    ui = new Ui::RoiUI;
    ui->setupUi(itemWidget);
    setSettingsWidget(itemWidget); /// устанавливаем виджет на лайаут в BaseProcessingWidget

    onChangedSizeImage();

    connect(ui->xTopSlider,SIGNAL(valueChanged(int)),this,SLOT(onTopXChanged(int)));
    connect(ui->yTopSlider,SIGNAL(valueChanged(int)),this,SLOT(onTopYChanged(int)));
    connect(ui->xBottomSlider,SIGNAL(valueChanged(int)),this,SLOT(onBottomXChanged(int)));
    connect(ui->yBottomSlider,SIGNAL(valueChanged(int)),this,SLOT(onBottomYChanged(int)));
    connect(m_processing,SIGNAL(onChangedSizeImage()),this,SLOT(onChangedSizeImage()));
    connect(m_processing,SIGNAL(outputVideoStream(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));
    setTitleWidget("ROI");
}

void ROIWidget::onTopXChanged(int x)
{
    if(x % 4 == 0){
        if(x < ui->xBottomSlider->value()){
            m_processing->setTopX(x);
            ui->xTop->setText(QString::number(x));}
        else
            ui->xTopSlider->setValue(ui->xBottomSlider->value()-1);
    }
}

void ROIWidget::onTopYChanged(int y)
{
    if(y % 4 == 0){
        if(y < ui->yBottomSlider->value()){
            m_processing->setTopY(y);
            ui->yTop->setText(QString::number(y));
        }
        else
            ui->yTopSlider->setValue(ui->yBottomSlider->value()-1);
    }
}

void ROIWidget::onBottomXChanged(int x)
{
    if(x % 4 == 0){
        if(x > ui->xTopSlider->value()){
            m_processing->setBottomX(x);
            ui->xBottom->setText(QString::number(x));
        }
        else
            ui->xBottomSlider->setValue(ui->xTopSlider->value()+1);
    }
}

void ROIWidget::onBottomYChanged(int y)
{
    if(y % 4 == 0){
        if(y > ui->yTopSlider->value()){
            m_processing->setBottomY(y);
            ui->yBottom->setText(QString::number(y));
        }
        else
            ui->yBottomSlider->setValue(ui->yTopSlider->value()+1);
    }
}

void ROIWidget::onChangedSizeImage()
{
    std::pair<int,int> size = m_processing->bottomAngle();
    std::pair<int,int> top = m_processing->topAngle();

    ui->xTopSlider->setMaximum(size.first);
    ui->xBottomSlider->setMaximum(size.first);
    ui->yTopSlider->setMaximum(size.second);
    ui->yBottomSlider->setMaximum(size.second);

    ui->xTopSlider->setValue(top.first);
    ui->yTopSlider->setValue(top.second);
    ui->xBottomSlider->setValue(size.first);
    ui->yBottomSlider->setValue(size.second);

    ui->xTop->setText(QString::number(top.first));
    ui->yTop->setText(QString::number(top.second));
    ui->xBottom->setText(QString::number(size.first));
    ui->yBottom->setText(QString::number(size.second));
}
