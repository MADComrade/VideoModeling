#ifndef SINGLETONTHREAD_H
#define SINGLETONTHREAD_H

#include <QThread>
#include <QMutex>

class SingletonThread : public QThread
{
    Q_OBJECT
public:
    static SingletonThread* getInstance();
    static void drop();

protected:
    void run();

private:
     SingletonThread(QObject *parent = 0);
    ~SingletonThread(){}

     SingletonThread(SingletonThread const&) = delete;
     SingletonThread& operator= (SingletonThread const&) = delete;

     static QMutex m_mutex;
     static SingletonThread* m_instance;
};
#endif // SINGLETONTHREAD_H
