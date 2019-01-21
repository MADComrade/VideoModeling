#ifndef CORRELATIONWIDGET_H
#define CORRELATIONWIDGET_H

#include "baseprocessingwidget.h"

class CorrelationProcessing;

namespace Ui
{ 
	class CorrelationProcessingWidget;
}

/*!
 * \brief Класс корреляционного преобразования изображения
 */
class CorrelationWidget : public BaseProcessingWidget
{
	Q_OBJECT
public:
	/*!
	* \brief Конструктор
	* \param processing - указатель на класс реализующий логарифмическое преобразования изображения
	* \param parent
	*/
	CorrelationWidget(CorrelationProcessing* processing, QWidget *parent = 0);
	~CorrelationWidget();

public slots :
	void onValueChangedX(int); 
	void onValueChangedY(int); 
	void onFilterTypeChanged(int);

private:
	CorrelationProcessing* m_processing;
	Ui::CorrelationProcessingWidget* ui;
};

#endif // CORRELATIONWIDGET_H
