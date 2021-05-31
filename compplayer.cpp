#include "compplayer.h"

CompPlayer::CompPlayer()
{
    name = "AI";
}

void CompPlayer::makeTurn()
{
    // TODO: make better ai
    int col = QRandomGenerator::global()->generate() % board.columns();
    int row = QRandomGenerator::global()->generate() % board.rows();
    game->handleTurn(this, col, row);

}
