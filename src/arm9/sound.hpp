#pragma once

#include <nds.h>
#include <nds/arm9/math.h>
#include <maxmod9.h>

class SoundPlayer
{
    public:
        SoundPlayer();
        void playSound();
        void stopSound();
};