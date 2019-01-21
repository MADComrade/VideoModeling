#ifndef IMAGEPLAYER_H
#define IMAGEPLAYER_H

#include "commonprocessing.h"
#include <QThread>
#include <QMutex>
#include <QObject>

class ImagePlayer : public CommonProcessing
{    
    Q_OBJECT
public:
    ImagePlayer(QObject *parent = 0);
    ~ImagePlayer();

    bool loadImage(std::string filename);
    bool isStart() const;
    void startPlay();
    void stopPlay();

    bool getLoadFlag() const;

    int getSleepImageTick() const;
    void setSleepImageTick(int sleepImageTick);

private slots:
    void run();

signals:
    void errorSimulation(const QString& error);
    void outputImage(const cv::Mat& frame); /// выходной видеокадр

private:
    void startInit();

    void msleep(int ms);
    QThread m_thread;
    QMutex m_mutex;
    bool m_start=false;
    bool m_loadFlag=false;
    int m_sleepImageTick=5000;
};

#endif // IMAGEPLAYER_H
