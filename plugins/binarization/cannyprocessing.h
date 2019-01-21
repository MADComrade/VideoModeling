#ifndef CANNYPROCESSING_H
#define CANNYPROCESSING_H

#include "commonprocessing.h"
#include <QMutex>

class CannyProcessing : public CommonProcessing
{
    Q_OBJECT
public:
    CannyProcessing(QObject *parent = 0);
    ~CannyProcessing();

    int minThreshold() const;
    void setMinThreshold(int minThreshold);

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
    int m_minThreshold=20;
    int m_ratio = 3;
    int m_kernelSize = 3;
};

#endif // CANNYPROCESSING_H
