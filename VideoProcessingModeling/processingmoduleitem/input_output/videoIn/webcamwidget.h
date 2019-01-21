#ifndef WEBCAMWIDGET_H
#define WEBCAMWIDGET_H

#include "baseprocessingwidget.h"

class WebCamPlayer;
class QComboBox;
class QLabel;
class QPushButton;
class QSlider;


class WebCamWidget : public BaseProcessingWidget
{
    Q_OBJECT
public:
    WebCamWidget(WebCamPlayer* webCam, QWidget *parent = 0);
    ~WebCamWidget();

signals:

private slots:
    void onClickStartStop();
    void onChangedTick(int i);
    void selectCam(int index);

private:
    void swapIcon();
    QString getFormattedTickImage(int tick);
    QSlider* m_tickSlider;
    QLabel* m_tickText;
    QPushButton* m_startStopButton;
    QComboBox* m_combo;
    WebCamPlayer* m_webCam;
};

#endif // WEBCAMWIDGET_H
