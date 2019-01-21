#ifndef FIDEALFILTERWIDGET_H
#define FIDEALFILTERWIDGET_H

#include "baseprocessingwidget.h"

namespace Ui {
    class FGaussianSettings;
}
class FIdealFilter;

class FIdealFilterWidget : public BaseProcessingWidget
{
    Q_OBJECT
public:
    FIdealFilterWidget(FIdealFilter* processing, QWidget *parent = 0);
    ~FIdealFilterWidget(){}

private:
    Ui::FGaussianSettings* m_settingWidget;
    FIdealFilter* m_processing;
};

#endif // FIDEALFILTERWIDGET_H
