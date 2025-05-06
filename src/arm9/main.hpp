#pragma once

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <memory>
#include <string>
#include <vector>
#include <iostream>
#include <regex>

#include <fat.h>
#include <filesystem.h>
#include <nds.h>
#include <nds/arm9/dldi.h>

#include "loader.hpp"
#include "save.hpp"

Save *save;

int main();
void update();
void render();