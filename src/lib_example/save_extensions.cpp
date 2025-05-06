#include "../arm9/save.hpp"

#define SYM_PUBLIC __attribute__((visibility ("default")))

void setOrClearFlag(Save *save, u16 flag, bool set)
{
    flag--;
    int byte = flag >> 3;
    int bit = flag & 7;

    if (set)
    {
        save->getSaveSlot()->flags[byte] = save->getSaveSlot()->flags[byte] | (1 << bit);
    }
    else
    {
        save->getSaveSlot()->flags[byte] = save->getSaveSlot()->flags[byte] & ~(1 << bit);
    }
}
SYM_PUBLIC bool isFlagSet(Save *save, u16 flag)
{
    flag--;
    return (save->getSaveSlot()->flags[flag >> 3] >> (flag & 7)) & 1;
}
SYM_PUBLIC void setFlag(Save *save, u16 flag)
{
    setOrClearFlag(save, flag, true);
}
SYM_PUBLIC void clearFlag(Save *save, u16 flag)
{
    setOrClearFlag(save, flag, false);
}
SYM_PUBLIC u8 getGlobal(Save *save, u16 global)
{
    return save->getSaveSlot()->globals[--global];
}
SYM_PUBLIC void setGlobal(Save *save, u16 global, u8 value)
{
    save->getSaveSlot()->globals[--global] = value;
}

SYM_PUBLIC void saveSeekForSomeReason(Save *save, string otherSave)
{
    FILE *otherSaveFile = fopen(otherSave.c_str(), "rb");

    fseek(otherSaveFile, 100, SEEK_SET);

    fclose(otherSaveFile);
}