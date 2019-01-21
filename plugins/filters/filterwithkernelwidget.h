#ifndef FILTERWITHKERNELWIDGET_H
#define FILTERWITHKERNELWIDGET_H

#include "baseprocessingwidget.h"

class QLabel;
class QComboBox;
class FilterWithKernel;

class FilterWithKernelWidget : public BaseProcessingWidget
{
    Q_OBJECT
public:
    FilterWithKernelWidget(FilterWithKernel* processingLevel, QWidget *parent = 0);
    ~FilterWithKernelWidget();

private slots:
    void onChangedKernel(int i);

private:
    FilterWithKernel* m_filterWithKernel;
    QComboBox* m_comboBox;
};

#endif // FILTERWITHKERNELWIDGET_H
