#ifndef ADAPTIVETHRESHOLDPROCESSING_H
#define ADAPTIVETHRESHOLDPROCESSING_H

#include "commonprocessing.h"
#include <QMutex>

class AdaptiveThresholdProcessing : public CommonProcessing
{
    Q_OBJECT
public:
    AdaptiveThresholdProcessing(QObject *parent = 0);
    ~AdaptiveThresholdProcessing();

    int maxThreshold() const;
    void setMaxThreshold(int maxThreshold);

    int getIdThresholdType() const;
    void setIdThresholdType(int idThresholdType);

    QStringList getThresholTypesList() const;

    int getIdAdaptiveType() const;
    void setIdAdaptiveType(int value);

    QStringList getAdaptiveTypesList() const;

    int getKernelIndex() const;
    void setKernelIndex(int kernelIndex);

    QStringList getKernelList() const;

    double getParamConstant() const;
    void setParamConstant(double paramConstant);

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
    int m_maxThreshold=255;
    int m_idThresholdType=0;
    QStringList m_thresholTypesList;
    QList<int> m_thresholTypeValues;
    int m_idAdaptiveType=0;
    QStringList m_adaptiveTypesList;
    QList<int> m_adaptiveTypeValues;
    int m_kernelIndex=0;
    QStringList m_kernelList;
    QList<int> m_kernelValueList;
    double m_paramConstant=5;
    int m_kernelValue=3;
};

#endif // ADAPTIVETHRESHOLDPROCESSING_H
