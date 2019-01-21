#ifndef OUTPUTVIDEOITEM_H
#define OUTPUTVIDEOITEM_H

#include <QGraphicsEllipseItem>
#include <QRectF>

//!
//! \brief Класс выходного потока видео
//!
class OutputVideoItem : public QGraphicsEllipseItem
{
public:
    enum { Type = UserType + 7 }; /// тип блока
    //!
    //! \brief Конструктор блока
    //! \param x - начальная позиция по х
    //! \param y - начальная позиция по y
    //! \param w - ширина
    //! \param h - высота
    //!
    OutputVideoItem(qreal x, qreal y, qreal w, qreal h);
    //!
    //! \brief Конструктор блока
    //! \param rect - координаты и размер блока
    //!
    OutputVideoItem(const QRectF &rect);
    ~OutputVideoItem();

    int type() const Q_DECL_OVERRIDE { return Type;}

};

#endif // OUTPUTVIDEO_H
