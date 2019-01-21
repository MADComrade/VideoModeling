#ifndef ROIWIDGET_H
#define ROIWIDGET_H

#include "baseprocessingwidget.h"

class ROIProcessing;
namespace Ui
{
    class RoiUI;
}

class ROIWidget : public BaseProcessingWidget
{
    Q_OBJECT
public:
    ROIWidget(ROIProcessing* processing, QWidget *parent = 0);
    ~ROIWidget(){}

private slots:
    void onTopXChanged(int x);
    void onTopYChanged(int y);
    void onBottomXChanged(int x);
    void onBottomYChanged(int y);
    void onChangedSizeImage();

private:
    ROIProcessing* m_processing;
    Ui::RoiUI* ui;
};

#endif // ROIWIDGET_H
