#include "loader.hpp"

typedef Save *(fnCreateSave)();

fnCreateSave *createSaveFn;

namespace Loader
{
    void *saveLib;

    void loadExampleLib()
    {
        saveLib = dlopen("nitro:/dsl/example.dsl", RTLD_NOW | RTLD_LOCAL);
        printf("Example lib loaded to %x\n", (u32)saveLib);

        createSaveFn = (fnCreateSave *)dlsym(saveLib, "createSave");
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