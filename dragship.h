#ifndef DRAGSHIP_H
#define DRAGSHIP_H

#include <QVector>
#include <QGraphicsRectItem>
#include <QPainter>
#include "square.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include "ship.h"
#include "board.h"


class Ship;
class DragShip : public QGraphicsRectItem
{
    friend class Ship;
public:
    DragShip();
    DragShip(Ship *sh, int squareWidth, int squareHeight, int boardWidth, int boardHeight, Board *b);
    void sync();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Ship *ship;
    Board *board;
    int sqW, sqH;
    int boardW, boardH;
    int shapeW, shapeH;
    bool hold;
    QColor color;
    Ship::Direction startingDir;
    bool checkPos();
    void rotate();

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // DRAGSHIP_H
