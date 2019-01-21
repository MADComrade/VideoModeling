#ifndef WEBCAMPLAYER_H
#define WEBCAMPLAYER_H

#include "commonprocessing.h"
#include <QThread>
#include <QMutex>
#include <QObject>

class WebCamPlayer : public CommonProcessing
{
    Q_OBJECT
public:
    WebCamPlayer(QObject *parent = 0);
    ~WebCamPlayer();

    bool isStart() const;
    void startPlay();
    void stopPlay();

    int getSleepImageTick() const;
    void setSleepImageTick(int sleepImageTick);

    QStringList getAvailableCameras() const;
    void setIdCamSelect(int idCam);
    int getIdCam();

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
    int m_sleepImageTick=300;
    int m_idCam {-1};
};

#endif // WEBCAMPLAYER_H
