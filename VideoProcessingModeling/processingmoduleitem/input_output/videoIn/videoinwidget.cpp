#include "videoinwidget.h"
#include "ui_videoinwidget.h"

#include <QIcon>
#include <QFileDialog>
#include <QMessageBox>
#include <QTime>
#include "videoimageplayer.h"

const int TICK=10000;

VideoInWidget::VideoInWidget(VideoImagePlayer *player, QWidget *parent) :
    CommonWidget(parent),
    ui(new Ui::VideoInWidget),
    m_player(player)
{
    ui->setupUi(this);
    setWorkState(m_player->getWorkState());
    this->setOutputImageLable(ui->outVideoImage);
    if(!m_player->getLoadFlag()){
        ui->startStop_b->setEnabled(false);
    }else{
        if(m_player->getWorkState()){
            ui->horizontalSlider->setMaximum(m_player->getNumberOfFrames());
            ui->label_2->setText( getFormattedTime( (int)m_player->getNumberOfFrames()/(int)m_player->getFrameRate()));
        }
        else{
            ui->horizontalSlider->setMaximum(TICK);
            ui->label_2->setText(getFormattedTickImage(m_player->getSleepImageTick()));
        }
    }
    swapIcon();
    connect(m_player,SIGNAL(outputVideoStream(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));
    connect(m_player,SIGNAL(outputImage(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));
}

VideoInWidget::~VideoInWidget()
{
    disconnect(m_player,SIGNAL(outputVideoStream(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));
    this->deleteLater();
    delete ui;
}

void VideoInWidget::setWorkState(bool state)
{
    if(state){
        ui->workWithVideo_rb->setChecked(true);
        ui->workWithImage_rb->setChecked(false);
    }
    else{
        ui->workWithImage_rb->setChecked(true);
        ui->workWithImage_rb->setChecked(false);
    }
}

void VideoInWidget::on_startStop_b_clicked()
{
    m_player->setPlayState(!m_player->getPlayState());
    swapIcon();
}

void VideoInWidget::on_load_b_clicked()
{
    if(!m_player->getPlayState()){
        if(m_player->getWorkState()){
            QString filename = QFileDialog::getOpenFileName(this,
                                                            tr("Open Video"), ".",
                                                            tr("Video Files (*.avi *.mpg *.mp4 *.mkv)"));
            if (!filename.isEmpty()){
                if (!m_player->loadVideo(filename.toStdString()))
                {
                    QMessageBox msgBox;
                    msgBox.setText("The selected video could not be opened!");
                    msgBox.exec();
                }
                else{
                    ui->startStop_b->setEnabled(true);
                    ui->horizontalSlider->setEnabled(true);
                    ui->horizontalSlider->setMaximum(m_player->getNumberOfFrames());
                    ui->label_2->setText( getFormattedTime( (int)m_player->getNumberOfFrames()/(int)m_player->getFrameRate()));
                    ui->label->setText("0:00");
                }
            }
        }
        else{
            QString filename = QFileDialog::getOpenFileName(this,
                                                            tr("Open Image"), ".",
                                                            tr("Image Files (*.png *.bmp *.jpg)"));
            if (!filename.isEmpty()){
                if (!m_player->loadVideo(filename.toStdString()))
                {
                    QMessageBox msgBox;
                    msgBox.setText("The selected video could not be opened!");
                    msgBox.exec();
                }
                else{
                    ui->startStop_b->setEnabled(true);
                    ui->horizontalSlider->setEnabled(true);
                    ui->horizontalSlider->setMaximum(TICK);
                    ui->horizontalSlider->setValue(m_player->getSleepImageTick());
                    ui->label_2->setText(getFormattedTickImage(m_player->getSleepImageTick()));
                    ui->label->setText("0:00");
                }
            }
        }
    }else{
        QMessageBox msgBox;
        msgBox.setText("Остановите воспроизведение!");
        msgBox.exec();
    }
}

void VideoInWidget::on_workWithVideo_rb_clicked(bool checked)
{
    Q_UNUSED(checked)

    if(m_player->getWorkState()!=true){
        m_player->setWorkState(true);
    }
    if(!m_player->getLoadFlag()){
        ui->startStop_b->setEnabled(false);
        swapIcon();
    }


}

void VideoInWidget::on_workWithImage_rb_clicked(bool checked)
{
    Q_UNUSED(checked)

    if(m_player->getWorkState()!=false){
        m_player->setWorkState(false);
    }
    if(!m_player->getLoadFlag()){
        ui->startStop_b->setEnabled(false);
        swapIcon();
    }
}

void VideoInWidget::swapIcon()
{
    if(m_player->getPlayState()){
        ui->startStop_b->setIcon(QIcon(":/images/stop.png"));
    }
    else{
        ui->startStop_b->setIcon(QIcon(":/images/start.png"));
    }

}

QString VideoInWidget::getFormattedTime(int timeInSeconds)
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

QString VideoInWidget::getFormattedTickImage(int tick)
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

void VideoInWidget::on_horizontalSlider_sliderMoved(int position)
{
    if(m_player->getWorkState()){
        m_player->setCurrentFrame(position);
        ui->label->setText( getFormattedTime( position/(int)m_player->getFrameRate()) );
    }
    else{
        m_player->setSleepImageTick(position);
        ui->label_2->setText( getFormattedTickImage( position) );
    }
}

void VideoInWidget::setVideoFrame(const cv::Mat &frame)
{
     if(m_player->getWorkState()){
         ui->label->setText( getFormattedTime((int)(m_player->getCurrentFrame()/m_player->getFrameRate())));
         ui->horizontalSlider->setValue(m_player->getCurrentFrame());
     }
    CommonWidget::setVideoFrame(frame);
}
