#ifndef GAUSSIANNOISEWIDGET_H
#define GAUSSIANNOISEWIDGET_H

#include "baseprocessingwidget.h"

class QLabel;
class QDoubleSpinBox;
class QHBoxLayout;
class GaussianNoiseProcessing;


class GaussianNoiseWidget : public BaseProcessingWidget
{
    Q_OBJECT
public:
    GaussianNoiseWidget(GaussianNoiseProcessing* processing, QWidget *parent = 0);
    ~GaussianNoiseWidget();

private:
    GaussianNoiseProcessing* m_processing;
    QDoubleSpinBox* m_mean;
    QDoubleSpinBox* m_sigma;
};

#endif // GAUSSIANNOISEWIDGET_H
