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
    void makeTurn() override;
};

#endif // COMPPLAYER_H
