#ifndef CANNYWIDGET_H
#define CANNYWIDGET_H

#include "baseprocessingwidget.h"

namespace Ui {
    class CannyWidget;
}
class CannyProcessing;

class CannyWidget : public BaseProcessingWidget
{
    Q_OBJECT
public:
    CannyWidget(CannyProcessing* processing, QWidget *parent = 0);
    ~CannyWidget(){}

private:
    CannyProcessing* m_processing;
    Ui::CannyWidget* m_settingWidget;
};

#endif // CANNYWIDGET_H
