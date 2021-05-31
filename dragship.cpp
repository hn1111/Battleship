#include "dragship.h"

#include <QGraphicsScene>
#include "fieldview.h"
DragShip::DragShip()
{

}

DragShip::DragShip(Ship *sh,  int sWidth, int sHeight, int boardW, int boardH, Board *b):
    QGraphicsRectItem(),
    ship(sh), board(b),
    sqW(sWidth), sqH(sHeight),
    boardW(boardW), boardH(boardH)
{
    color = Qt::black;
    hold = false;
    setPos(ship->xB * sWidth, ship->yB * sHeight);
    setFlag(QGraphicsItem::ItemIsMovable);
    setAcceptHoverEvents(true);
    sync();
}

void DragShip::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    startingDir = ship->dir;
    if (event->button() == Qt::MiddleButton || event->button() == Qt::RightButton && hold) {
        rotate();
    } else {
        hold = true;
        QGraphicsRectItem::mousePressEvent(event);
    }
}

void DragShip::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsRectItem::mouseMoveEvent(event);
    // no dragging over the borders
    if (x() < 0) {
        setX(0);
    }
    if (y() < 0)
        setY(0);

    if (y() + shapeH > boardH)
        setY(boardH - shapeH);

    if (x() + shapeW > boardW)
        setX(boardW - shapeW);

    if (checkPos())
        color = Qt::black;
    else
        color = Qt::red;
}

void DragShip::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton || event->button() == Qt::RightButton)
        return;
    hold = false;
    QGraphicsRectItem::mouseReleaseEvent(event);
    if (checkPos()) {
        ship->removeFromBoard();
        ship->xB = round(pos().x()/sqW);
        ship->yB = round(pos().y()/sqH);
        board->createSquarePointers(ship);
    } else {
        ship->dir = startingDir;
    }
    color = Qt::black;
    setPos(ship->xB * sqW, ship->yB * sqH);
}

bool DragShip::checkPos()
{
    ship->removeFromBoard();

    int x = round(pos().x()/sqW);
    int y = round(pos().y()/sqH);

    if (x < 0 || y < 0 || x >= board->columns() || y >= board->rows())
        return false;

    bool correct =  board->isSpaceFree(x, y,
                       ship->sqNum, ship->dir);

    ship->putOnBoard();
    return correct;
}

void DragShip::rotate()
{

    if (ship->dir == Ship::horizontal) {
        ship->dir = Ship::vertical;
    } else {
        ship->dir = Ship::horizontal;
    }
}

void DragShip::sync()
{
    shapeW = ship->dir == Ship::vertical ? sqW : sqW * ship->sqNum;
    shapeH = ship->dir == Ship::horizontal ? sqH : sqH * ship->sqNum;
}


void DragShip::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::transparent);
    painter->setPen(QPen(color, 3));
    sync();
    setRect(0,0,shapeW,shapeH);
    painter->drawRect(0, 0, shapeW, shapeH);
}

