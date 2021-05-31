#ifndef PLAYER_H
#define PLAYER_H

#include "ship.h"
#include "board.h"
#include <QVector>


class Game;
class Player
{
public:
    Player();
    virtual ~Player() {};
    int shipsAlive() const;

    Board board;
    Game *game;
    QString name;
    bool checkLose();
    virtual void makeTurn() = 0;
};

#endif // PLAYER_H
