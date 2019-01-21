#include "gaussiannoisewidget.h"
#include <QLabel>
#include <QDoubleSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "gaussiannoiseprocessing.h"

GaussianNoiseWidget::GaussianNoiseWidget(GaussianNoiseProcessing* processing, QWidget *parent):
    BaseProcessingWidget(parent), m_processing(processing)
{
    QHBoxLayout* procLayout = new QHBoxLayout();
    QVBoxLayout* linkage = new QVBoxLayout();
    m_mean = new QDoubleSpinBox(this);
    m_sigma = new QDoubleSpinBox(this);

    m_mean->setMaximum(255);
    m_sigma->setMaximum(180);
    QLabel* meanText = new QLabel(tr(" Mean = "),this);
    meanText->setAlignment(Qt::AlignCenter);
    QLabel* sigmaText = new QLabel(tr(" Sigma = "),this);
    sigmaText->setAlignment(Qt::AlignCenter);

    m_mean->setValue(m_processing->getMean());
    m_sigma->setValue(m_processing->getSigma());

    procLayout->addWidget(meanText);
    procLayout->addWidget(m_mean);
    procLayout->addWidget(sigmaText);
    procLayout->addWidget(m_sigma);
    linkage->addItem(procLayout);

    QWidget* itemWidget = new QWidget;
    itemWidget->setLayout(linkage);
    setSettingsWidget(itemWidget);
    connect(m_processing,SIGNAL(outputVideoStream(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));
    setTitleWidget("Gaussian Noise");

    connect(m_mean, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_processing->setMean(d); });
    connect(m_sigma, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_processing->setSigma(d); });

}

GaussianNoiseWidget::~GaussianNoiseWidget()
{

}
