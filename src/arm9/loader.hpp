#pragma once

#include <dlfcn.h>

#include "save.hpp"

namespace Loader
{
    void loadExampleLib();
    void unloadExmapleLib();

    Save *createSave();
}