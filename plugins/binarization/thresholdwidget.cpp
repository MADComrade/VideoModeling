#include "thresholdwidget.h"

#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "thresholdprocessing.h"

#define TMAX 255
#define TMIN 0

ThresholdWidget::ThresholdWidget(ThresholdProcessing *processing, QWidget *parent)
    : BaseProcessingWidget(parent)
{
    m_processing = processing;

    /// слайдер регулировки нижнего порога
    m_minSlider =new QSlider(Qt::Horizontal,this);
    m_minSlider->setMaximum(TMAX);
    m_minSlider->setMinimum(TMIN);
    m_minSlider->setValue(m_processing->minThreshold());
    QLabel* m_minAbout = new QLabel(tr("Min value "),this);
    m_minText = new QLabel(QString::number(m_processing->minThreshold()),this);
    /// слайдер регулировки верхнего порога
    m_maxSlider =new QSlider(Qt::Horizontal,this);
    m_maxSlider->setMaximum(TMAX);
    m_maxSlider->setMinimum(TMIN);
    m_maxSlider->setValue(m_processing->maxThreshold());
    QLabel* m_maxAbout = new QLabel(tr("Max value "),this);
    m_maxText = new QLabel(QString::number(m_processing->maxThreshold()),this);
    /// объединение группы виджетов отвечающих за нижний порог
    QHBoxLayout* minLine = new QHBoxLayout();
    minLine->addWidget(m_minAbout);
    minLine->addWidget(m_minSlider);
    minLine->addWidget(m_minText);
    /// объединение группы виджетов отвечающих за верхний порог
    QHBoxLayout* maxLine = new QHBoxLayout();
    maxLine->addWidget(m_maxAbout);
    maxLine->addWidget(m_maxSlider);
    maxLine->addWidget(m_maxText);
    /// Выбор типа бинаризации
    QHBoxLayout* typeProc = new QHBoxLayout();
    QLabel* m_switchAbout = new QLabel(tr("Тип бинаризации"),this);
    m_switchProcessing = new QComboBox(this);
    m_switchProcessing->addItems(m_processing->processingTypesList());
    m_switchProcessing->setCurrentIndex(m_processing->typeIndex());
    typeProc->addWidget(m_switchAbout);
    typeProc->addWidget(m_switchProcessing);
    ///Компоновка лайаутов
    QVBoxLayout* linkage = new QVBoxLayout();
    linkage->addItem(minLine);
    linkage->addItem(maxLine);
    linkage->addItem(typeProc);

    QWidget* itemWidget = new QWidget;
    itemWidget->setLayout(linkage); /// помещаем скомпонованный лайаут на виджет

    setSettingsWidget(itemWidget); /// устанавливаем виджет на лайаут в BaseProcessingWidget

    /// инициализируем соединения
    connect(m_maxSlider,SIGNAL(valueChanged(int)),this,SLOT(onChangedMax(int)));
    connect(m_minSlider,SIGNAL(valueChanged(int)),this,SLOT(onChangedMin(int)));
    connect(m_switchProcessing,SIGNAL(currentIndexChanged(int)),this,SLOT(onChangedProcessing(int)));
    connect(m_processing,SIGNAL(outputVideoStream(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));
    setWindowTitle(tr("Настройка блока бинаризации"));
}

ThresholdWidget::~ThresholdWidget()
{

}

void ThresholdWidget::onChangedMax(int i)
{
    if(i>m_minSlider->value()){
        m_maxText->setText(QString::number(i));
        m_processing->setMaxThreshold(i);
    }else{
        m_maxSlider->setValue(m_minSlider->value()+1);
    }
}

void ThresholdWidget::onChangedMin(int i)
{
    if(i<m_maxSlider->value()){
        m_minText->setText(QString::number(i));
        m_processing->setMinThreshold(i);
    }else{
        m_minSlider->setValue(m_maxSlider->value()-1);
    }
}

void ThresholdWidget::onChangedProcessing(int i)
{
    if(i>=0){
        m_processing->setTypeIndex(i);
    }
}
