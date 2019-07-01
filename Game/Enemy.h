//
// Created by vhundef on 26.06.19.
//

#ifndef COURSEWORK_ENEMY_H
#define COURSEWORK_ENEMY_H


#include "Ship.h"

class Enemy : Ship {
private:
    bool initialised;
public:

    Enemy(ScreenManager *screenMgr) {
        init(screenMgr);
        initialised = true;
    }

    Enemy() {
        initialised = false;
    };

    void init(ScreenManager *screenMgr) {
        cout << "Enemy was spawned: " << this << endl;
        health = 100;
        screenManager = screenMgr;
        movementDirection = 1;
        movementSpeed = 1;
        {
            body.w = 80;
            body.h = 30;
            body.x = randIntInRange(0, screenManager->getScreenWidth());
            body.y = 70;
            SDL_FillRect(screenMgr->getMainSurface(), &body, bodyColor);
        }
        location.x1 = body.x;
        location.x2 = body.x + body.w;
        location.y1 = body.y;
        location.y1 = body.y + body.h;

        weapon.init(screenManager);

        initialised = true;
    }

    void reDraw() {
        if (!initialised)throw runtime_error("Error: tried to call reDraw for uninitialised Enemy ship!");
        weapon.shoot();
        updateLocation();
        //cout<< "Enemy("<<this<<") new location: "<<location.x1<<endl;
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
