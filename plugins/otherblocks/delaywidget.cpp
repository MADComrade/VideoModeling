#include "delaywidget.h"
#include "delayprocessing.h"
#include <QLabel>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>

#define PARAM_MAX 10000
#define PARAM_MIN 100

DelayWidget::DelayWidget(DelayProcessing *proc, QWidget *parent) :
    BaseProcessingWidget(parent),m_delayProcessing(proc)
{
    QHBoxLayout* procLayout = new QHBoxLayout();
    QVBoxLayout* linkage = new QVBoxLayout();
    m_tickSlider =new QSlider(Qt::Horizontal,this);
    m_tickSlider->setMaximum(PARAM_MAX);
    m_tickSlider->setMinimum(PARAM_MIN);
    m_tickSlider->setValue(m_delayProcessing->getDelayImageTick());
    QLabel* m_tickAbout = new QLabel(tr("Delay value "),this);
    m_tickText = new QLabel(QString::number(m_delayProcessing->getDelayImageTick()/1000.0) + " sec",this);
    procLayout->addWidget(m_tickAbout);
    procLayout->addWidget(m_tickSlider);
    procLayout->addWidget(m_tickText);
    linkage->addItem(procLayout);

    QWidget* itemWidget = new QWidget;
    itemWidget->setLayout(linkage);
    setSettingsWidget(itemWidget);

     connect(m_tickSlider,SIGNAL(valueChanged(int)),this,SLOT(onChangedTick(int)));
     connect(m_tickSlider,SIGNAL(valueChanged(int)),m_delayProcessing,SLOT(setDelayImageTick(int)));
     connect(m_delayProcessing,SIGNAL(outputVideoStream(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));
     setTitleWidget("Delay");
}

DelayWidget::~DelayWidget()
{

}

void DelayWidget::onChangedTick(int i)
{
    m_tickText->setText(getFormattedTickImage(i));
}

QString DelayWidget::getFormattedTickImage(int tick)
{
    float msec = (float)tick/1000;
    QString rezult;
    if(msec <1){
        rezult = QString::number(msec)+ " msec";
    }
    else{
        rezult = QString::number(msec)+ " sec";
    }
    return rezult;
}
