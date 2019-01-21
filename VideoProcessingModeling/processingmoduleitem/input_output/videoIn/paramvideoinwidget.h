#ifndef PARAMVIDEOINWIDGET_H
#define PARAMVIDEOINWIDGET_H

#include "baseprocessingwidget.h"

class ParamVideoInput;
class QLabel;
class QPushButton;
class QSlider;

class ParamVideoInWidget : public BaseProcessingWidget
{
    Q_OBJECT
public:
    ParamVideoInWidget(ParamVideoInput* videoPlayer, QWidget *parent = 0);
    ~ParamVideoInWidget(){}

protected slots:
    /*!
     * \brief Слот для отображения входного видеокадра
     * \param frame - текущий кадр
     */
    virtual void setVideoFrame(const cv::Mat& frame);

private slots:
    void onClickLoad();
    void onClickStartStop();
    void onChangedTick(int i);
    void onChangedFrame(int i);

private:
    void swapIcon();
    QString getFormattedTime(int timeInSeconds);
    QString getFormattedTickImage(int tick);
    ParamVideoInput* m_videoPlayer;
    QSlider* m_tickSlider;
    QSlider* m_frameSlider;
    QLabel* m_maxTimeText;
    QLabel* m_currentTimeText;
    QLabel* m_tickText;
    QPushButton* m_loadButton;
    QPushButton* m_startStopButton;
};

#endif // PARAMVIDEOINWIDGET_H
