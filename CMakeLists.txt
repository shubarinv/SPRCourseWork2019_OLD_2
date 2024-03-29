cmake_minimum_required(VERSION 3.13)
project(CourseWork)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH})
find_package(SDL REQUIRED)
find_package(SDL_ttf REQUIRED)
find_package(SDL_draw REQUIRED)
# Workaround for the non-working REQUIRED flag
if (NOT SDL_FOUND)
    message(FATAL_ERROR "SDL not found!")
endif (NOT SDL_FOUND)

link_libraries(
        ${SDL_LIBRARY}
        ${SDLDRAW_LIBRARY}
        ${SDLTTF_LIBRARY}
        SDLmain # Sadly not included in SDL_LIBRARY variable
)
set(CMAKE_CXX_STANDARD 17)
add_executable(CourseWork Driver.cpp Game/ScreenManager.h Game/UI_Manager.h Game/Player.h Game/Ship.h Game/GameObject.h Game/Enemy.h Game/GameManager.h Game/Weapon.h)