#ifndef NEGATIVEPROCESSING_H
#define NEGATIVEPROCESSING_H

#include "commonprocessing.h"
#include <QMutex>

/*!
 * \brief Класс преобразования изображения в негатив
 */
class NegativeProcessing : public CommonProcessing
{
    Q_OBJECT
public:
    NegativeProcessing(QObject *parent = 0);
	~NegativeProcessing();

public slots:
    /*!
     * \brief Переопределенный метод от CommonProcessing.
     * Отвечает за реализацию процесса обработки входного кадра видеоряда
     * \param frame - входной кадр
     */
    void intputVideoStream(const cv::Mat& frame);

private:
    cv::Mat m_subMat;

};

#endif // NEGATIVEPROCESSING_H
