cmake_minimum_required(VERSION 3.30)
project(chk_kigen LANGUAGES C VERSION 0.1.0)

include(cmake/chk.cmake)

find_package(Cwalk CONFIG REQUIRED)
find_package(SDL3 CONFIG REQUIRED)

chk_add(NAME Core KIND lib
    HDR
    "color.h"
    "fmt.h"
    "log.h"
    "math.h"
    "types.h"
    "vec.h"

    SRC
    "color.c"
    "fmt.c"
    "log.c"
    "math.c"
    "vec.c"

    PRV
    cwalk
)

chk_add(NAME Launcher KIND lib
    HDR
    "launcher.h"
    "input.h"
    "timer.h"

    SRC
    "launcher.c"
    "input.c"
    "timer.c"

    PUB
    chk::Core

    PRV
    SDL3::SDL3
)

chk_add(NAME Kigen KIND exe
    SRC
    "main.c"

    PUB
    chk::Core
    chk::Launcher

    PRV
    SDL3::SDL3
)
