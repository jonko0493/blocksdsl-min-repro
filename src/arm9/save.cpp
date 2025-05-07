#include "save.hpp"
#include "loader.hpp"

// Make things unnecessarily complicated so we can use C++ stuff lol
void debugLog(string str)
{
    printf(format("{}\n", str).c_str());
}

void pointlessTimer()
{
    debugLog("In the timer");
    swiWaitForVBlank();
    timerStop(1);
}

string SaveManager::getSavePath()
{    
    string defaultDrive = string(fatGetDefaultDrive());
    if (defaultDrive == "")
    {
        defaultDrive = "fat:/";
    }
    string path = format("{}main.sav", defaultDrive);
    return path;
}

void SaveManager::initializeSave(string path)
{
    debugLog("Initializing save file...");
    FILE *newSaveFile = fopen(path.c_str(), "wb");
    u8 *cleanData = new u8[NUM_SAVE_SLOTS * SAVE_SLOT_SIZE];
    fwrite(cleanData, sizeof(u8), NUM_SAVE_SLOTS * SAVE_SLOT_SIZE, newSaveFile);
    fclose(newSaveFile);
    delete cleanData;
}

void SaveManager::checkSave(string path)
{
    if (access(path.c_str(), F_OK) != 0)
    {
        debugLog("Save file does not exist; initializing...");
        initializeSave(path);
        return;
    }
    FILE *saveFile = fopen(path.c_str(), "rb");
    fseek(saveFile, 0, SEEK_END);
    long length = ftell(saveFile);
    if (length != NUM_SAVE_SLOTS * SAVE_SLOT_SIZE)
    {
        debugLog(format("Save file was wrong size {:d} bytes; re-initializing...", length));
        fclose(saveFile);
        initializeSave(path);
    }
}

void SaveManager::save(int slot, Save *save)
{
    string path = getSavePath();
    debugLog(format("Attempting to save to {}...", path));
    checkSave(path);

    FILE *saveFile = fopen(path.c_str(), "rb+");
    fseek(saveFile, slot * SAVE_SLOT_SIZE, SEEK_SET);

    int flagWrite = fwrite(save->getSaveSlot()->flags, sizeof(u8), 512, saveFile);
    debugLog(format("Wrote {:d} bytes of flags", flagWrite));
    int globalWrite = fwrite(save->getSaveSlot()->globals, sizeof(u8), 512, saveFile);
    debugLog(format("Wrote {:d} bytes of globals", globalWrite));

    fclose(saveFile);
    debugLog("Saved!");

    timerStart(1, ClockDivider_64, 1, pointlessTimer);
}

Save *SaveManager::load(int slot)
{
    string path = getSavePath();
    debugLog(format("Attempting to load from {}...", path));
    checkSave(path);

    FILE *saveFile = fopen(path.c_str(), "rb");
    fseek(saveFile, slot * SAVE_SLOT_SIZE, SEEK_SET);

    Save *save = Loader::createSave();

    int flagRead = fread(save->getSaveSlot()->flags, sizeof(u8), 512, saveFile);
    debugLog(format("Read {:d} bytes of flags", flagRead));
    int globalRead = fwrite(save->getSaveSlot()->globals, sizeof(u8), 512, saveFile);
    debugLog(format("Read {:d} bytes of globals", globalRead));

    fclose(saveFile);

    return save;
}

Save::~Save() {}