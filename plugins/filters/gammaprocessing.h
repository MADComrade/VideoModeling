#ifndef GAMMAPROCESSING_H
#define GAMMAPROCESSING_H

#include "commonprocessing.h"
#include <QMutex>

/*!
 * \brief Класс степенного преобразования изображения
 */
class GammaProcessing : public CommonProcessing
{
    Q_OBJECT
public:
	GammaProcessing(QObject *parent = 0);
	~GammaProcessing();

	void setConstant(double); // Установить константу степенного преобразования
	void setConstantPow(double); // Установить степенную константу степенного преобразования

    double getConstant() const;

    double getConstantPow() const;

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
    double constant=1; /// Константа степенного преобразования
    double constantPow=1; /// Степенная конcтанта степенного преобразования
};

#endif // GAMMAPROCESSING_H
