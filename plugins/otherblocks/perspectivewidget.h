#ifndef PERSPECTIVEWIDGET_H
#define PERSPECTIVEWIDGET_H

#include "commontransformwidget.h"

class QSlider;
class QLabel;
class QComboBox;
class QDoubleSpinBox;
class QHBoxLayout;
class PerspectiveTransformations;

class PerspectiveWidget : public CommonTransformWidget
{
    Q_OBJECT
public:
    PerspectiveWidget(PerspectiveTransformations* perspective, QWidget *parent = 0);
    ~PerspectiveWidget(){}

private:
    QDoubleSpinBox* m_bottomRightX;
    QDoubleSpinBox* m_bottomRightY;
    PerspectiveTransformations* m_perspectiveTr;
};

#endif // PERSPECTIVEWIDGET_H
