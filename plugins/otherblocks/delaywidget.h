#ifndef DELAYNOISE_H
#define DELAYNOISE_H

#include "baseprocessingwidget.h"

class QSlider;
class QLabel;
class QHBoxLayout;
class DelayProcessing;

class DelayWidget : public BaseProcessingWidget
{
    Q_OBJECT
public:
    DelayWidget(DelayProcessing* proc, QWidget *parent = 0);
    ~DelayWidget();

private slots:
    void onChangedTick(int i);

private:
    QString getFormattedTickImage(int tick);
    DelayProcessing* m_delayProcessing;
    QSlider* m_tickSlider;
    QLabel* m_tickText;
};

#endif // DELAYNOISE_H
