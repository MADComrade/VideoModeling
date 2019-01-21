#ifndef ROTATEPROCESSING_H
#define ROTATEPROCESSING_H

#include "commonprocessing.h"
#include <QMutex>

class RotateProcessing : public CommonProcessing
{
     Q_OBJECT
public:
    RotateProcessing(QObject *parent = 0);
    ~RotateProcessing();


    int xCenter() const;
    void setXCenter(int xCenter);

    int yCenter() const;
    void setYCenter(int yCenter);

    double scale() const;
    void setScale(double scale);

    double angle() const;
    void setAngle(double angle);

    cv::Size inputImageSize() const;
    void setInputImageSize(const cv::Size &inputImageSize);

    virtual void setModuleParameter(const QJsonObject &param);
    virtual void getModuleParameter(QJsonObject &param);

public slots:
    /*!
     * \brief Переопределенный метод от CommonProcessing.
     * Отвечает за реализацию процесса обработки входного кадра видеоряда
     * \param frame - входной кадр
     */
    void intputVideoStream(const cv::Mat& frame);

signals:
    void onChangedWidth(int w);
    void onChangedHeight(int h);

private:
    void rotate(const cv::Mat& src, cv::Mat& dst, double angle, cv::Point2f center, double scale = 1.0, cv::Scalar intensity = cv::Scalar());

    int m_xCenter=0;
    int m_yCenter=0;

    cv::Size m_inputImageSize;//(0,0);

    double m_scale=1;
    double m_angle=0;
};

#endif // ROTATEPROCESSING_H
