#ifndef SCALEWIDGET_H
#define SCALEWIDGET_H

#include "baseprocessingwidget.h"

class ScaleProcessing;

class ScaleWidget : public BaseProcessingWidget
{
    Q_OBJECT
public:
    ScaleWidget(ScaleProcessing* processing, QWidget *parent = 0);
    ~ScaleWidget(){}

private:
    ScaleProcessing* m_processing;
};

#endif // SCALEWIDGET_H
