//
// Created by vhundef on 25.06.19.
//

#ifndef COURSEWORK_SHIP_H
#define COURSEWORK_SHIP_H

#include <SDL/SDL.h>
#include <SDL/SDL_draw.h>
#include "GameObject.h"
#include "ScreenManager.h"
#include <list>

using namespace std;

class Ship : GameObject {
protected:
    int health{0}, movementDirrection{0}, movementSpeed{0};

    ScreenManager *screenManager = nullptr;
    list<SDL_Rect> shipParts;
    // list<int> hitLocX;
    coords location;

public:
    coords getCoords() {
        return location;
    }

    void setHealth(int deltaHealth) {
        health += deltaHealth;
    }
};


#endif //COURSEWORK_SHIP_H
