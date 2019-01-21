#ifndef COMMONPROCESSING_H
#define COMMONPROCESSING_H

#include <QObject>
#include <opencv2/core/core.hpp>
#include <QJsonObject>
#include <QMutex>
#include <QMutexLocker>

class SimulationSingleton;
/*!
 * \brief Базовый класс обработки видеокадра
 */
class CommonProcessing : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Конструктор по умолчанию
     * \param parent
     */
    CommonProcessing(QObject *parent = 0);
    ~CommonProcessing();

    /*!
     * \brief Название используемого метода обработки
     * \return
     */
    QString getBlockProcessingName() const;

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

    virtual void setModuleParameter(const QJsonObject& param);
    virtual void getModuleParameter(QJsonObject& param);

    void setSimulationManager(SimulationSingleton *sim);

    SimulationSingleton *getSimulationManager() const;


signals:
    void outputVideoStream(const cv::Mat& frame); /// выходной видеокадр
    void stopSim();
    void errorSim(const QString& error);

public slots:
    virtual void intputVideoStream(const cv::Mat& frame); /// слот обработки входного видеокадра

protected:
    /*!
     * \brief Установка названия используемого метода обработки
     */
    void setBlockProcessingName(const QString &name);
    /*!
     * \brief Установка текущий типа блока обработки
     * \param moduleType
     */
    void setModuleType(const int &moduleType);
    /*!
     * \brief Установка Текущего типа обработки осуществляемого блоком
     * \param blockProcessing
     */
    void setBlockProcessing(const int &blockProcessing);

    virtual void startInit();

    cv::Mat m_frame;
    cv::Mat m_outFrame;
    QString m_name;
    int m_moduleType = 0;
    int m_blockProcessing = 0;
    QMutex m_mutex;

private:
    SimulationSingleton* m_simulation;
};

#endif // COMMONPROCESSING_H
