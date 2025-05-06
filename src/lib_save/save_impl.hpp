#pragma once

#include "../arm9/save.hpp"
#include "../arm9/sound.hpp"

class SaveImpl : Save
{
    private:
        SaveSlot *saveSlot;

        void setOrClearFlag(u16 flag, bool set);

    public:
        SaveImpl();
        SaveImpl(SaveSlot *save);
        ~SaveImpl();
        SaveSlot *getSaveSlot();
        bool isFlagSet(u16 flag);
        void setFlag(u16 flag);
        void clearFlag(u16 flag);
        u8 getGlobal(u16 global);
        void setGlobal(u16 global, u8 value);
};