#include "ship.h"

Ship::Ship(int xBoard, int yBoard, int squaresNum, Ship::Direction direction):
    xB(xBoard), yB(yBoard),
    sqNum(squaresNum),
    dir(direction)
{

}

void Ship::checkShip()
{

    bool isDead = true;
    for (auto sq : squares)
        if (sq->status != Square::dead && sq->status != Square::hit)
            isDead = false;
    if (isDead)
        for (auto sq : squares)
            sq->status = Square::dead;
}

bool Ship::isAlive()
{
    for (auto sq : squares)
        if (sq->status == Square::occupied)
            return true;
    return false;
}

void Ship::removeFromBoard()
{
    // pointers to squares stay the same
    // only changes the board
    for (auto &sq : squares)
        sq->status = Square::empty;
}

void Ship::putOnBoard()
{
    // pointers to squares stay the same
    // only changes the board
    for (auto &sq : squares)
        sq->status = Square::occupied;
}
