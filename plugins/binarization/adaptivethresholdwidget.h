#ifndef ADAPTIVETHRESHOLDWIDGET_H
#define ADAPTIVETHRESHOLDWIDGET_H

#include "baseprocessingwidget.h"

class QSlider;
class QLabel;
class QComboBox;
class AdaptiveThresholdProcessing;

class AdaptiveThresholdWidget : public BaseProcessingWidget
{
    Q_OBJECT
public:
    AdaptiveThresholdWidget(AdaptiveThresholdProcessing* processingLevel,QWidget *parent = 0);
    ~AdaptiveThresholdWidget(){}

public slots:
    void onChangedMax(int i); /// изменение верхнего порога бинаризации
    void onChangedParamConstant(int i);
    void onChangedKernel(int i);
    void onChangedAdaptiveMethod(int i);
    void onChangedThresholdType(int i);

private:
    QSlider* m_paramConstantSlider;
    QSlider* m_maxSlider;
    QLabel* m_paramConstantText;
    QLabel* m_maxText;
    QComboBox* m_switchKernel;
    QComboBox* m_switchAdaptiveMethod;
    QComboBox* m_switchThresholdType;
    AdaptiveThresholdProcessing* m_processingLevel;
    double m_constant;
    const double m_paramConstantCoeff = 100;
};

#endif // ADAPTIVETHRESHOLDWIDGET_H
