#include "paramvideoinwidget.h"

#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QString>
#include <QFileDialog>
#include <QTime>
#include <QMessageBox>
#include "paramvideoinput.h"

#define PARAM_MAX 10000
#define PARAM_MIN 500

ParamVideoInWidget::ParamVideoInWidget(ParamVideoInput *videoPlayer, QWidget *parent)
    : BaseProcessingWidget(parent)
{
    m_videoPlayer = videoPlayer;
    QHBoxLayout* procLayout = new QHBoxLayout();
    QVBoxLayout* linkage = new QVBoxLayout();
    m_frameSlider =new QSlider(Qt::Horizontal,this);
    m_frameSlider->setMinimum(0);

    m_currentTimeText = new QLabel(tr("0:00"),this);
    m_maxTimeText = new QLabel(tr("0:00"),this);
    if(m_videoPlayer->getLoadFlag()){
        m_frameSlider->setMaximum(m_videoPlayer->getNumberOfFrames());
        m_frameSlider->setValue(m_videoPlayer->getCurrentFrame());
        m_maxTimeText->setText(getFormattedTime( (int)m_videoPlayer->getNumberOfFrames()/(int)m_videoPlayer->getFrameRate()));
        m_currentTimeText->setText( getFormattedTime( (int)m_videoPlayer->getCurrentFrame()/(int)m_videoPlayer->getFrameRate()));
    }else{
        m_frameSlider->setEnabled(false);
    }
    procLayout->addWidget(m_currentTimeText);
    procLayout->addWidget(m_frameSlider);
    procLayout->addWidget(m_maxTimeText);
    linkage->addItem(procLayout);

    procLayout = new QHBoxLayout();
    m_tickSlider =new QSlider(Qt::Horizontal,this);
    m_tickSlider->setMaximum(PARAM_MAX);
    m_tickSlider->setMinimum(PARAM_MIN);
    m_tickSlider->setValue(m_videoPlayer->getSleepImageTick());
    QLabel* m_tickAbout = new QLabel(tr("Tick value "),this);
    m_tickText = new QLabel(QString::number(m_videoPlayer->getSleepImageTick()/1000.0) + " sec",this);
    procLayout->addWidget(m_tickAbout);
    procLayout->addWidget(m_tickSlider);
    procLayout->addWidget(m_tickText);
    linkage->addItem(procLayout);

    procLayout = new QHBoxLayout();
    m_startStopButton = new QPushButton(this);
    m_loadButton = new QPushButton(tr("Загрузка"), this);
    procLayout->addWidget(m_startStopButton);
    procLayout->addWidget(m_loadButton);
    linkage->addItem(procLayout);

    QWidget* itemWidget = new QWidget;
    itemWidget->setLayout(linkage);
    setSettingsWidget(itemWidget);

    swapIcon();
    connect(m_frameSlider,SIGNAL(valueChanged(int)),this,SLOT(onChangedFrame(int)));
    connect(m_tickSlider,SIGNAL(valueChanged(int)),this,SLOT(onChangedTick(int)));
    connect(m_loadButton,SIGNAL(released()),this,SLOT(onClickLoad()));
    connect(m_startStopButton,SIGNAL(released()),this,SLOT(onClickStartStop()));
    connect(m_videoPlayer,SIGNAL(outputVideoStream(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));
    connect(m_videoPlayer,SIGNAL(outputImage(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));
    setWindowTitle(tr("Параметризированный блок проигрывания видео"));

}

void ParamVideoInWidget::setVideoFrame(const cv::Mat &frame)
{
    m_currentTimeText->setText( getFormattedTime((int)(m_videoPlayer->getCurrentFrame()/m_videoPlayer->getFrameRate())));
    m_frameSlider->setValue(m_videoPlayer->getCurrentFrame());
    CommonWidget::setVideoFrame(frame);
}

void ParamVideoInWidget::onClickLoad()
{
    if(m_videoPlayer->isStart()){
        m_videoPlayer->stopPlay();
    }
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open Video"), ".",
                                                    tr("Video Files (*.avi *.mpg *.mp4 *.mkv)"));
    if (!filename.isEmpty()){
        if (!m_videoPlayer->loadVideo(filename.toStdString()))
        {
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
        }
        else{
            m_frameSlider->setMaximum(m_videoPlayer->getNumberOfFrames());
            m_frameSlider->setValue(m_videoPlayer->getCurrentFrame());
            m_maxTimeText->setText(getFormattedTime((int)m_videoPlayer->getNumberOfFrames()/(int)m_videoPlayer->getFrameRate()));
            m_currentTimeText->setText( getFormattedTime( (int)m_videoPlayer->getCurrentFrame()/(int)m_videoPlayer->getFrameRate()));
            m_frameSlider->setEnabled(true);
        }
    }
}

void ParamVideoInWidget::onClickStartStop()
{
    if(m_videoPlayer->getLoadFlag()){
        if(m_videoPlayer->isStart()){
            m_videoPlayer->stopPlay();
        }else{
            m_videoPlayer->startPlay();
        }
        swapIcon();
    }
}

void ParamVideoInWidget::onChangedTick(int i)
{
    m_videoPlayer->setSleepImageTick(i);
    m_tickText->setText(getFormattedTickImage(i));
}

void ParamVideoInWidget::onChangedFrame(int i)
{
    m_videoPlayer->setCurrentFrame(i);
    m_currentTimeText->setText( getFormattedTime( i/(int)m_videoPlayer->getFrameRate()) );
}

void ParamVideoInWidget::swapIcon()
{
    if(m_videoPlayer->isStart()){
        m_startStopButton->setIcon(QIcon(":/images/stop.png"));
    }else{
        m_startStopButton->setIcon(QIcon(":/images/start.png"));
    }
}

QString ParamVideoInWidget::getFormattedTime(int timeInSeconds)
{
    int seconds = (int) (timeInSeconds) % 60 ;
    int minutes = (int) ((timeInSeconds / 60) % 60);
    int hours   = (int) ((timeInSeconds / (60*60)) % 24);

    QTime t(hours, minutes, seconds);
    if (hours == 0 )
        return t.toString("mm:ss");
    else
        return t.toString("h:mm:ss");
}

QString ParamVideoInWidget::getFormattedTickImage(int tick)
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
