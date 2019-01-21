#ifndef SCALEPROCESSING_H
#define SCALEPROCESSING_H

#include "commonprocessing.h"
#include <QMutex>

class ScaleProcessing : public CommonProcessing
{
    Q_OBJECT
public:
    ScaleProcessing(QObject *parent = 0);
    ~ScaleProcessing();

    double scaleValue() const;
    void setScaleValue(double scaleValue);

    virtual void setModuleParameter(const QJsonObject &param);
    virtual void getModuleParameter(QJsonObject &param);
signals:

public slots:
    /*!
     * \brief Переопределенный метод от CommonProcessing.
     * Отвечает за реализацию процесса обработки входного кадра видеоряда
     * \param frame - входной кадр
     */
    void intputVideoStream(const cv::Mat& frame);

private:
    /// <summary>
    /// Scales the specified source.
    /// </summary>
    /// <param name="src">The source.</param>
    /// <param name="dst">The destination.</param>
    /// <param name="f">The f.</param>
    /// <param name="intensity">The intensity.</param>
    void scale(const cv::Mat& src, cv::Mat& dst, double f = 1.0, cv::Scalar intensity = cv::Scalar());

    /// <summary>
    /// Scales the specified source.
    /// </summary>
    /// <param name="src">The source.</param>
    /// <param name="dst">The destination.</param>
    /// <param name="cx">The cx.</param>
    /// <param name="cy">The cy.</param>
    /// <param name="intensity">The intensity.</param>
    void scale(const cv::Mat& src, cv::Mat& dst, double cx, double cy, cv::Scalar intensity = cv::Scalar());

    double m_scaleValue=1;
};

#endif // SCALEPROCESSING_H
