#include "webcamplayer.h"
#include <QMutexLocker>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "moduleconfig.h"
#include "simulationsingleton.h"

#include <QCameraInfo>
#include <QDebug>

WebCamPlayer::WebCamPlayer(QObject *parent) : CommonProcessing(parent)
{
    connect(&m_thread,SIGNAL(started()),this,SLOT(run()));
    this->moveToThread(&m_thread);
    setBlockProcessingName("WebCam");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::IO);
    setModuleType(CONFUGUATOR::ModuleType::WebCam);
}

WebCamPlayer::~WebCamPlayer()
{
    QMutexLocker a(&m_mutex);
    if(m_start){
        m_start = false;
        m_thread.terminate();
        m_thread.deleteLater();
        m_thread.wait();
    }
}

bool WebCamPlayer::isStart() const
{
    return m_start;
}

void WebCamPlayer::startPlay()
{
    if(m_idCam<0){
        emit errorSimulation(tr("Выберете камеру для работы!"));
        return;
    }
    m_start = true;
    m_thread.start();
}

void WebCamPlayer::stopPlay()
{
    m_start = false;
    m_thread.terminate();
}

int WebCamPlayer::getSleepImageTick() const
{
    return m_sleepImageTick;
}

void WebCamPlayer::setSleepImageTick(int sleepImageTick)
{
    m_sleepImageTick = sleepImageTick;
}

QStringList WebCamPlayer::getAvailableCameras() const
{
    QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
    QStringList cams;
    foreach (const QCameraInfo &cameraInfo, cameras){
        cams << cameraInfo.description();
    }

    return cams;
}

void WebCamPlayer::setIdCamSelect(int idCam)
{
    m_idCam = idCam;
}

int WebCamPlayer::getIdCam()
{
    return m_idCam;
}

void WebCamPlayer::run()
{
    cv::VideoCapture cam(m_idCam);
    if (!cam.isOpened()) {
        qDebug()<<"Нет соединения с камерой!";
        return;
    }

    while(m_start){
        cam >> m_frame;
        cv::cvtColor(m_frame,m_outFrame,CV_BGR2GRAY);

        if(getSimulationManager()->isRun()){
            emit outputVideoStream(m_outFrame);
        }
        else
            emit outputImage(m_outFrame);
        this->msleep(m_sleepImageTick);
    }
}

void WebCamPlayer::startInit()
{
    connect(this, SIGNAL(errorSimulation(QString)),getSimulationManager(),SLOT(SimulationError(QString)));
    connect(getSimulationManager(),&SimulationSingleton::startSimulation,this, [this]{
        if(m_idCam<0){
            emit errorSimulation(tr("Выберете камеру для работы!"));
        }else{
            startPlay();
        }
    }, Qt::DirectConnection);
    connect(getSimulationManager(),&SimulationSingleton::stopSimulation,this, [this]{
        stopPlay();
    }, Qt::DirectConnection);
}

void WebCamPlayer::msleep(int ms)
{
//    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
//    nanosleep(&ts, NULL);
    this->thread()->msleep(ms);
}
