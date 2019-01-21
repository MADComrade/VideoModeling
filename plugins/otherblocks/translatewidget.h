#ifndef TRANSLATEWIDGET_H
#define TRANSLATEWIDGET_H

#include "baseprocessingwidget.h"

class TranslateProcessing;
namespace Ui
{
    class TranslateUI; ///todo
}

class TranslateWidget : public BaseProcessingWidget
{
    Q_OBJECT
public:
    TranslateWidget(TranslateProcessing* processing, QWidget *parent = 0);
    ~TranslateWidget(){}

private slots:
    void onChangedWidth(int w);
    void onChangedHeight(int h);
    void onXChanged(int x);
    void onYChanged(int y);

private:
    TranslateProcessing* m_processing;
    Ui::TranslateUI* ui;
};

#endif // TRANSLATEWIDGET_H
