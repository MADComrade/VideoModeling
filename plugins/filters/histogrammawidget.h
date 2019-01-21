#ifndef HISTOGRAMMAWIDGET_H
#define HISTOGRAMMAWIDGET_H

#include "baseprocessingwidget.h"

class HistogrammaProcessing;

/*!
* \brief Класс эквалиации изображения
*/
class HistogrammaWidget : public BaseProcessingWidget
{
	Q_OBJECT
public:
	/*!
	* \brief Конструктор
	* \param processing - указатель на класс реализующий эквализацию изображения
	* \param parent
	*/
	HistogrammaWidget(HistogrammaProcessing* processing, QWidget *parent = 0);
	~HistogrammaWidget();

private:
	HistogrammaProcessing* m_processing;

};

#endif // HISTOGRAMMAMWIDGET_H
