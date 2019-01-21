#ifndef VIDEOIMAGEPLAYER_H
#define VIDEOIMAGEPLAYER_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/*!
 * \brief Класс отвечающий за входное изображение, которое будет передаваться по цепочке обработки
 */
class VideoImagePlayer : public QThread
{
    Q_OBJECT
public:
    /*!
     * \brief Конструктор по умолчанию
     * \param parent
     */
    VideoImagePlayer(QObject *parent = 0);
    ~VideoImagePlayer();

    /*!
     * \brief Загрузка фото или видеоизображения для последующего проигрывания
     * \param filename - путь до файла
     * \return true если файл успешно открыт, иначе - false
     */
    bool loadVideo(std::string filename);
    /*!
     * \return текущее состояние проигрывателя play/stop
     */
    bool isStopped() const;
    /*!
     * \brief Перемотка к заданному кадру при проигрывании видеоряда
     * \param frameNumber - номер кадра
     */
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

    /*!
     * \brief Задание режима работы: работа с видео (true) или изображением (false)
     * \param state
     */
    void setWorkState(bool state);
    /*!
     * \brief getWorkState
     * \return текущий режим работы
     */
    bool getWorkState() const;

    /*!
     * \brief Установка состояния проигрывателя
     * \param state - play(true)/stop(false)
     */
    void setPlayState(bool state);
    /*!
     * \brief getPlayState
     * \return состояниt проигрывателя play(true)/stop(false)
     */
    bool getPlayState() const;

    /*!
     * \brief getLoadFlag
     * \return флаг загрузки файла для проигрывания
     */
    bool getLoadFlag() const;
    void setLoadFlag(bool loadFlag);

    /*!
     * \brief getSleepImageTick
     * \return текущее время задержки при проигрывании изображений
     */
    int getSleepImageTick() const;
    /*!
     * \brief Установка текущего времи задержки при проигрывании изображений
     * \param sleepImageTick
     */
    void setSleepImageTick(int sleepImageTick);

signals:
    void outputVideoStream(const cv::Mat& frame); /// выходное изображение
    void errorSimulation(const QString& error);
    void outputImage(const cv::Mat& frame); /// выходной видеокадр

protected:
    void run();
    void msleep(int ms);

private:
   void deleteCapture();
   QMutex m_mutex;
   QWaitCondition condition;
   cv::Mat m_frame;
   int m_frameRate;
   cv::VideoCapture * m_capture;
   cv::Mat m_inputImage;

   bool m_workWithVideo = true;
   bool m_start=false;
   bool m_loadFlag=false;
   int m_sleepImageTick=5000;
};

#endif // VIDEOIMAGEPLAYER_H
