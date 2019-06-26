//
// Created by vhundef on 25.06.19.
//

#ifndef COURSEWORK_UI_MANAGER_H
#define COURSEWORK_UI_MANAGER_H


#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_draw.h>

class UI_Manager {
private:
    TTF_Font *fnt;
    ScreenManager *screenManager = nullptr;
    SDL_Color text_color;
    SDL_Surface *text_surface = nullptr;
public:
    UI_Manager(ScreenManager *screenMgr) {
        screenManager = screenMgr;
        if (TTF_Init()) {
            throw runtime_error("UI_Manager: Failed to init SDL_TTF ");
        }
        fnt = TTF_OpenFont("Roboto-Regular.ttf", 20);
        if (!fnt) {
            printf("TTF_OpenFont: %s\n", TTF_GetError());
            // handle error
        }
    }

    /**
     * @param x - Horizontal position of text (in pixels)
     * @param y - Vertical position of text (in pixels)
     * @param text - Text that you want to add to the screen
     **/
    void drawText(int x, int y, const string &text) {
        text_color.r = 255;
        text_color.g = 255;
        text_color.b = 255;
        text_surface = TTF_RenderUTF8_Solid(fnt, text.c_str(), text_color);

        SDL_Rect textBg;
        textBg.x = x;
        textBg.y = y;

        SDL_BlitSurface(text_surface, nullptr, screenManager->getMainSurface(), &textBg);
        SDL_FreeSurface(text_surface);
        text_surface = nullptr;

    }

    /**
     * @param x - Horizontal position of text (in pixels)
     * @param y - Vertical position of text (in pixels)
     * @param width - width of a button
     * @param height - height if a button
     * @param text - Text that you want to add to the screen
     **/
    void createButton(int x, int y, int width, int height, const string &text, int color) {
        Draw_FillRect(screenManager->getMainSurface(), static_cast<Sint16>(x), static_cast<Sint16>(y),
                      static_cast<Uint16>(width), static_cast<Uint16>(height), color);
        drawText((x + width / 2) - 10 * (text.length() / 2.0), y + height / 2 - 10, text);
    }

};


#endif //COURSEWORK_UI_MANAGER_H
