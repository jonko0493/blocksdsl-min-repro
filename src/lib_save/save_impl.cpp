#include "save_impl.hpp"

SaveImpl::SaveImpl()
{
    this->saveSlot = new SaveSlot();
}

SaveImpl::SaveImpl(SaveSlot *save)
{
    this->saveSlot = save;
}

SaveImpl::~SaveImpl()
{
    delete saveSlot;
}

SaveSlot *SaveImpl::getSaveSlot()
{
    return this->saveSlot;
}

void SaveImpl::setOrClearFlag(u16 flag, bool set)
{
    flag--;
    int byte = flag >> 3;
    int bit = flag & 7;

    if (set)
    {
        this->saveSlot->flags[byte] = this->saveSlot->flags[byte] | (1 << bit);
    }
    else
    {
        this->saveSlot->flags[byte] = this->saveSlot->flags[byte] & ~(1 << bit);
    }
}

bool SaveImpl::isFlagSet(u16 flag)
{
    flag--;
    return (this->saveSlot->flags[flag >> 3] >> (flag & 7)) & 1;
}

void SaveImpl::setFlag(u16 flag)
{
    setOrClearFlag(flag, true);
}

void SaveImpl::clearFlag(u16 flag)
{
    setOrClearFlag(flag, false);
}

u8 SaveImpl::getGlobal(u16 global)
{
    return this->saveSlot->globals[--global];
}

void SaveImpl::setGlobal(u16 global, u8 value)
{
    this->saveSlot->globals[--global] = value;
}