#include "main.hpp"

bool playing = false;

void vblank_handler(void)
{
    inputGetAndSend();
    Wifi_Update();

    if (fifoCheckValue32(FIFO_USER_01))
    {
        u32 soundCommand = fifoGetValue32(FIFO_USER_01);
        u32 sound = soundCommand & SOUND_MASK;
        
        if (soundCommand & (START_SOUND | PLAY_PERSISTENT_SOUND)) 
        {
            mmEffect(sound);
            if (soundCommand & START_SOUND)
            {
                playing = true;
            }
        }
    }
    if (!mmActive() && playing)
    {
        playing = false;
        fifoSendValue32(FIFO_USER_01, STOP_SOUND);
    }
}

int main()
{
    enableSound();

    readUserSettings();

    ledBlink(LED_ALWAYS_ON);

    touchInit();
    
    irqInit();
    irqSet(IRQ_VBLANK, vblank_handler);

    fifoInit();
    installWifiFIFO();
    installSoundFIFO();
    if (isDSiMode())
        installCameraFIFO();
    installSystemFIFO();

    mmInstall(FIFO_MAXMOD);

    initClockIRQTimer(3);

    irqEnable(IRQ_VBLANK);

    while (1)
    {
        swiWaitForVBlank();
    }

    return 0;
}