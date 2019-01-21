#ifndef LOGARITHMPROCESSING_H
#define LOGARITHMPROCESSING_H

#include "commonprocessing.h"
#include <QMutex>

/*!
 * \brief Класс логарифмического преобразования изображения
 */
class LogarithmProcessing : public CommonProcessing
{
    Q_OBJECT
public:
	LogarithmProcessing(QObject *parent = 0);
	~LogarithmProcessing();

	void setConstant(double); // Установить константу логарифмического преобразования

    double getConstant() const;

    virtual void setModuleParameter(const QJsonObject &param);
    virtual void getModuleParameter(QJsonObject &param);
public slots:
    /*!
     * \brief Переопределенный метод от CommonProcessing.
     * Отвечает за реализацию процесса обработки входного кадра видеоряда
     * \param frame - входной кадр
     */
    void intputVideoStream(const cv::Mat& frame);

private:
    double constant=35; // Коснтанта логарифмического преобразования
};

#endif // LOGARITHMPROCESSING_H
