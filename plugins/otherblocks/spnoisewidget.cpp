#include "spnoisewidget.h"
#include "spnoiseprocessing.h"

#include <QLabel>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

SPNoiseWidget::SPNoiseWidget(SPNoiseProcessing *processing, QWidget *parent):
    BaseProcessingWidget(parent), m_processing(processing)
{
    QHBoxLayout* procLayout = new QHBoxLayout();
    QVBoxLayout* linkage = new QVBoxLayout();
    m_black = new QDoubleSpinBox(this);
    m_white = new QDoubleSpinBox(this);

    m_black->setRange(0,1);
    m_white->setRange(0,1);
    m_black->setSingleStep(0.02);
    m_white->setSingleStep(0.02);
    QLabel* meanText = new QLabel(tr(" Mean = "),this);
    meanText->setAlignment(Qt::AlignCenter);
    QLabel* sigmaText = new QLabel(tr(" Sigma = "),this);
    sigmaText->setAlignment(Qt::AlignCenter);

    m_black->setValue(m_processing->getBlack());
    m_white->setValue(m_processing->getWhite());

    procLayout->addWidget(meanText);
    procLayout->addWidget(m_black);
    procLayout->addWidget(sigmaText);
    procLayout->addWidget(m_white);
    linkage->addItem(procLayout);

    QWidget* itemWidget = new QWidget;
    itemWidget->setLayout(linkage);
    setSettingsWidget(itemWidget);
    connect(m_processing,SIGNAL(outputVideoStream(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));
    setTitleWidget("Salt and Paper Noise");

    connect(m_black, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_processing->setBlack(d); });
    connect(m_white, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_processing->setWhite(d); });

}
