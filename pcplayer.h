#ifndef PCPLAYER_H
#define PCPLAYER_H

#include "player.h"

class PCPlayer : public Player
{
public:
    PCPlayer();
    void makeMove() override {
    };
};

#endif // PCPLAYER_H
