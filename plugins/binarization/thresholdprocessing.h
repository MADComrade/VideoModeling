#ifndef THRESHOLDPRICESSING_H
#define THRESHOLDPRICESSING_H

#include "commonprocessing.h"
#include <QMutex>

/*!
 * \brief Класс бинаризации изображения
 */
class ThresholdProcessing : public CommonProcessing
{
    Q_OBJECT
public:
    ThresholdProcessing(QObject *parent = 0);
    ~ThresholdProcessing();

    /*!
     * \return значение верхнего порога
     */
    int maxThreshold() const;
    /*!
     * \brief Установка значения верхнего порога
     * \param maxThreshold
     */
    void setMaxThreshold(int maxThreshold);

    /*!
     * \return Значение нижнего порога
     */
    int minThreshold() const;
    /*!
     * \brief Установка значения нижнего порога
     * \param minThreshold
     */
    void setMinThreshold(int minThreshold);

    /*!
     * \return Список способов бинаризации
     */
    QStringList processingTypesList() const;

    /*!
     * \return Индекс выбранного способа бинаризации
     */
    int typeIndex() const;
    /*!
     * \brief Установка индекса выбранного способа бинаризации
     * \param typeIndex
     */
    void setTypeIndex(int typeIndex);

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
    int m_minThreshold=0;
    int m_typeIndex=0;
    QStringList m_processingTypesList;
    QList<int> m_TypesValue;

};

#endif // THRESHOLDPRICESSING_H
