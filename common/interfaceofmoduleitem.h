#ifndef INTERFACEOFMODULEITEM_H
#define INTERFACEOFMODULEITEM_H

#include <QGraphicsItem>
#include <QSharedPointer>
#include <QObject>
#include <QJsonObject>

#include <opencv2/core/core.hpp>
#include "moduleconfig.h"
#include "commonmanager.h"
#include "settings_block_io.h"


class SimulationSingleton;
class InputDataItem;
class OutputDataItem;
class InputVideoItem;
class OutputVideoItem;
class ArrowBlock;
//!
//! \brief Интерфейс для работы с блоками на сцене
//!
class InterfaceOfModuleItem : public QObject, public QGraphicsItemGroup
{
    Q_OBJECT
public:
    /*!
     * \brief Конструктор по умолчанию
     * \param parent
     */
    InterfaceOfModuleItem(Param param=In1Out1,QGraphicsItemGroup *parent = 0);
    virtual ~InterfaceOfModuleItem();
    /*!
     * \brief Удаление соединяющей линии между блоками
     * \param arrow - соединяющая линия
     */
    virtual void removeArrow(ArrowBlock *arrow);
    /*!
     * \brief Удаление всех соединяющих линий данного блока обработки
     */
    virtual void removeArrows();
    /*!
     * \brief Добавление соединяющей линии между блоками
     * \param arrow - добавляемая соединяющая линия
     */
    virtual void addArrow(ArrowBlock *arrow);

    void setModuleParameter(const QJsonObject& param);
    void getModuleParameter(QJsonObject& param);

    virtual InputDataItem* getInputDataItem();
    virtual OutputDataItem* getOutputDataItem();
    virtual InputVideoItem* getInputVideoItem();
    virtual OutputVideoItem* getOutputVideoItem();

    /*!
     * \brief Запрос текущего типа блока обработки
     * \return id блока обработки
     */
    virtual int moduleType() const;
    /*!
     * \brief Тип обработки осуществляемый блоком
     * \return id типа обработки
     */
    virtual int blockProcessingType() const;

    QString getModuleName() const;
    void setModuleName(const QString &moduleName);

    const QList<ArrowBlock *>& getArrows() const;

    void setSimulationManager(SimulationSingleton *sim);

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event) Q_DECL_OVERRIDE;
    /// изменение расположения блока и перерисовка соединяющих линий
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) Q_DECL_OVERRIDE;

signals:
    ///output signals
    void outputVideoStream(const cv::Mat& frame);
    void outputDataStream();
    ///input signals
    void onInputVideoStream(const cv::Mat& frame);
    void onInputDataStream();
protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event); /// обработка двойного клика по блоку
    void setCommonManager(CommonManager* manager); /// установка менеджера обработки видео
    CommonManager* getCommonManager() const;

    QList<ArrowBlock *> arrows;
    QMenu *m_ContextMenu;
    int m_moduleType = 0;
    int m_blockProcessing = 0;

    QGraphicsTextItem* m_itemText;
    QGraphicsRectItem* m_item;
    QGraphicsTextItem* m_textVout;
    QGraphicsTextItem* m_textVin;
    QGraphicsTextItem* m_textDout;
    QGraphicsTextItem* m_textDin;
    OutputVideoItem* m_outEl;
    InputVideoItem* m_inEl;
    InputDataItem* m_dInEl;
    OutputDataItem* m_dOutEl;

    QSharedPointer<CommonManager> m_manager;
    Param m_param;
    QString m_moduleName;
};

#endif // INTERFACEOFMODULEITEM_H
