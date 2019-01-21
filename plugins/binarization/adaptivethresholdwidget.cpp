#include "adaptivethresholdwidget.h"

#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "adaptivethresholdprocessing.h"

#define TMAX 255
#define TMIN 1
#define PARAM_MAX 1000
#define PARAM_MIN -1000

AdaptiveThresholdWidget::AdaptiveThresholdWidget(AdaptiveThresholdProcessing *processingLevel, QWidget *parent)
    : BaseProcessingWidget(parent),
      m_processingLevel(processingLevel)
{
    QHBoxLayout* procLayout = new QHBoxLayout();
    QVBoxLayout* linkage = new QVBoxLayout();
    m_maxSlider =new QSlider(Qt::Horizontal,this);
    m_maxSlider->setMaximum(TMAX);
    m_maxSlider->setMinimum(TMIN);
    m_maxSlider->setValue(m_processingLevel->maxThreshold());
    QLabel* m_maxAbout = new QLabel(tr("Max value "),this);
    m_maxText = new QLabel(QString::number(m_processingLevel->maxThreshold()),this);
    procLayout->addWidget(m_maxAbout);
    procLayout->addWidget(m_maxSlider);
    procLayout->addWidget(m_maxText);
    linkage->addItem(procLayout);

    procLayout = new QHBoxLayout();
    m_paramConstantSlider =new QSlider(Qt::Horizontal,this);
    m_paramConstantSlider->setMaximum(PARAM_MAX);
    m_paramConstantSlider->setMinimum(PARAM_MIN);
    m_paramConstantSlider->setValue(int(m_processingLevel->getParamConstant()*m_paramConstantCoeff));
    QLabel* m_constAbout = new QLabel(tr("C value "),this);
    m_paramConstantText = new QLabel(QString::number(m_processingLevel->getParamConstant()),this);
    procLayout->addWidget(m_constAbout);
    procLayout->addWidget(m_paramConstantSlider);
    procLayout->addWidget(m_paramConstantText);
    linkage->addItem(procLayout);

    procLayout = new QHBoxLayout();
    QLabel* m_label = new QLabel(tr("Метод адаптивной бина-ции"),this);
    m_switchAdaptiveMethod = new QComboBox(this);
    m_switchAdaptiveMethod->addItems(m_processingLevel->getAdaptiveTypesList());
    m_switchAdaptiveMethod->setCurrentIndex(m_processingLevel->getIdAdaptiveType());
    procLayout->addWidget(m_label);
    procLayout->addWidget(m_switchAdaptiveMethod);
    linkage->addItem(procLayout);


    procLayout = new QHBoxLayout();
    m_label = new QLabel(tr("Размер аппертуры фильтра"),this);
    m_switchKernel = new QComboBox(this);
    m_switchKernel->addItems(m_processingLevel->getKernelList());
    m_switchKernel->setCurrentIndex(m_processingLevel->getKernelIndex());
    procLayout->addWidget(m_label);
    procLayout->addWidget(m_switchKernel);
    linkage->addItem(procLayout);

    procLayout = new QHBoxLayout();
    m_label = new QLabel(tr("Тип бинаризации"),this);
    m_switchThresholdType = new QComboBox(this);
    m_switchThresholdType->addItems(m_processingLevel->getThresholTypesList());
    m_switchThresholdType->setCurrentIndex(m_processingLevel->getIdThresholdType());
    procLayout->addWidget(m_label);
    procLayout->addWidget(m_switchThresholdType);
    linkage->addItem(procLayout);

    QWidget* itemWidget = new QWidget;
    itemWidget->setLayout(linkage);
    setSettingsWidget(itemWidget);

    connect(m_maxSlider,SIGNAL(valueChanged(int)),this,SLOT(onChangedMax(int)));
    connect(m_paramConstantSlider,SIGNAL(valueChanged(int)),this,SLOT(onChangedParamConstant(int)));
    connect(m_switchAdaptiveMethod,SIGNAL(currentIndexChanged(int)),this,SLOT(onChangedAdaptiveMethod(int)));
    connect(m_switchKernel,SIGNAL(currentIndexChanged(int)),this,SLOT(onChangedKernel(int)));
    connect(m_switchThresholdType,SIGNAL(currentIndexChanged(int)),this,SLOT(onChangedThresholdType(int)));
    connect(m_processingLevel,SIGNAL(outputVideoStream(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));
    setWindowTitle(tr("Настройка блока адаптивной бинаризации"));
}

void AdaptiveThresholdWidget::onChangedMax(int i)
{
    m_maxText->setText(QString::number(i));
    m_processingLevel->setMaxThreshold(i);
}

void AdaptiveThresholdWidget::onChangedParamConstant(int i)
{
    if(i!=0){
        m_constant = i/m_paramConstantCoeff;
    }else{
        m_constant = i;
    }
     m_paramConstantText->setText(QString::number(m_constant));
     m_processingLevel->setParamConstant(m_constant);

}

void AdaptiveThresholdWidget::onChangedKernel(int i)
{
    if(i>=0){
        m_processingLevel->setKernelIndex(i);
    }

}

void AdaptiveThresholdWidget::onChangedAdaptiveMethod(int i)
{
    if(i>=0){
        m_processingLevel->setIdAdaptiveType(i);
    }
}

void AdaptiveThresholdWidget::onChangedThresholdType(int i)
{
    if(i>=0){
        m_processingLevel->setIdThresholdType(i);
    }
}
