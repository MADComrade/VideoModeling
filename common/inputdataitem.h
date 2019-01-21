#ifndef INPUTDATAITEM_H
#define INPUTDATAITEM_H

#include <QGraphicsEllipseItem>
#include <QRectF>
#include <QObject>

//!
//! \brief Класс входного потока данных
//!
class InputDataItem : public QGraphicsEllipseItem
{
public:
    enum { Type = UserType + 4 }; /// тип блока
    //!
    //! \brief Конструктор блока
    //! \param x - начальная позиция по х
    //! \param y - начальная позиция по y
    //! \param w - ширина
    //! \param h - высота
    //!
    InputDataItem(qreal x, qreal y, qreal w, qreal h);
    //!
    //! \brief Конструктор блока
    //! \param rect - координаты и размер блока
    //!
    InputDataItem(const QRectF &rect);
    ~InputDataItem();

    int type() const Q_DECL_OVERRIDE { return Type;}

private:
};

#endif // INPUTDATAITEM_H
