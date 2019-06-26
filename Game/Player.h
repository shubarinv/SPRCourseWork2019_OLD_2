//
// Created by vhundef on 26.06.19.
//

#ifndef COURSEWORK_PLAYER_H
#define COURSEWORK_PLAYER_H

#include "Ship.h"

class Player : Ship {
public:
    explicit Player(ScreenManager *screenMgr) {
        screenManager = screenMgr;
        health = 100;
        movementDirrection = 1;
        movementSpeed = 0;
        //shipParts.push_back();
    }
};


#endif //COURSEWORK_PLAYER_H
