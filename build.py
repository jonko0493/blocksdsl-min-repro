from architectds import *

arm9 = Arm9Binary(
    sourcedirs=['src/arm9'],
    libs=['mm9', 'nds9'],
    cxxflags='-Werror -Wno-psabi -fpermissive -std=gnu++20',
    libdirs=['${BLOCKSDS}/libs/maxmod', '${BLOCKSDS}/libs/libnds']
)
arm9.generate_elf()

save_lib = Arm9DynamicLibrary(
    name='save',
    main_binary=arm9,
    sourcedirs=['src/lib_save'],
    cxxflags='-Werror -Wno-psabi -fpermissive -std=gnu++20',
    libdirs=['${BLOCKSDS}/libs/maxmod', '${BLOCKSDS}/libs/libnds']
)
save_lib.generate_dsl()

nitrofs = NitroFS()
nitrofs.add_arm9_dsl(save_lib)
nitrofs.add_files_unchanged('nitrofs')
nitrofs.generate_image()

nds = NdsRom(
    binaries=[arm9, save_lib, nitrofs],
    nds_path='dyn_lib_bug_min_repro.nds',
    game_title='Dynamic Library',
    game_subtitle='Bug Repro'
)
nds.generate_nds()

nds.run_command_line_arguments()