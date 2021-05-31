#include "player.h"

Player::Player()
{

}

bool Player::checkLose()
{
    // this function will change state of ship's cells if every cell is dead
    bool lost = true;
    for (auto sh : board.ships()) {
        sh->checkShip();
        if (sh->isAlive())
            lost = false;
    }
    return lost;
}
