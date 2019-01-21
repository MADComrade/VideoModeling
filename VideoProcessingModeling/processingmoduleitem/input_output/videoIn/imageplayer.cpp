#include "imageplayer.h"
#include <QMutexLocker>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "moduleconfig.h"
#include "simulationsingleton.h"
#include <QDebug>


ImagePlayer::ImagePlayer(QObject *parent)
    : CommonProcessing(parent)
{
    connect(&m_thread,SIGNAL(started()),this,SLOT(run()));
    this->moveToThread(&m_thread);
    setBlockProcessingName("Image");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::IO);
    setModuleType(CONFUGUATOR::ModuleType::ImageInput);
}

ImagePlayer::~ImagePlayer()
{
    QMutexLocker a(&m_mutex);
    if(m_start){
        m_start = false;
        m_thread.terminate();
        m_thread.deleteLater();
        m_thread.wait();
    }

}

bool ImagePlayer::loadImage(std::string filename)
{
    m_outFrame = cv::imread(filename,CV_LOAD_IMAGE_GRAYSCALE);
    if(! m_outFrame.data ){
        m_loadFlag=false;
        return false;
    }
    m_loadFlag=true;
    emit outputImage(m_outFrame);
    return true;
}

void ImagePlayer::msleep(int ms)
{
    //struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    this->thread()->msleep(ms);//nanosleep(&ts, NULL);
}

int ImagePlayer::getSleepImageTick() const
{
    return m_sleepImageTick;
}

void ImagePlayer::setSleepImageTick(int sleepImageTick)
{
    m_sleepImageTick = sleepImageTick;
}

void ImagePlayer::run()
{
    while(m_start){
        m_mutex.lock();
        if(getSimulationManager()->isRun())
            emit outputVideoStream(m_outFrame);
        else
            emit outputImage(m_outFrame);
        m_mutex.unlock();
        this->msleep(m_sleepImageTick);
    }
}

void ImagePlayer::startInit()
{
    connect(this, SIGNAL(errorSimulation(QString)),getSimulationManager(),SLOT(SimulationError(QString)));
    connect(getSimulationManager(),&SimulationSingleton::startSimulation,this, [this]{
       if(!m_loadFlag){
           emit errorSimulation(tr("Нет загруженного изображения для его последующей обработки!"));
       }else{
           startPlay();
       }
    }, Qt::DirectConnection);
    connect(getSimulationManager(),&SimulationSingleton::stopSimulation,this, [this]{
           stopPlay();
    }, Qt::DirectConnection);
}

bool ImagePlayer::getLoadFlag() const
{
    return m_loadFlag;
}

bool ImagePlayer::isStart() const
{
    return m_start;
}

void ImagePlayer::startPlay()
{
    m_start = true;
    m_thread.start();
}

void ImagePlayer::stopPlay()
{
    m_start = false;
    m_thread.terminate();
}

