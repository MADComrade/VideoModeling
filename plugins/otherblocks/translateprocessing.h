#ifndef TRANSLATEPROCESSING_H
#define TRANSLATEPROCESSING_H

#include "commonprocessing.h"
#include <QMutex>

class TranslateProcessing : public CommonProcessing
{
    Q_OBJECT
public:
    TranslateProcessing(QObject *parent = 0);
    ~TranslateProcessing();

    int dX() const;
    void setDX(int dX);

    int dY() const;
    void setDY(int dY);

    cv::Size inputImageSize() const;

    virtual void setModuleParameter(const QJsonObject &param);
    virtual void getModuleParameter(QJsonObject &param);
signals:
    void onChangedWidth(int w);
    void onChangedHeight(int h);

public slots:
    /*!
     * \brief Переопределенный метод от CommonProcessing.
     * Отвечает за реализацию процесса обработки входного кадра видеоряда
     * \param frame - входной кадр
     */
    void intputVideoStream(const cv::Mat& frame);

private:
    void translate(const cv::Mat& src, cv::Mat& dst, float dx, float dy, cv::Scalar intensity = cv::Scalar());
    int m_dX=0;
    int m_dY=0;

    cv::Size m_inputImageSize;//(0,0);
};

#endif // TRANSLATEPROCESSING_H
