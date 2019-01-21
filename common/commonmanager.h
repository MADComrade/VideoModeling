#ifndef COMMONMANAGER_H
#define COMMONMANAGER_H

#include <QObject>
#include <QJsonObject>
#include <opencv2/core/core.hpp>
#include "moduleconfig.h"

class SimulationSingleton;
class CommonProcessing;
class CommonWidget;
/*!
 * \brief Базовый класс менеджера управления блока убработки видео
 */
class CommonManager: public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Конструктор по умолчанию
     * \param parent
     */
    CommonManager(QObject *parent = 0);
    ~CommonManager();

    /*!
     * \brief Показать виджет настройки текущего блока обработки видео
     */
    virtual void widgetShow();
    /*!
     * \brief Текущий тип блока обработки
     * \return тип блока обработки
     */
    int getModuleType() const;
    /*!
     * \brief Текущий тип обработки осуществляемый блоком
     * \return тип обработки осуществляемый блоком
     */
    int getBlockProcessing() const;
    /*!
     * \brief Название используемого метода обработки
     * \return
     */
    QString getBlockName();

    virtual void setModuleParameter(const QJsonObject& param);
    virtual void getModuleParameter(QJsonObject& param);

    void setSimulationManager(SimulationSingleton *sim);

protected slots:
    virtual void widgetClose(); /// слот обработки сигнала о закрытии виджета настройки

signals:
    void outputVideoStream(const cv::Mat &image); /// выходной видеопоток
    void intputVideoStream(const cv::Mat &image); /// входной видеопоток

protected:
    bool isWidgetShow() const; /// состояние отображение виджета настройки
    /*!
     * \brief Установка указателя на класс обработки видео
     * \param processingLevel
     */
    void setProcessingLevel(CommonProcessing *processingLevel);
    /*!
     * \return указатель на класс обработки видео
     */
    CommonProcessing *processingLevel() const;
    /*!
     * \brief Установка указателя на виджет настройки обработки видео
     * \param visualizationLevel
     */
    void setVisualizationLevel(CommonWidget *visualizationLevel);
    void initConnectionProcLevel(); /// инициализация соединений

    bool m_show=false;
    CommonProcessing* m_processingLevel = nullptr;
    CommonWidget* m_visualizationLevel = nullptr;

};

#endif // COMMONMANAGER_H
