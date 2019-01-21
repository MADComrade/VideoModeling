#include "fbutterworthwidget.h"
#include "fbutterworthfilter.h"
#include "ui_fbutterworthsetting.h"

FButterworthWidget::FButterworthWidget(FButterworthFilter *processing, QWidget *parent)
    : BaseProcessingWidget(parent)
{
    QWidget* itemWidget = new QWidget(this);
    m_processing = processing;
    m_settingWidget = new Ui::FButterworthSettings;
    m_settingWidget->setupUi(itemWidget);
    setSettingsWidget(itemWidget);

    m_settingWidget->widthSpinBox->setValue(m_processing->width());
    m_settingWidget->orderSpinBox->setValue(m_processing->order());
    m_settingWidget->checkBox->setChecked(m_processing->inverseFlag());

    connect(m_settingWidget->widthSpinBox, static_cast<void(QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
        [=](double d){ m_processing->setWidth(d); });
    connect(m_settingWidget->orderSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
        [=](int d){ m_processing->setOrder(d); });
    connect(m_settingWidget->checkBox, &QCheckBox::stateChanged, [this](int state){
      if (state == Qt::Unchecked) m_processing->setInverseFlag(false);
      else if (state == Qt::Checked) m_processing->setInverseFlag(true);
    });
    connect(m_processing, SIGNAL(outputVideoStream(cv::Mat)), this, SLOT(setVideoFrame(cv::Mat)));

    setWindowTitle(tr("Частотный фильтр Баттерворта"));
}
