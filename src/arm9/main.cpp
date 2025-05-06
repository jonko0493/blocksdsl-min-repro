#include "main.hpp"

void wait_forever(void)
{
    while (1)
        swiWaitForVBlank();
}

int main()
{
    defaultExceptionHandler();

    PrintConsole topScreen;
    PrintConsole bottomScreen;

    videoSetMode(MODE_0_2D);
    videoSetModeSub(MODE_0_2D);

    vramSetBankA(VRAM_A_MAIN_BG);
    vramSetBankC(VRAM_C_SUB_BG);

    consoleInit(&topScreen, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, true, true);
    consoleInit(&bottomScreen, 3, BgType_Text4bpp, BgSize_T_256x256, 31, 0, false, true);

    consoleSelect(&topScreen);

    mulf32(floattof32(1.0), floattof32(25.0));

    bool init_ok = nitroFSInit(NULL);
    if (!init_ok)
    {
        perror("nitroFSInit()");
        wait_forever();
    }
    // Initialize FAT for save files
    if (!fatInitDefault())
    {
        perror("fatInitDefault()");
        wait_forever();
    }
    swiWaitForVBlank();

    printf("Creating save file...\n");
    save = new Save();

    // use necessary functions here so we can include them in dynlibs
    save->getSaveSlot();
    mallinfo();

    printf("Loading example library...\n");
    Loader::loadExampleLib();

    SaveExtensions::setFlag(save, 5);
    if (SaveExtensions::isFlagSet(save, 5))
    {
        printf("Flag 5 was set.\n");
    }
    SaveExtensions::setGlobal(save, 5, 20);
    printf("Global 5 was set to %d\n", SaveExtensions::getGlobal(save, 5));

    SaveManager::save(1, save);

    SaveExtensions::saveSeekForSomeReason(save, string("nitro:/files/tmp.sav"));

    printf("Mem used: %d\nMem free: %d\n", Debug::getMemUsed(), Debug::getMemFree());

    printf("Unloading example lib...\n");
    Loader::unloadExmapleLib();

    printf("Press START to exit to loader\n");

    while (1)
    {
        swiWaitForVBlank();

        scanKeys();

        if (keysHeld() & KEY_START)
            break;
    }

    return 0;
}