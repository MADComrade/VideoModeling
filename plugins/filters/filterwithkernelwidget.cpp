#include "filterwithkernelwidget.h"

#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>

#include "filterwithkernel.h"

FilterWithKernelWidget::FilterWithKernelWidget(FilterWithKernel *processingLevel, QWidget *parent)
    : BaseProcessingWidget(parent)
{
    m_filterWithKernel = processingLevel;
    QHBoxLayout* typeProc = new QHBoxLayout();
    QLabel* m_label = new QLabel(tr("Размер аппертуры фильтра"),this);
    m_comboBox = new QComboBox(this);
    m_comboBox->addItems(m_filterWithKernel->kernelList());
    m_comboBox->setCurrentIndex(m_filterWithKernel->kernelIndex());
    typeProc->addWidget(m_label);
    typeProc->addWidget(m_comboBox);

    QWidget* itemWidget = new QWidget;
    itemWidget->setLayout(typeProc);
    setSettingsWidget(itemWidget);
    connect(m_comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(onChangedKernel(int)));
    connect(m_filterWithKernel,SIGNAL(outputVideoStream(cv::Mat)),this,SLOT(setVideoFrame(cv::Mat)));

    setTitleWidget(tr("Настройка блока ")+m_filterWithKernel->getBlockProcessingName());
}

FilterWithKernelWidget::~FilterWithKernelWidget()
{

}

void FilterWithKernelWidget::onChangedKernel(int i)
{
    if(i>=0){
        m_filterWithKernel->setKernelIndex(i);
    }
}
