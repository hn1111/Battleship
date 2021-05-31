#include "player.h"

Player::Player()
{

}

bool Player::checkLose()
{
    bool lost = true;
    for (auto sh : board.ships()) {
        sh->checkShip();
        if (sh->isAlive())
            lost = false;
    }
    return lost;
}
