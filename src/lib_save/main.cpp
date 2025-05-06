#include "save_impl.hpp"

#define SYM_PUBLIC __attribute__((visibility ("default")))

SYM_PUBLIC Save *createSave()
{
    return (Save *)new SaveImpl();
}