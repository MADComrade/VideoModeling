#ifndef FBUTTERWORTHWIDGET_H
#define FBUTTERWORTHWIDGET_H

#include "baseprocessingwidget.h"

namespace Ui {
    class FButterworthSettings;
}
class FButterworthFilter;
class FButterworthWidget : public BaseProcessingWidget
{
    Q_OBJECT
public:
    FButterworthWidget(FButterworthFilter* processing, QWidget *parent = 0);
    ~FButterworthWidget(){}

private:
    FButterworthFilter* m_processing;
    Ui::FButterworthSettings* m_settingWidget;
};

#endif // FBUTTERWORTHWIDGET_H
