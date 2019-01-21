#include "flaplacianwidget.h"
#include "flaplaciandetector.h"
#include "ui_laplaciansettings.h"

FLaplacianWidget::FLaplacianWidget(FLaplacianDetector *processing, QWidget *parent)
    : BaseProcessingWidget(parent)
{
    QWidget* itemWidget = new QWidget(this);
    m_processing = processing;
    m_settingWidget = new Ui::LaplacianSettings;
    m_settingWidget->setupUi(itemWidget);
    setSettingsWidget(itemWidget);

    m_settingWidget->scaleSpinBox->setValue(m_processing->scale());
    m_settingWidget->deltaSpinBox->setValue(m_processing->delta());
    m_settingWidget->checkBox->setChecked(m_processing->processingFlag());
    if(!m_processing->processingFlag())
        m_settingWidget->groupBox->setEnabled(false);

    connect(m_settingWidget->scaleSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
        [=](int d){ m_processing->setScale(d); });
    connect(m_settingWidget->deltaSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
        [=](int d){ m_processing->setDelta(d); });
    connect(m_settingWidget->checkBox, &QCheckBox::stateChanged, [this](int state){
      if (state == Qt::Unchecked) {
          m_processing->setProcessingFlag(false);
          m_settingWidget->groupBox->setEnabled(false);
      }
      else if (state == Qt::Checked){
          m_processing->setProcessingFlag(true);
          m_settingWidget->groupBox->setEnabled(true);
      }
    });
    connect(m_processing, SIGNAL(outputVideoStream(cv::Mat)), this, SLOT(setVideoFrame(cv::Mat)));

    setWindowTitle(tr("Детектор границ Лапласа"));

}
