#include "imageplayerwidget.h"

#include "imageplayer.h"
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QIcon>
#include <QFileDialog>
#include <QMessageBox>

#define PARAM_MAX 10000
#define PARAM_MIN 1000

ImagePlayerWidget::ImagePlayerWidget(ImagePlayer *player, QWidget *parent)
    : BaseProcessingWidget(parent)
{
    m_player = player;
    QHBoxLayout* procLayout = new QHBoxLayout();
    QVBoxLayout* linkage = new QVBoxLayout();
    m_tickSlider =new QSlider(Qt::Horizontal,this);
    m_tickSlider->setMaximum(PARAM_MAX);
    m_tickSlider->setMinimum(PARAM_MIN);
    m_tickSlider->setValue(m_player->getSleepImageTick());
    QLabel* m_tickAbout = new QLabel(tr("Tick value "),this);
    m_tickText = new QLabel(QString::number(m_player->getSleepImageTick()/1000.0) + " sec",this);
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
    connect(m_tickSlider,SIGNAL(valueChanged(int)),this,SLOT(onChangedTick(int)));
    connect(m_loadButton,SIGNAL(released()),this,SLOT(onClickLoad()));
    connect(m_startStopButton,SIGNAL(released()),this,SLOT(onClickStartStop()));
    connect(m_player,SIGNAL(outputVideoStream(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));
    connect(m_player,SIGNAL(outputImage(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));
    setWindowTitle(tr("Блок генерации видео из изображения"));
}

void ImagePlayerWidget::onClickLoad()
{
    if(m_player->isStart()){
        m_player->stopPlay();
    }
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open Image"), ".",
                                                    tr("Image Files (*.png *.bmp *.jpg)"));
    if (!filename.isEmpty()){
        if (!m_player->loadImage(filename.toStdString()))
        {
            QMessageBox msgBox;
            msgBox.setText("The selected video could not be opened!");
            msgBox.exec();
        }
    }
}

void ImagePlayerWidget::onClickStartStop()
{
    if(m_player->getLoadFlag()){
        if(m_player->isStart()){
            m_player->stopPlay();
        }else{
            m_player->startPlay();
        }
        swapIcon();
    }

}

void ImagePlayerWidget::onChangedTick(int i)
{
    m_player->setSleepImageTick(i);
    m_tickText->setText(getFormattedTickImage(i));
}

void ImagePlayerWidget::swapIcon()
{
    if(m_player->isStart()){
        m_startStopButton->setIcon(QIcon(":/images/stop.png"));
    }else{
        m_startStopButton->setIcon(QIcon(":/images/start.png"));
    }
}

QString ImagePlayerWidget::getFormattedTickImage(int tick)
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
