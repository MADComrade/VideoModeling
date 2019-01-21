#ifndef COMMONWIDGET_H
#define COMMONWIDGET_H

#include <QWidget>

#include <QImage>
#include <opencv2/core/core.hpp>

class QLabel;
/*!
 * \brief Базовый класс виджета
 */
class CommonWidget : public QWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Конструктор по умолчанию
     * \param parent
     */
    CommonWidget(QWidget *parent = 0);
    ~CommonWidget();

protected slots:
    /*!
     * \brief Слот для отображения входного видеокадра
     * \param frame - текущий кадр
     */
    virtual void setVideoFrame(const cv::Mat& frame);

signals:
    void onCloseWidget(); /// сигнал о закрытии виджета

protected:
    bool isInit() const;
    void setInit(bool init);
    /*!
     * \brief Установка указателя на QLabel на котором
     * будет осуществляться отображение видеокадра
     * \param outputImageLable
     */
    void setOutputImageLable(QLabel *outputImageLable);
    void closeEvent(QCloseEvent *event); /// событие закрытия виджета

    bool m_init=false;
    QImage m_outputImage;
    QLabel* m_outputImageLable;
};

#endif // COMMONWIDGET_H
