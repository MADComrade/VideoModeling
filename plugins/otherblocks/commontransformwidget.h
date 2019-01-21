#ifndef COMMONTRANSFORMWIDGET_H
#define COMMONTRANSFORMWIDGET_H

#include "baseprocessingwidget.h"

class QSlider;
class QLabel;
class QComboBox;
class QDoubleSpinBox;
class QHBoxLayout;

class CommonTransformWidget : public BaseProcessingWidget
{
    Q_OBJECT
public:
    CommonTransformWidget(QWidget *parent = 0);
    ~CommonTransformWidget(){}

protected slots:

protected:
    QDoubleSpinBox* m_topLeftX;
    QDoubleSpinBox* m_topLeftY;
    QDoubleSpinBox* m_topRightX;
    QDoubleSpinBox* m_topRightY;
    QDoubleSpinBox* m_bottomX;
    QDoubleSpinBox* m_bottomY;

    QComboBox* m_flagBox;
    QComboBox* m_borderModeBox;
    QHBoxLayout* m_topLeftLayout;
    QHBoxLayout* m_topRightLayout;
    QHBoxLayout* m_flagLayout;
    QHBoxLayout* m_borderModeLayout;
};

#endif // COMMONTRANSFORMWIDGET_H
