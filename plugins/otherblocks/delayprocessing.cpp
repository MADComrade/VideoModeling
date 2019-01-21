#include "delayprocessing.h"
#include "blockenums.h"
#include "moduleconfig.h"

using namespace std;
DelayProcessing::DelayProcessing(QObject *parent)
    : CommonProcessing(parent)
{
    setBlockProcessingName("Delay");
    setBlockProcessing(CONFUGUATOR::BlockProcessing::Transformations);
    setModuleType(BLOCKSTYPE::ModuleType::Delay);

    //m_temp.resize(300);
    m_state = STATE_DELAY::Stop;
    m_timeDelay = new QTimer(this);
    m_timeDelay->setInterval(m_delay);
    connect(m_timeDelay,SIGNAL(timeout()),this,SLOT(timerTick()));
}

DelayProcessing::~DelayProcessing()
{
    QMutexLocker lock(&m_mutex);
}

void DelayProcessing::setModuleParameter(const QJsonObject &param)
{
    m_delay = param["Delay"].toInt();
}

void DelayProcessing::getModuleParameter(QJsonObject &param)
{
    param["Delay"] = m_delay;
}

int DelayProcessing::getDelayImageTick() const
{
    return m_delay;
}

void DelayProcessing::setDelayImageTick(int delayImageTick)
{
    QMutexLocker lock(&m_mutex);
    m_timeDelay->setInterval(abs(delayImageTick - m_delay));
    m_delay = delayImageTick;
    m_state = STATE_DELAY::Stop;
    m_timeDelay->start();

}

void DelayProcessing::intputVideoStream(const cv::Mat &frame)
{
    QMutexLocker lock(&m_mutex);
    if(m_temp.empty()){
        m_state = STATE_DELAY::Stop;
        m_timeDelay->start();        
    }
    m_temp.push_back(frame.clone());
    if(m_state == STATE_DELAY::Start){

        m_state = STATE_DELAY::Stop;
    }
}

void DelayProcessing::timerTick()
{
    m_state = STATE_DELAY::Start;
    m_timeDelay->setInterval(m_delay);
    if(!m_temp.empty()){
        m_outFrame = m_temp[0];
        m_temp.pop_front();
        emit outputVideoStream(m_outFrame);
    }

}
