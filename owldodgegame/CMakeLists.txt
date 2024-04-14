#NOT WORKING PROBABLY
cmake_minimum_required(VERSION 3.26)
project(owldodgegame C)

set(CMAKE_C_STANDARD 17)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)
set(SDL2_PATH "C:/Users/LenY/dev/uni/sem 1/nagyhz_1/owldodgegame/SDL2-2.30.0/x86_64-w64-mingw32")
include_directories(.)
INCLUDE(FindPkgConfig)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIR} ${SDL2GFX_INCLUDE_DIRS} ${SDL2TTF_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})
add_compile_options(-lSDL2_gfx;-lSDL2_ttf;-lSDL2_image;-lSDL2_mixer)

add_executable(owldodgegame src/main.c
        src/render.c
        src/entity.c
        src/game.c
        src/math_helper.c
        src/menu.c
        src/overlay.c
        src/scoreboard.c
        src/state.c
        include/render.h
        include/entity.h
        include/game.h
        include/macros.h
        include/math_helper.h
        include/menu.h
        include/overlay.h
        include/scoreboard.h
        include/state.h
        )

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARY} ${SDL2TTF_LIBRARIES} ${SDL2IMAGE_LIBRARIES})