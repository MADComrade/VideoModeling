#ifndef CORRELATIONPROCESSING_H
#define CORRELATIONPROCESSING_H

#include "commonprocessing.h"
#include <QMutex>
///TODO save
/*!
 * \brief Класс корреляционного преобразования изображения
 */
class CorrelationProcessing : public CommonProcessing
{
    Q_OBJECT
public:

	enum FILTER {
        LINEAR,    /// линейный фильтр
		MEDIAN,    /// медианный фильтр
		SUSPENDED  /// взвешенный средний фильтр
	};

	CorrelationProcessing(QObject *parent = 0);
	~CorrelationProcessing();

	void setFilterType(FILTER);
	void setX(int);
	void setY(int);

    int getFilterType() const;

    int getX() const;

    int getY() const;

public slots:
    /*!
     * \brief Переопределенный метод от CommonProcessing.
     * Отвечает за реализацию процесса обработки входного кадра видеоряда
     * \param frame - входной кадр
     */
    void intputVideoStream(const cv::Mat& frame);

private:
    FILTER filterType=LINEAR; /// тип фильтра
    int X=3; /// размер якоря фильтра по горизонтали
    int Y=3; /// размер якоря фильтра по вертикали
};

#endif // CORRELATIONPROCESSING_H
