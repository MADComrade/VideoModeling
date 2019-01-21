#include "perspectivewidget.h"

#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDoubleSpinBox>

#include "perspectivetransformations.h"

PerspectiveWidget::PerspectiveWidget(PerspectiveTransformations *perspective, QWidget *parent)
    : CommonTransformWidget(parent),
      m_perspectiveTr(perspective)
{
    m_bottomRightX= new QDoubleSpinBox(this);
    m_bottomRightX->setRange(0,1);
    m_bottomRightX->setSingleStep(0.05);

    m_bottomRightY= new QDoubleSpinBox(this);
    m_bottomRightY->setRange(0,1);
    m_bottomRightY->setSingleStep(0.05);

    QVBoxLayout* linkage = new QVBoxLayout();
    linkage->addItem(m_topLeftLayout);
    linkage->addItem(m_topRightLayout);

    QLabel*  bottomLeft = new QLabel(tr("Bottom Left"),this);
    QHBoxLayout* m_bottomLayout = new QHBoxLayout;
    QLabel* x = new QLabel(tr(" X = "),this);
    x->setAlignment(Qt::AlignRight);
    QLabel* y = new QLabel(tr(" Y = "),this);
    y->setAlignment(Qt::AlignRight);
    m_bottomLayout->addWidget(bottomLeft);
    m_bottomLayout->addWidget(x);
    m_bottomLayout->addWidget(m_bottomX);
    m_bottomLayout->addWidget(y);
    m_bottomLayout->addWidget(m_bottomY);

    QLabel*  bottomRight = new QLabel(tr("Bottom Right"),this);
    QHBoxLayout* m_bottomRightLayout = new QHBoxLayout;
    x = new QLabel(tr(" X = "),this);
    x->setAlignment(Qt::AlignRight);
    y = new QLabel(tr(" Y = "),this);
    y->setAlignment(Qt::AlignRight);
    m_bottomRightLayout->addWidget(bottomRight);
    m_bottomRightLayout->addWidget(x);
    m_bottomRightLayout->addWidget(m_bottomRightX);
    m_bottomRightLayout->addWidget(y);
    m_bottomRightLayout->addWidget(m_bottomRightY);

    linkage->addItem(m_bottomLayout);
    linkage->addItem(m_bottomRightLayout);
    linkage->addItem(m_flagLayout);
    linkage->addItem(m_borderModeLayout);

    m_topLeftX->setValue(m_perspectiveTr->getTopLeftX());
    m_topLeftY->setValue(m_perspectiveTr->getTopLeftY());
    m_topRightX->setValue(m_perspectiveTr->getTopRightX());
    m_topRightY->setValue(m_perspectiveTr->getTopRightY());
    m_bottomX->setValue(m_perspectiveTr->getBottomLeftX());
    m_bottomY->setValue(m_perspectiveTr->getBottomLeftY());
    m_bottomRightX->setValue(m_perspectiveTr->getBottomRightX());
    m_bottomRightY->setValue(m_perspectiveTr->getBottomRightY());

    m_flagBox->addItems(m_perspectiveTr->getFlagList());
    m_flagBox->setCurrentIndex(m_perspectiveTr->getFlagIndex());

    m_borderModeBox->addItems(m_perspectiveTr->getBorderModeList());
    m_borderModeBox->setCurrentIndex(m_perspectiveTr->getBorderModeIndex());

    QWidget* itemWidget = new QWidget;
    itemWidget->setLayout(linkage);
    setSettingsWidget(itemWidget);

    setWindowTitle(tr("Перспективная трансформация"));

    connect(m_flagBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),
        [=](int index){ m_perspectiveTr->setFlagIndex(index);});
    connect(m_borderModeBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::activated),
        [=](int index){ m_perspectiveTr->setBorderModeIndex(index);});
    connect(m_topLeftX, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_perspectiveTr->setTopLeftX(d); });
    connect(m_topLeftY, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_perspectiveTr->setTopLeftY(d); });
    connect(m_topRightX, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_perspectiveTr->setTopRightX(d); });
    connect(m_topRightY, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_perspectiveTr->setTopRightY(d); });
    connect(m_bottomX, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_perspectiveTr->setBottomLeftX(d); });
    connect(m_bottomY, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_perspectiveTr->setBottomLeftY(d); });
    connect(m_bottomRightX, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_perspectiveTr->setBottomRightX(d); });
    connect(m_bottomRightY, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_perspectiveTr->setBottomRightY(d); });
    connect(m_perspectiveTr,SIGNAL(outputVideoStream(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));

}
