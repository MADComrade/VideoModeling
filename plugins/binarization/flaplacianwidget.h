#ifndef FLAPLACIANWIDGET_H
#define FLAPLACIANWIDGET_H

#include "baseprocessingwidget.h"

namespace Ui {
    class LaplacianSettings;
}
class FLaplacianDetector;

class FLaplacianWidget : public BaseProcessingWidget
{
    Q_OBJECT
public:
    FLaplacianWidget(FLaplacianDetector* processing, QWidget *parent = 0);
    ~FLaplacianWidget(){}

private:
    FLaplacianDetector* m_processing;
    Ui::LaplacianSettings* m_settingWidget;
};

#endif // FLAPLACIANWIDGET_H
