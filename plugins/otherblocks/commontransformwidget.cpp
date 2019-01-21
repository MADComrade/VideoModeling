#include "commontransformwidget.h"

#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDoubleSpinBox>

CommonTransformWidget::CommonTransformWidget(QWidget *parent)
    : BaseProcessingWidget(parent)
{
    m_topLeftX = new QDoubleSpinBox(this);
    m_topLeftX->setRange(0,1);
    m_topLeftX->setSingleStep(0.05);

    m_topLeftY = new QDoubleSpinBox(this);
    m_topLeftY->setRange(0,1);
    m_topLeftY->setSingleStep(0.05);

    m_topRightX = new QDoubleSpinBox(this);
    m_topRightX->setRange(0,1);
    m_topRightX->setSingleStep(0.05);

    m_topRightY = new QDoubleSpinBox(this);
    m_topRightY->setRange(0,1);
    m_topRightY->setSingleStep(0.05);

    m_bottomX = new QDoubleSpinBox(this);
    m_bottomX->setRange(0,1);
    m_bottomX->setSingleStep(0.05);

    m_bottomY = new QDoubleSpinBox(this);
    m_bottomY->setRange(0,1);
    m_bottomY->setSingleStep(0.05);

    QLabel*  left = new QLabel(tr("Top Left"),this);
    QLabel*  right = new QLabel(tr("Top Right"),this);
    QLabel* x = new QLabel(tr(" X = "),this);
    x->setAlignment(Qt::AlignRight);
    QLabel* y = new QLabel(tr(" Y = "),this);
    y->setAlignment(Qt::AlignRight);

    m_topLeftLayout = new QHBoxLayout;
    m_topLeftLayout->addWidget(left);
    m_topLeftLayout->addWidget(x);
    m_topLeftLayout->addWidget(m_topLeftX);
    m_topLeftLayout->addWidget(y);
    m_topLeftLayout->addWidget(m_topLeftY);

    x = new QLabel(tr(" X = "),this);
    x->setAlignment(Qt::AlignRight);
    y = new QLabel(tr(" Y = "),this);
    y->setAlignment(Qt::AlignRight);
    m_topRightLayout = new QHBoxLayout;
    m_topRightLayout->addWidget(right);
    m_topRightLayout->addWidget(x);
    m_topRightLayout->addWidget(m_topRightX);
    m_topRightLayout->addWidget(y);
    m_topRightLayout->addWidget(m_topRightY);

    m_flagBox = new QComboBox(this);
    m_borderModeBox = new QComboBox(this);

    m_flagLayout = new QHBoxLayout;
    QLabel*  flag = new QLabel(tr("Интерполяция"),this);
    m_flagLayout->addWidget(flag);
    m_flagLayout->addWidget(m_flagBox);

    m_borderModeLayout = new QHBoxLayout;
    QLabel*  borderMode = new QLabel(tr("Экстраполяция"),this);
    m_borderModeLayout->addWidget(borderMode);
    m_borderModeLayout->addWidget(m_borderModeBox);
}
