#ifndef INPUTVIDEOITEM_H
#define INPUTVIDEOITEM_H

#include <QGraphicsEllipseItem>
#include <QRectF>

//!
//! \brief Класс входного потока видео
//!
class InputVideoItem : public QGraphicsEllipseItem
{    
public:
    enum { Type = UserType + 5 }; /// тип блока
    //!
    //! \brief Конструктор блока
    //! \param x - начальная позиция по х
    //! \param y - начальная позиция по y
    //! \param w - ширина
    //! \param h - высота
    //!
    InputVideoItem(qreal x, qreal y, qreal w, qreal h);
    //!
    //! \brief Конструктор блока
    //! \param rect - координаты и размер блока
    //!
    InputVideoItem(const QRectF &rect);
    ~InputVideoItem();

    int type() const Q_DECL_OVERRIDE { return Type;}

};

#endif // INPUTVIDEO_H
