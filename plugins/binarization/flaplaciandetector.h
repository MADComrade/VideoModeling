#ifndef FLAPLACIANDETECTOR_H
#define FLAPLACIANDETECTOR_H

#include "commonprocessing.h"
#include <QMutex>


class FLaplacianDetector : public CommonProcessing
{
    Q_OBJECT
public:
    FLaplacianDetector(QObject *parent = 0);
    ~FLaplacianDetector();

    bool processingFlag() const;
    void setProcessingFlag(bool processingFlag);

    int scale() const;
    void setScale(int scale);

    int delta() const;
    void setDelta(int delta);

    virtual void setModuleParameter(const QJsonObject &param);
    virtual void getModuleParameter(QJsonObject &param);

public slots:
    /*!
     * \brief Переопределенный метод от CommonProcessing.
     * Отвечает за реализацию процесса обработки входного кадра видеоряда
     * \param frame - входной кадр
     */
    void intputVideoStream(const cv::Mat& frame);

private:
    bool m_processingFlag=false;
    int m_kernelSize = 3;
    int m_scale = 1;
    int m_delta = 0;
};

#endif // FLAPLACIANDETECTOR_H
