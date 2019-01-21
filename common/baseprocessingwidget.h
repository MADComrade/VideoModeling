#ifndef BASEPROCESSINGWIDGET_H
#define BASEPROCESSINGWIDGET_H

#include "commonwidget.h"

namespace Ui {
class BaseProcessingWidget;
}
/*!
 * \brief Базовый класс виджета настройки блока обработки видео
 */
class BaseProcessingWidget : public CommonWidget
{
    Q_OBJECT
public:
    /*!
     * \brief Конструктор по умолчанию
     * \param parent
     */
    BaseProcessingWidget(QWidget *parent = 0);
    ~BaseProcessingWidget();

protected:
    /*!
     * \brief Установка виджета в лайаут настройки блока обработки видео
     * \param setting
     */
    void setSettingsWidget(QWidget* setting);
    /*!
     * \brief Установка текущего названия виджета
     * \param title
     */
    void setTitleWidget(const QString& title);

private:
    Ui::BaseProcessingWidget *ui;
};

#endif // BASEPROCESSINGWIDGET_H
