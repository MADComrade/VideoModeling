#include "affinewidget.h"

#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDoubleSpinBox>

#include "affinetransformations.h"

AffineWidget::AffineWidget(AffineTransformations *affine, QWidget *parent)
    : CommonTransformWidget(parent),
      m_affineTrans(affine)
{
    QVBoxLayout* linkage = new QVBoxLayout();
    linkage->addItem(m_topLeftLayout);
    linkage->addItem(m_topRightLayout);

    QLabel*  bottom = new QLabel(tr("Bottom"),this);
    QHBoxLayout* m_bottomLayout = new QHBoxLayout;
    QLabel* x = new QLabel(tr(" X = "),this);
    x->setAlignment(Qt::AlignRight);
    QLabel* y = new QLabel(tr(" Y = "),this);
    y->setAlignment(Qt::AlignRight);
    m_bottomLayout->addWidget(bottom);
    m_bottomLayout->addWidget(x);
    m_bottomLayout->addWidget(m_bottomX);
    m_bottomLayout->addWidget(y);
    m_bottomLayout->addWidget(m_bottomY);

    linkage->addItem(m_bottomLayout);
    linkage->addItem(m_flagLayout);
    linkage->addItem(m_borderModeLayout);

    m_topLeftX->setValue(m_affineTrans->getTopLeftX());
    m_topLeftY->setValue(m_affineTrans->getTopLeftY());
    m_topRightX->setValue(m_affineTrans->getTopRightX());
    m_topRightY->setValue(m_affineTrans->getTopRightY());
    m_bottomX->setValue(m_affineTrans->getBottomX());
    m_bottomY->setValue(m_affineTrans->getBottomY());

    m_flagBox->addItems(m_affineTrans->getFlagList());
    m_flagBox->setCurrentIndex(m_affineTrans->getFlagIndex());

    m_borderModeBox->addItems(m_affineTrans->getBorderModeList());
    m_borderModeBox->setCurrentIndex(m_affineTrans->getBorderModeIndex());

    QWidget* itemWidget = new QWidget;
    itemWidget->setLayout(linkage);
    setSettingsWidget(itemWidget);

    setWindowTitle(tr("Афинные преобразования"));

    connect(m_flagBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),
        [=](int index){ m_affineTrans->setFlagIndex(index);});
    connect(m_borderModeBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),
        [=](int index){ m_affineTrans->setBorderModeIndex(index);});
    connect(m_topLeftX, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_affineTrans->setTopLeftX(d); });
    connect(m_topLeftY, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_affineTrans->setTopLeftY(d); });
    connect(m_topRightX, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_affineTrans->setTopRightX(d); });
    connect(m_topRightY, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_affineTrans->setTopRightY(d); });
    connect(m_bottomX, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_affineTrans->setBottomX(d); });
    connect(m_bottomY, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_affineTrans->setBottomY(d); });
    connect(m_affineTrans,SIGNAL(outputVideoStream(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));

}
