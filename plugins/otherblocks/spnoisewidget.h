#ifndef SPNOISEWIDGET_H
#define SPNOISEWIDGET_H

#include "baseprocessingwidget.h"

class QLabel;
class QDoubleSpinBox;
class QHBoxLayout;
class SPNoiseProcessing;

class SPNoiseWidget : public BaseProcessingWidget
{
    Q_OBJECT
public:
    SPNoiseWidget(SPNoiseProcessing* processing, QWidget *parent = 0);
    ~SPNoiseWidget(){}

private:
    SPNoiseProcessing* m_processing;
    QDoubleSpinBox* m_black;
    QDoubleSpinBox* m_white;
};

#endif // SPNOISEWIDGET_H
