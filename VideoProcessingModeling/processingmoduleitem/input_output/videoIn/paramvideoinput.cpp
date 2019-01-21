#include "paramvideoinput.h"
#include "moduleconfig.h"
#include "simulationsingleton.h"

ParamVideoInput::ParamVideoInput(QObject *parent)
    : CommonProcessing(parent),
      m_capture(0)
{
    m_thread = new QThread();
    connect(m_thread,SIGNAL(started()),this,SLOT(run()));
    this->moveToThread(m_thread);
    setBlockProcessingName("Video");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::IO);
    setModuleType(CONFUGUATOR::ModuleType::VideoParamIn);
}

ParamVideoInput::~ParamVideoInput()
{
    QMutexLocker locker (&m_mutex);
    m_start = false;
    if(m_capture != 0){
        m_capture->release();
        delete m_capture;
        m_capture = 0;
    }
    m_thread->terminate();
    m_thread->deleteLater();
    m_thread->wait();
    delete m_thread;
}

bool ParamVideoInput::isStart() const
{
    return m_start;
}

bool ParamVideoInput::loadVideo(std::string filename)
{
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

void ParamVideoInput::startPlay()
{
    m_start = true;
    m_thread->start();
}

void ParamVideoInput::stopPlay()
{
    m_start = false;
    m_thread->terminate();
}

bool ParamVideoInput::getLoadFlag() const
{
    return m_loadFlag;
}

void ParamVideoInput::run()
{
    while (m_start) {
        m_mutex.lock();
        if (!m_capture->read(m_frame))
        {
            m_start = false;
            emit errorSimulation(tr("Ошибка чтения текущего кадра!"));
        }
        if (m_frame.channels()== 3){
            cv::cvtColor(m_frame, m_outFrame, CV_BGR2GRAY);
        }
        m_mutex.unlock();
        if(SimulationSingleton::getInstance()->isRun())
            emit outputVideoStream(m_outFrame);
        else
            emit outputImage(m_outFrame);
        this->msleep(m_sleepImageTick);
    }
}

void ParamVideoInput::startInit()
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

void ParamVideoInput::msleep(int ms)
{
//    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
//    nanosleep(&ts, NULL);
    this->thread()->msleep(ms);
}

void ParamVideoInput::deleteCapture()
{
    if(m_capture != 0){
        m_mutex.lock();
        m_capture->release();
        delete m_capture;
        m_capture = 0;
        m_mutex.unlock();
        m_thread->terminate();
    }
}

int ParamVideoInput::getSleepImageTick() const
{
    return m_sleepImageTick;
}

void ParamVideoInput::setSleepImageTick(int sleepImageTick)
{
    m_sleepImageTick = sleepImageTick;
}

void ParamVideoInput::setCurrentFrame(int frameNumber)
{
    QMutexLocker locker (&m_mutex);
    m_capture->set(CV_CAP_PROP_POS_FRAMES, frameNumber);
}

double ParamVideoInput::getFrameRate()
{
    return m_frameRate;
}

double ParamVideoInput::getCurrentFrame()
{
    return m_capture->get(CV_CAP_PROP_POS_FRAMES);
}

double ParamVideoInput::getNumberOfFrames()
{
    return m_capture->get(CV_CAP_PROP_FRAME_COUNT);
}
