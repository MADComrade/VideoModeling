#ifndef NEGATIVEMWIDGET_H
#define NEGATIVEMWIDGET_H

#include "baseprocessingwidget.h"

class NegativeProcessing;

/*!
* \brief Класс преобразования изображения в негатив
*/
class NegativeWidget : public BaseProcessingWidget
{
	Q_OBJECT
public:
	/*!
	* \brief Конструктор
	* \param processing - указатель на класс реализующий преобразования изображения в негатив
	* \param parent
	*/
	NegativeWidget(NegativeProcessing* processing, QWidget *parent = 0);
	~NegativeWidget();

private:
	NegativeProcessing* m_processing;

};

#endif // NEGATIVEMWIDGET_H
