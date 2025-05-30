#include "loader.hpp"

typedef bool (fnIsFlagSet)(Save *, u16);
typedef void (fnSetFlag)(Save *, u16);
typedef void (fnClearFlag)(Save *, u16);
typedef u8 (fnGetGlobal)(Save *, u16);
typedef void (fnSetGlobal)(Save *, u16, u8);

typedef int (fnGetMemUsed)();
typedef int (fnGetMemFree)();

fnIsFlagSet *isFlagSetFn;
fnSetFlag *setFlagFn;
fnClearFlag *clearFlagFn;
fnGetGlobal *getGlobalFn;
fnSetGlobal *setGlobalFn;

fnGetMemUsed *getMemUsedFn;
fnGetMemFree *getMemFreeFn;

namespace Loader
{
    void *exampleLib;

    void loadExampleLib()
    {
        exampleLib = dlopen("nitro:/dsl/example.dsl", RTLD_NOW | RTLD_LOCAL);
        printf("Example lib loaded to %x\n", (u32)exampleLib);

        isFlagSetFn = (fnIsFlagSet *)dlsym(exampleLib, "_Z9isFlagSetP4Savet");
        printf("isFlagSet loaded to %x\n", (u32)isFlagSetFn);
        setFlagFn = (fnSetFlag *)dlsym(exampleLib, "_Z7setFlagP4Savet");
        clearFlagFn = (fnClearFlag *)dlsym(exampleLib, "_Z9clearFlagP4Savet");
        getGlobalFn = (fnGetGlobal *)dlsym(exampleLib, "_Z9getGlobalP4Savet");
        setGlobalFn = (fnSetGlobal *)dlsym(exampleLib, "_Z9setGlobalP4Saveth");

        getMemUsedFn = (fnGetMemUsed *)dlsym(exampleLib, "getMemUsed");
        getMemFreeFn = (fnGetMemFree *)dlsym(exampleLib, "getMemFree");
    }

    void unloadExmapleLib()
    {
        dlclose(exampleLib);
    }
}

namespace SaveExtensions
{
    bool isFlagSet(Save *save, u16 flag)
    {
        return isFlagSetFn(save, flag);
    }

    void setFlag(Save *save, u16 flag)
    {
        setFlagFn(save, flag);
    }

    void clearFlag(Save *save, u16 flag)
    {
        clearFlagFn(save, flag);
    }

    u8 getGlobal(Save *save, u16 global)
    {
        return getGlobalFn(save, global);
    }

    void setGlobal(Save *save, u16 global, u8 value)
    {
        setGlobalFn(save, global, value);
    }
}

namespace Debug
{
    int getMemUsed()
    {
        return getMemUsedFn();
    }

    int getMemFree()
    {
        return getMemFreeFn();
    }
}