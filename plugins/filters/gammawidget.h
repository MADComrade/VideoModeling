#ifndef GAMMAWIDGET_H
#define GAMMAWIDGET_H

#include "baseprocessingwidget.h"

class GammaProcessing;

/*!
 * \brief Класс степенного преобразования изображения
 */
class GammaWidget : public BaseProcessingWidget
{
	Q_OBJECT
public:
	/*!
	* \brief Конструктор
	* \param processing - указатель на класс реализующий логарифмическое преобразования изображения
	* \param parent
	*/
	GammaWidget(GammaProcessing* processing, QWidget *parent = 0);
	~GammaWidget();

public slots :
	void onValueChangedConstant(double i); /// изменение константы степенного преобразования изображения
	void onValueChangedConstantPow(double i); /// изменение степенной константы степенного преобразования изображения

private:
	GammaProcessing* m_processing;

};

#endif // GAMMAWIDGET_H
