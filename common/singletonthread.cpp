#include "singletonthread.h"
#include "opencv2/core.hpp"
SingletonThread* SingletonThread::m_instance=0;
QMutex SingletonThread::m_mutex;

SingletonThread *SingletonThread::getInstance()
{
    m_mutex.lock();
    if(!m_instance){
        m_instance = new SingletonThread();
        //qRegisterMetaType< cv::Mat >("cv::Mat");
    }
    m_mutex.unlock();
    return m_instance;
}

void SingletonThread::drop()
{
    m_mutex.lock();
    m_instance->terminate();
    m_instance->wait();
    delete m_instance;
    m_instance = 0;
    m_mutex.unlock();
}

void SingletonThread::run()
{
    this->exec();
}

SingletonThread::SingletonThread(QObject *parent)
    : QThread(parent)
{

}
