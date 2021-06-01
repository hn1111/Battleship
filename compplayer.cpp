#include "compplayer.h"

CompPlayer::CompPlayer()
{
    name = "AI";
}

void CompPlayer::makeMove()
{
    // TODO: make better ai
    Square sq = possibleMoves[QRandomGenerator::global()->generate() % possibleMoves.count()];

    game->handleTurn(this, sq.col, sq.row);

}

void CompPlayer::startNewGame()
{
    board.createShips();
    for (int row = 0; row < board.rows(); ++row) {
        for (int col = 0; col < board.columns(); ++col) {
            possibleMoves.append(Square{col, row});
        }
    }
}
