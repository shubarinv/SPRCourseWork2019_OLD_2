//
// Created by vhundef on 25.06.19.
//

#ifndef COURSEWORK_SCREENMANAGER_H
#define COURSEWORK_SCREENMANAGER_H

#include <SDL/SDL.h>
#include <exception>
#include <stdexcept>
#include <iostream>

using namespace std;

class ScreenManager {

private:
    Sint16 max_x{1280}, max_y{720}; ///< @var max_x- Screen width. @var max_y screen height.
    SDL_Surface *mainSurface;
public:

    ScreenManager() { ///< @brief Trying to init SDL
        mainSurface = SDL_SetVideoMode(max_x, max_y, 16, SDL_ANYFORMAT | SDL_DOUBLEBUF);
        if (!mainSurface) {
            throw runtime_error("ScreenManager: Failed to init SDL\n" + (string) SDL_GetError());
        }
        SDL_WM_SetCaption("Курсовая rev 2.0", nullptr);
    }

    void updateScreen() {
        SDL_UpdateRect(mainSurface, 0, 0, max_x, max_y);
    }

    ~ScreenManager() {
        SDL_FreeSurface(mainSurface);
        SDL_Quit();
    }

    // === GETTERS AND SETTERS ====

    SDL_Surface *
    getMainSurface() const { ///<@brief returns pointer to surface that contains every single thing on screen
        return mainSurface;
    }

    Sint16 getScreenWidth() {
        return max_x;
    }

    Sint16 getScreenHeight() {
        return max_y;
    }
};


#endif //COURSEWORK_SCREENMANAGER_H
