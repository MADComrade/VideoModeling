#ifndef FGAUSSIANPROCESSING_H
#define FGAUSSIANPROCESSING_H

#include "commonprocessing.h"
#include <QMutex>

class FGaussianProcessing : public CommonProcessing
{
    Q_OBJECT
public:
    FGaussianProcessing(QObject *parent = 0);
    ~FGaussianProcessing();

    double getSigma() const;
    void setSigma(double sigma);

    bool getInverseFlag() const;
    void setInverseFlag(bool inverseFlag);

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
    cv::Mat applyGaussianFilter(cv::Mat src, double sigma = -1.0);
    double m_sigma = 5;
    bool m_inverseFlag=false;
};

#endif // FGAUSSIANPROCESSING_H
