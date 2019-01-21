#ifndef ROIPROCESSING_H
#define ROIPROCESSING_H

#include "commonprocessing.h"
#include <QMutex>

class ROIProcessing : public CommonProcessing
{
    Q_OBJECT
public:
    explicit ROIProcessing(QObject *parent = 0);
    ~ROIProcessing();

    std::pair<int, int> topAngle() const;
    std::pair<int, int> bottomAngle() const;
    void setTopX(int x);
    void setTopY(int y);
    void setBottomX(int x);
    void setBottomY(int y);

    virtual void setModuleParameter(const QJsonObject &param);
    virtual void getModuleParameter(QJsonObject &param);
signals:
    void onChangedSizeImage();

public slots:
    /*!
     * \brief Переопределенный метод от CommonProcessing.
     * Отвечает за реализацию процесса обработки входного кадра видеоряда
     * \param frame - входной кадр
     */
    void intputVideoStream(const cv::Mat& frame);

private:
    std::pair<int,int> m_topAngle;
    std::pair<int,int> m_bottomAngle;
    cv::Size m_inputImageSize;

};

#endif // ROIPROCESSING_H
