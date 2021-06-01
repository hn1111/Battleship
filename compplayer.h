#ifndef COMPPLAYER_H
#define COMPPLAYER_H

#include "player.h"
#include <QRandomGenerator>

#include "game.h"
#include <QThread>
#include <QCoreApplication>

class CompPlayer : public Player
{
public:
    CompPlayer();
    void makeMove() override;

public slots:
    void startNewGame() override;

private:
    QList<Square> nextTarget;
    QList<Square> possibleMoves;
};

#endif // COMPPLAYER_H
