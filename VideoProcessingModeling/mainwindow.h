#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "moduleconfig.h"
#include "interfaceofmoduleitem.h"

#include <QMainWindow>

class DiagramScene;

QT_BEGIN_NAMESPACE
class QAction;
class QToolBox;
class QSpinBox;
class QComboBox;
class QFontComboBox;
class QButtonGroup;
class QLineEdit;
class QGraphicsTextItem;
class QFont;
class QToolButton;
class QAbstractButton;
class QGraphicsView;
class QGridLayout;
QT_END_NAMESPACE

class PluginInterface;
class SimulationSingleton;
/*!
 * \brief Класс главной формы
 * \author Chernyshev S.A.
 * 	\version 1.0
    Класс, генерирующий главное рабочее окно.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
   MainWindow();
   ~MainWindow();

private slots:
   /*!
     * \brief Выделение элемента в области отрисовки
     * \param id - номер выделенного элемента
     */
    void buttonGroupClicked(int id);
    /*!
     * \brief Удаление элементов со сцены
     */
    void deleteItem();
    /*!
     * \brief Установка режима перемещения или отрисовки линии на сцене
     * \param id - номер режима работы
     */
    void pointerGroupClicked(int id);
    /*!
     * \brief Снятие выделения с блоков для отрисовки, т.е. после помещения на сцену блока,
     * чтобы поместить его снова надо выбрать на панеле по новой
     * \param item - текущий блок, который поместили на сцену
     */
    void itemInserted(InterfaceOfModuleItem *item);
    /*!
     * \brief Снятие выделения с текстового блока
     * \param item - текущий текстовый блок, который поместили на сцену
     */
    void textInserted(QGraphicsTextItem *item);
    /*!
     * \brief Изменение шрифта
     * \param font - тип шрифта
     */
    void currentFontChanged(const QFont &font);
    /*!
     * \brief Изменение размера шрифта
     * \param size - размер
     */
    void fontSizeChanged(const QString &size);
    /*!
     * \brief Скалирование сцены отрисовки блоков
     * \param scale - коэф. скалирования
     */
    void sceneScaleChanged(const QString &scale);
    /*!
     * \brief Изменение цвета текста
     */
    void textColorChanged();
    /*!
     * \brief Изменение цвета линии
     */
    void lineColorChanged();
    void textButtonTriggered();
    void lineButtonTriggered();
    void handleFontChange();
    /*!
     * \brief Выделение выбранного элемента
     * \param item - выбранный блок
     */
    void itemSelected(QGraphicsItem *item);
    void about();

    void saveProject();
    void openProject();

    void simulationError(const QString& error);
    void startSumulation();

private:
    void createToolBox();
    void createActions();
    void createMenus();
    void createToolbars();
    /*!
     * \brief Компоновка доступных для ПО блоков обработки
     * \param layoutBlocks - лайаут для установки кнопок отрисовки блоков
     * \param blocks - QMap<QString, CONFUGUATOR::ModuleType>,
     * где QString - имя блока, CONFUGUATOR::ModuleType - id устанавливаемого блока
     */
    void configLayout(QGridLayout * layoutBlocks, QMap<QString, int> blocks, bool plugins = false);
    /*!
     * \brief создание виджета с рисунком блока обработки и подписью
     * \param text - название блока
     * \param type - тип блока
     * \return виджет, который помещается в QGridLayout
     */
    QWidget *createCellWidget(const QString &text, int type, bool plugins = false);
    QMenu *createColorMenu(const char *slot, QColor defaultColor);
    QIcon createColorToolButtonIcon(const QString &image, QColor color);
    QIcon createColorIcon(QColor color);

    DiagramScene *scene;
    QGraphicsView *view;

    QAction *exitAction;
    QAction *addAction;
    QAction *deleteAction;

    QAction *saveAction;
    QAction *openAction;

    QAction *simulationAction;

    QAction *toFrontAction;
    QAction *sendBackAction;
    QAction *aboutAction;

    QMenu *fileMenu;
    QMenu *itemMenu;
    QMenu *aboutMenu;

    QToolBar *textToolBar;
    QToolBar *editToolBar;
    QToolBar *colorToolBar;
    QToolBar *pointerToolbar;
    QToolBar *simulationToolbar;

    QComboBox *sceneScaleCombo;
    QComboBox *itemColorCombo;
    QComboBox *textColorCombo;
    QComboBox *fontSizeCombo;
    QFontComboBox *fontCombo;

    QToolBox *toolBox;
    QButtonGroup *buttonGroup;
//    QButtonGroup *buttonFilterGroup;
    QButtonGroup *pointerTypeGroup;
    QButtonGroup *backgroundButtonGroup;
    QToolButton *fontColorToolButton;
    QToolButton *fillColorToolButton;
    QToolButton *lineColorToolButton;
    QAction *boldAction;
    QAction *underlineAction;
    QAction *italicAction;
    QAction *textAction;
    QAction *fillAction;
    QAction *lineAction;
    PluginInterface* m_currentPlugins;
    SimulationSingleton* m_simSingleton;

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void onCloseMainWindow();
};
//! [0]

#endif // MAINWINDOW_H
