#ifndef LOGARITHMWIDGET_H
#define LOGARITHMWIDGET_H

#include "baseprocessingwidget.h"

class LogarithmProcessing;

/*!
 * \brief Класс логарифмического преобразования изображения
 */
class LogarithmWidget : public BaseProcessingWidget
{
	Q_OBJECT
public:
	/*!
	* \brief Конструктор
	* \param processing - указатель на класс реализующий логарифмическое преобразования изображения
	* \param parent
	*/
	LogarithmWidget(LogarithmProcessing* processing, QWidget *parent = 0);
	~LogarithmWidget();

public slots :
	void onValueChangedConstant(double i); /// изменение константы логарифмического преобразования изображения

private:
	LogarithmProcessing* m_processing;

};

#endif // LOGARITHMWIDGET_H
