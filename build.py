from architectds import *

arm9 = Arm9Binary(
    sourcedirs=['src/arm9'],
    libs=['nds9'],
    cxxflags='-Werror -Wno-psabi -fpermissive -std=gnu++20',
    libdirs=['${BLOCKSDS}/libs/libnds']
)
arm9.generate_elf()

example_lib = Arm9DynamicLibrary(
    name='example',
    main_binary=arm9,
    sourcedirs=['src/lib_example'],
    cxxflags='-Werror -Wno-psabi -fpermissive -std=gnu++20',
    libdirs=['${BLOCKSDS}/libs/libnds']
)
example_lib.generate_dsl()

nitrofs = NitroFS()
nitrofs.add_arm9_dsl(example_lib)
nitrofs.generate_image()

nds = NdsRom(
    binaries=[arm9, example_lib, nitrofs],
    nds_path='dyn_lib_bug_min_repro.nds',
    game_title='Dynamic Library',
    game_subtitle='Bug Repro'
)
nds.generate_nds()

nds.run_command_line_arguments()