#ifndef SHIP_H
#define SHIP_H

#include <QVector>
#include "square.h"


class Ship
{
    friend class DragShip;
    friend class Board;
public:
    enum Direction
    {
        horizontal,
        vertical
    };
    Ship(int xBoard, int yBoard, int squares, Direction);
    void checkShip();
    bool isAlive();
    void removeFromBoard();
    void putOnBoard();

private:
    QVector<Square*> squares;
    int xB, yB;
    int sqNum;
    Direction dir;
};
#endif // SHIP_H
