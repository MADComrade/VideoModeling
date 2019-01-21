#ifndef AFFINEWIDGET_H
#define AFFINEWIDGET_H

#include "commontransformwidget.h"

class QSlider;
class QLabel;
class QComboBox;
class QDoubleSpinBox;
class QHBoxLayout;
class AffineTransformations;

class AffineWidget : public CommonTransformWidget
{
    Q_OBJECT
public:
    AffineWidget(AffineTransformations* affine, QWidget *parent = 0);
    ~AffineWidget(){}

signals:

public slots:
private:
    AffineTransformations* m_affineTrans;


};

#endif // AFFINEWIDGET_H
