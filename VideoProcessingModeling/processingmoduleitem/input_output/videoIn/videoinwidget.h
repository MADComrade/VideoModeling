#ifndef VIDEOINWIDGET_H
#define VIDEOINWIDGET_H

#include "commonwidget.h"
#include <opencv2/core/core.hpp>
#include <QObject>

class VideoImagePlayer;
namespace Ui {
class VideoInWidget;
}
/*!
 * \brief Виджет настройки проигрывателя
 */
class VideoInWidget : public CommonWidget
{
    Q_OBJECT

public:
    explicit VideoInWidget(VideoImagePlayer* player,QWidget *parent = 0);
    ~VideoInWidget();

private slots:
    void on_startStop_b_clicked();

    void on_load_b_clicked();

    void on_workWithVideo_rb_clicked(bool checked);
    void on_workWithImage_rb_clicked(bool checked);

    void on_horizontalSlider_sliderMoved(int position);

protected slots:
    /*!
     * \brief Слот для отображения входного видеокадра
     * \param frame - текущий кадр
     */
    virtual void setVideoFrame(const cv::Mat& frame);

private:
    void setWorkState(bool state);
    void swapIcon();
    QString getFormattedTime(int timeInSeconds);
    QString getFormattedTickImage(int tick);

    Ui::VideoInWidget *ui;
    VideoImagePlayer* m_player;
};

#endif // VIDEOINWIDGET_H
