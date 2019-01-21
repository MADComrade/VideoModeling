#ifndef FGAUSSIANWIDGET_H
#define FGAUSSIANWIDGET_H

#include "baseprocessingwidget.h"

namespace Ui {
    class FGaussianSettings;
}
class FGaussianProcessing;

class FGaussianWidget : public BaseProcessingWidget
{
    Q_OBJECT
public:
    FGaussianWidget(FGaussianProcessing* processing, QWidget *parent = 0);
    ~FGaussianWidget(){}

private:
    Ui::FGaussianSettings* m_settingWidget;
    FGaussianProcessing* m_processing;

};

#endif // FGAUSSIANWIDGET_H
