#ifndef HISTOGRAMMAROCESSING_H
#define HISTOGRAMMAROCESSING_H

#include "commonprocessing.h"
#include <QMutex>

/*!
 * \brief Класс эквализации изображения
 */
class HistogrammaProcessing : public CommonProcessing
{
    Q_OBJECT
public:
	HistogrammaProcessing(QObject *parent = 0);
	~HistogrammaProcessing();

public slots:
    /*!
     * \brief Переопределенный метод от CommonProcessing.
     * Отвечает за реализацию процесса обработки входного кадра видеоряда
     * \param frame - входной кадр
     */
    void intputVideoStream(const cv::Mat& frame);

private:

};

#endif // HISTOGRAMMAROCESSING_H
