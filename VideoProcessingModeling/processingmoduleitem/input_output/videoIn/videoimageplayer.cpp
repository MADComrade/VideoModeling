#include "videoimageplayer.h"
#include <QMutexLocker>
#include "simulationsingleton.h"

VideoImagePlayer::VideoImagePlayer(QObject *parent)
    : QThread(parent),
      m_capture(0)
{
    connect(this, SIGNAL(errorSimulation(QString)),SimulationSingleton::getInstance(),SLOT(SimulationError(QString)));
    connect(SimulationSingleton::getInstance(),&SimulationSingleton::startSimulation,this, [this]{
       if(!m_loadFlag){
           emit errorSimulation(tr("Нет загруженного изображения для его последующей обработки!"));
       }else{
           setPlayState(true);
       }
    });
    connect(SimulationSingleton::getInstance(),&SimulationSingleton::stopSimulation,this, [this]{
           setPlayState(false);
    });
}

VideoImagePlayer::~VideoImagePlayer()
{
    m_mutex.lock();
    m_start=false;
    if(m_capture != 0){
        m_capture->release();
        delete m_capture;
    }
    condition.wakeOne();
    m_mutex.unlock();
    wait();
}

bool VideoImagePlayer::loadVideo(std::string filename)
{
    if(m_workWithVideo){
        deleteCapture();
        m_capture  =  new cv::VideoCapture(filename);

        if (m_capture->isOpened())
        {
            m_frameRate = (int) m_capture->get(CV_CAP_PROP_FPS);
            m_loadFlag=true;
            return true;
        }
        else{
            m_loadFlag=false;
            return false;
        }

    }
    else{
        m_inputImage = cv::imread(filename,CV_LOAD_IMAGE_GRAYSCALE);
        if(! m_inputImage.data ){
            m_loadFlag=false;
            return false;
        }
        m_loadFlag=true;
        return true;
    }
}

bool VideoImagePlayer::isStopped() const
{
    return !m_start;
}

void VideoImagePlayer::setCurrentFrame(int frameNumber)
{
    QMutexLocker locker (&m_mutex);
    m_capture->set(CV_CAP_PROP_POS_FRAMES, frameNumber);
}

double VideoImagePlayer::getFrameRate()
{
    return m_frameRate;
}

double VideoImagePlayer::getCurrentFrame()
{
    return m_capture->get(CV_CAP_PROP_POS_FRAMES);
}

double VideoImagePlayer::getNumberOfFrames()
{
    return m_capture->get(CV_CAP_PROP_FRAME_COUNT);
}

void VideoImagePlayer::setWorkState(bool state)
{
    if(m_workWithVideo != state){
        m_start=false;
        m_loadFlag = false;
        m_workWithVideo = state;
        if(!m_workWithVideo){
            deleteCapture();
        }
    }
}

void VideoImagePlayer::setPlayState(bool state)
{
    m_start = state;
    if(m_start){
        if (!isRunning()) {
            if(m_loadFlag)
                start(LowPriority);
        }
    }
}

bool VideoImagePlayer::getWorkState() const
{
    return m_workWithVideo;
}

bool VideoImagePlayer::getPlayState() const
{
    return m_start;
}

void VideoImagePlayer::run()
{
    if(m_workWithVideo){
        int delay = (1000/m_frameRate);
        while(m_start){
            m_mutex.lock();
            if (!m_capture->read(m_inputImage))
            {
                m_start = false;
            }
            if (m_inputImage.channels()== 3){
                cv::cvtColor(m_inputImage, m_frame, CV_BGR2GRAY);
            }
            m_mutex.unlock();
            if(SimulationSingleton::getInstance()->isRun())
                emit outputVideoStream(m_frame);
            else
                emit outputImage(m_frame);
            this->msleep(delay);
        }
    }else{
        while(m_start){
            if(SimulationSingleton::getInstance()->isRun())
                emit outputVideoStream(m_inputImage);
            else
                emit outputImage(m_frame);
            this->msleep(m_sleepImageTick);
        }
    }
}

void VideoImagePlayer::msleep(int ms)
{
//    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
//    nanosleep(&ts, NULL);
    this->thread()->msleep(ms);
}

void VideoImagePlayer::deleteCapture()
{
    if(m_capture != 0){
        m_mutex.lock();
        m_capture->release();
        delete m_capture;
        m_capture = 0;
        condition.wakeOne();
        m_mutex.unlock();
        wait();
    }
}

int VideoImagePlayer::getSleepImageTick() const
{
    return m_sleepImageTick;
}

void VideoImagePlayer::setSleepImageTick(int sleepImageTick)
{
    m_sleepImageTick = sleepImageTick;
}

bool VideoImagePlayer::getLoadFlag() const
{
    return m_loadFlag;
}

void VideoImagePlayer::setLoadFlag(bool loadFlag)
{
    m_loadFlag = loadFlag;
}
