#pragma once

#include <dlfcn.h>

#include "save.hpp"

namespace Loader
{
    void loadExampleLib();
    void unloadExmapleLib();
}

namespace SaveExtensions
{
    bool isFlagSet(Save *save, u16 flag);
    void setFlag(Save *save, u16 flag);
    void clearFlag(Save *save, u16 flag);
    u8 getGlobal(Save *save, u16 global);
    void setGlobal(Save *save, u16 global, u8 value);
    void saveSeekForSomeReason(Save *save, string otherSave);
}

namespace Debug
{
    int getMemUsed();
    int getMemFree();
}