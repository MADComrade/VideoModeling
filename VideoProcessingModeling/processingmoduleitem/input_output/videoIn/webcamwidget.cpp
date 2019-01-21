#include "webcamwidget.h"
#include "webcamplayer.h"
#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QFileDialog>
#include <QMessageBox>

#define PARAM_MAX 10000
#define PARAM_MIN 30


WebCamWidget::WebCamWidget(WebCamPlayer *webCam, QWidget *parent)
    : BaseProcessingWidget(parent)
{
    m_webCam = webCam;
    QHBoxLayout* procLayout = new QHBoxLayout();
    QVBoxLayout* linkage = new QVBoxLayout();
    m_combo = new QComboBox(this);
    m_combo->addItem("None");
    m_combo->addItems(m_webCam->getAvailableCameras());
    m_combo->setCurrentIndex(m_webCam->getIdCam()+1);
    procLayout->addWidget(m_combo);
    linkage->addItem(procLayout);

    procLayout = new QHBoxLayout();
    m_tickSlider =new QSlider(Qt::Horizontal,this);
    m_tickSlider->setMaximum(PARAM_MAX);
    m_tickSlider->setMinimum(PARAM_MIN);
    m_tickSlider->setValue(m_webCam->getSleepImageTick());
    QLabel* m_tickAbout = new QLabel(tr("Tick value "),this);
    m_tickText = new QLabel(QString::number(m_webCam->getSleepImageTick()/1000.0) + " sec",this);
    procLayout->addWidget(m_tickAbout);
    procLayout->addWidget(m_tickSlider);
    procLayout->addWidget(m_tickText);
    linkage->addItem(procLayout);

    procLayout = new QHBoxLayout();
    m_startStopButton = new QPushButton(this);
    procLayout->addWidget(m_startStopButton);
    linkage->addItem(procLayout);

    QWidget* itemWidget = new QWidget;
    itemWidget->setLayout(linkage);
    setSettingsWidget(itemWidget);

    swapIcon();
    connect(m_tickSlider,SIGNAL(valueChanged(int)),this,SLOT(onChangedTick(int)));
    connect(m_startStopButton,SIGNAL(released()),this,SLOT(onClickStartStop()));
    connect(m_webCam,SIGNAL(outputImage(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));
    connect(m_webCam,SIGNAL(outputVideoStream(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));
    connect(m_combo,SIGNAL(currentIndexChanged(int)),this,SLOT(selectCam(int)));
    setWindowTitle(tr("Блок работы с веб-камерой"));

}

WebCamWidget::~WebCamWidget()
{

}

void WebCamWidget::onClickStartStop()
{
    if(m_webCam->isStart()){
        m_webCam->stopPlay();
    }else{
        m_webCam->startPlay();
    }
    swapIcon();
}

void WebCamWidget::onChangedTick(int i)
{
    m_webCam->setSleepImageTick(i);
    m_tickText->setText(getFormattedTickImage(i));
}

void WebCamWidget::selectCam(int index)
{
    if(!m_webCam->isStart())
        m_webCam->setIdCamSelect(index-1);
    else
        m_combo->setCurrentIndex(0);
}

void WebCamWidget::swapIcon()
{
    if(m_webCam->isStart()){
        m_startStopButton->setIcon(QIcon(":/images/stop.png"));
    }else{
        m_startStopButton->setIcon(QIcon(":/images/start.png"));
    }
}

QString WebCamWidget::getFormattedTickImage(int tick)
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
