#ifndef FIDEALFILTER_H
#define FIDEALFILTER_H

#include "commonprocessing.h"
#include <QMutex>

class FIdealFilter : public CommonProcessing
{
    Q_OBJECT
public:
    FIdealFilter(QObject *parent = 0);
    ~FIdealFilter();

    bool getInverseFlag() const;
    void setInverseFlag(bool inverseFlag);

    double getWidth() const;
    void setWidth(double width);

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

    double m_width = 50;
    bool m_inverseFlag=false;
};

#endif // FIDEALFILTER_H
