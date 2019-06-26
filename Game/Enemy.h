//
// Created by vhundef on 26.06.19.
//

#ifndef COURSEWORK_ENEMY_H
#define COURSEWORK_ENEMY_H


#include "Ship.h"

class Enemy : Ship {
public:
    explicit Enemy(ScreenManager *screenMgr) {
        screenManager = screenMgr;
        health = 100;
        movementDirection = 1;
        movementSpeed = 1;
        {
            body.w = 80;
            body.h = 30;
            body.x = 100;
            body.y = 70;
            SDL_FillRect(screenMgr->getMainSurface(), &body, bodyColor);
        }
        location.x1 = body.x;
        location.x2 = body.x + body.w;
        location.y1 = body.y;
        location.y1 = body.y + body.h;
    }


    void reDraw() {
        updateLocation();
        body.x = location.x1;
        SDL_FillRect(screenManager->getMainSurface(), &body, bodyColor);
        /**
         * @bug code bellow will somewhy throw SEGFAULT
         * */
        if (movementDirection == -1) {
            //  Draw_Line(screenManager->getMainSurface(), location.x1, location.y2, location.x1-30, location.y1, 0x00);
        } else {
            // Draw_Line(screenManager->getMainSurface(), location.x2, location.y2, location.x2+1, location.y1, 0xff);
        }
    }
};


#endif //COURSEWORK_ENEMY_H
