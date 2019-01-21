#ifndef PARAMVIDEOINPUT_H
#define PARAMVIDEOINPUT_H

#include "commonprocessing.h"
#include "QThread"
#include <QMutex>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

class ParamVideoInput : public CommonProcessing
{
    Q_OBJECT
public:
    ParamVideoInput(QObject *parent = 0);
    ~ParamVideoInput();

    bool isStart() const;
    bool loadVideo(std::string filename);
    void startPlay();
    void stopPlay();

    bool getLoadFlag() const;

    int getSleepImageTick() const;
    void setSleepImageTick(int sleepImageTick);

    void setCurrentFrame( int frameNumber);
    /*!
     * \brief Количество кадров в секунду в текущем видеофайле
     * \return fps
     */
    double getFrameRate();
    /*!
     * \return Номер текущего проигрываемого кадра
     */
    double getCurrentFrame();
    /*!
     * \brief getNumberOfFrames
     * \return Номер последнего кадра в видеофайле
     */
    double getNumberOfFrames();

private slots:
    void run();

signals:
    void errorSimulation(const QString& error);
    void outputImage(const cv::Mat& frame); /// выходной видеокадр

private:

    void startInit();

    void msleep(int ms);
    void deleteCapture();
    QThread* m_thread;
    QMutex m_mutex;
    bool m_start=false;
    bool m_loadFlag=false;
    int m_sleepImageTick=5000;
    int m_frameRate;
    cv::VideoCapture * m_capture;
};

#endif // PARAMVIDEOINPUT_H
