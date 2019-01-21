#ifndef ROTATEWIDGET_H
#define ROTATEWIDGET_H

#include "baseprocessingwidget.h"

class RotateProcessing;

namespace Ui
{
    class RotateUI;
}

class RotateWidget : public BaseProcessingWidget
{
    Q_OBJECT
public:
    RotateWidget(RotateProcessing* processing,QWidget *parent = 0);
    ~RotateWidget(){}

private slots:
    void onXChanged(int x);
    void onYChanged(int y);
    void onChangedWidth(int w);
    void onChangedHeight(int h);

private:
    RotateProcessing* m_processing;
    Ui::RotateUI* ui;
};

#endif // ROTATEWIDGET_H
