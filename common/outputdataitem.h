#ifndef OUTPUTDATAITEM_H
#define OUTPUTDATAITEM_H

#include <QGraphicsEllipseItem>
#include <QRectF>

//!
//! \brief Класс выходного потока данных
//!
class OutputDataItem : public QGraphicsEllipseItem
{
public:
    enum { Type = UserType + 6 }; /// тип блока
    //!
    //! \brief Конструктор блока
    //! \param x - начальная позиция по х
    //! \param y - начальная позиция по y
    //! \param w - ширина
    //! \param h - высота
    //!
    OutputDataItem(qreal x, qreal y, qreal w, qreal h);
    //!
    //! \brief Конструктор блока
    //! \param rect - координаты и размер блока
    //!
    OutputDataItem(const QRectF &rect);
    ~OutputDataItem();

    int type() const Q_DECL_OVERRIDE { return Type;}

};

#endif // OUTPUTDATAITEM_H
