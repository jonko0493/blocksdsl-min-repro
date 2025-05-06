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

    printf("Loading example library...\n");
    Loader::loadExampleLib();

    SoundPlayer *soundPlayer = new SoundPlayer();
    soundPlayer->playSound();
    soundPlayer->stopSound();

    printf("Creating save file...\n");
    save = Loader::createSave();

    save->setFlag(5);
    if (save->isFlagSet(5))
    {
        printf("Flag 5 was set.");
    }

    save->setGlobal(5, 50);
    printf("Global 5 has value %d", save->getGlobal(5));

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