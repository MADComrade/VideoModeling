#ifndef IMAGEPLAYERWIDGET_H
#define IMAGEPLAYERWIDGET_H

#include "baseprocessingwidget.h"

class ImagePlayer;
class QLabel;
class QPushButton;
class QSlider;

class ImagePlayerWidget : public BaseProcessingWidget
{
    Q_OBJECT
public:
    ImagePlayerWidget(ImagePlayer* player, QWidget *parent = 0);
    ~ImagePlayerWidget(){}

private slots:
    void onClickLoad();
    void onClickStartStop();
    void onChangedTick(int i);

private:
    void swapIcon();
    QString getFormattedTickImage(int tick);
    QSlider* m_tickSlider;
    QLabel* m_tickText;
    QPushButton* m_loadButton;
    QPushButton* m_startStopButton;
    ImagePlayer* m_player;
};

#endif // IMAGEPLAYERWIDGET_H
