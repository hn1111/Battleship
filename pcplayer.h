#ifndef PCPLAYER_H
#define PCPLAYER_H

#include "player.h"

class PCPlayer : public Player
{
public:
    PCPlayer();
    void makeTurn() override {
    };
};

#endif // PCPLAYER_H
