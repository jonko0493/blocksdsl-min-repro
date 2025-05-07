#include "loader.hpp"

typedef Save *(fnCreateSave)();

fnCreateSave *createSaveFn;

namespace Loader
{
    void *saveLib;

    void loadExampleLib()
    {
        saveLib = dlopen("nitro:/dsl/save.dsl", RTLD_NOW | RTLD_LOCAL);
        printf("Save lib loaded to %x\n", (u32)saveLib);

        createSaveFn = (fnCreateSave *)dlsym(saveLib, "_Z10createSavev");
        printf("createSaveFn loaded to %x\n", (u32)createSaveFn);
    }

    void unloadExmapleLib()
    {
        dlclose(saveLib);
    }

    Save *createSave()
    {
        return createSaveFn();
    }
}