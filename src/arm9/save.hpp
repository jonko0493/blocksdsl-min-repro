#pragma once

#include <format>
#include <string>

#include <nds.h>
#include <nds/arm9/dldi.h>
#include <nds/interrupts.h>
#include <fat.h>

using namespace std;

#define NUM_SAVE_SLOTS 30
#define SAVE_SLOT_SIZE 1024

struct SaveSlot
{
    u8 *flags;
    u8 *globals;

    SaveSlot()
    {
        flags = new u8[512];
        globals = new u8[512];
    }
    ~SaveSlot()
    {
        delete flags;
        delete globals;
    }
};

class Save
{
    public:
        virtual ~Save();
        virtual SaveSlot *getSaveSlot();
        virtual bool isFlagSet(u16 flag);
        virtual void setFlag(u16 flag);
        virtual void clearFlag(u16 flag);
        virtual u8 getGlobal(u16 global);
        virtual void setGlobal(u16 global, u8 value);
};

class SaveManager
{
private:
    static string getSavePath();
    static void initializeSave(string path);
    static void checkSave(string path);
public:
    static void save(int slot, Save *save);
    static Save *load(int slot);
};