#ifndef THRESHOLDWIDGET_H
#define THRESHOLDWIDGET_H

#include "baseprocessingwidget.h"

class QSlider;
class QLabel;
class QComboBox;
class ThresholdProcessing;

/*!
 * \brief Класс описывающий виджет настройки блока бинаризации
 */
class ThresholdWidget : public BaseProcessingWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Конструктор
     * \param processing - указатель на класс реализующий бинаризацию изображения
     * \param parent
     */
    ThresholdWidget(ThresholdProcessing* processing, QWidget *parent = 0);
    ~ThresholdWidget();

signals:

public slots:
    void onChangedMax(int i); /// изменение верхнего порога бинаризации
    void onChangedMin(int i); /// изменение нижнего порога бинаризации
    void onChangedProcessing(int i); /// изменение типа бинаризации

private:
    QSlider* m_minSlider;
    QSlider* m_maxSlider;
    QLabel* m_minText;
    QLabel* m_maxText;
    QComboBox* m_switchProcessing;
    ThresholdProcessing* m_processing;

};

#endif // THRESHOLDWIDGET_H
