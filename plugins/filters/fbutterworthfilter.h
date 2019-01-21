#ifndef FBUTTERWORTHFILTER_H
#define FBUTTERWORTHFILTER_H

#include "commonprocessing.h"
#include <QMutex>

class FButterworthFilter : public CommonProcessing
{
    Q_OBJECT
public:
    FButterworthFilter(QObject *parent = 0);
    ~FButterworthFilter();

    double width() const;
    void setWidth(double width);

    bool inverseFlag() const;
    void setInverseFlag(bool inverseFlag);

    int order() const;
    void setOrder(int order);

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
    double m_width = 20;
    int m_order = 3;
    bool m_inverseFlag=false;
};

#endif // FBUTTERWORTHFILTER_H
