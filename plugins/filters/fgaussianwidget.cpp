#include "fgaussianwidget.h"
#include "ui_fgaussiansettingswidget.h"

#include "fgaussianprocessing.h"

FGaussianWidget::FGaussianWidget(FGaussianProcessing *processing, QWidget *parent)
    : BaseProcessingWidget(parent)
{
    QWidget* itemWidget = new QWidget(this);
    m_processing = processing;
    m_settingWidget = new Ui::FGaussianSettings;
    m_settingWidget->setupUi(itemWidget);
    setSettingsWidget(itemWidget);

    m_settingWidget->doubleSpinBox->setValue(m_processing->getSigma());
    m_settingWidget->checkBox->setChecked(m_processing->getInverseFlag());

    connect(m_settingWidget->doubleSpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_processing->setSigma(d); });
    connect(m_settingWidget->checkBox, &QCheckBox::stateChanged, [this](int state){
      if (state == Qt::Unchecked) m_processing->setInverseFlag(false);
      else if (state == Qt::Checked) m_processing->setInverseFlag(true);
    });
    connect(m_processing, SIGNAL(outputVideoStream(cv::Mat)), this, SLOT(setVideoFrame(cv::Mat)));

    setWindowTitle(tr("Частотный фильтр Гаусса"));

}
