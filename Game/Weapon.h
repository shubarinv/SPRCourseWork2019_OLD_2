//
// Created by vhundef on 01.07.19.
//

#ifndef COURSEWORK_WEAPON_H
#define COURSEWORK_WEAPON_H


#include <list>
#include "GameObject.h"
#include "Ship.h"

class Particle : public GameObject {
private:
    bool bIsOnScreen{true};
public:
    bool isOnScreen() const {
        return bIsOnScreen;
    }

    void setIsOnScreem(bool OnScreen) {
        Particle::bIsOnScreen = OnScreen;
    }
};

class Weapon : public GameObject {
private:
    int ammo{40}, power{1};
    bool initialsed{false};
    ScreenManager *screenManager;
    list <Particle> particles;
public:
    void init(ScreenManager *screenMgr) {
        initialsed = true;
    }

    Weapon() {
        initialsed = false;
    }

    int getPower() const {
        return power;
    }

    void setPower(int pwr) {
        Weapon::power = pwr;
    }

    void shoot() {
        if (!initialsed) throw runtime_error("ERROR: attempt to call shoot on uninitialised Weapon instance\n");
    }

    int getAmmo() const {
        return ammo;
    }

    void setAmmo(int ammoAmount) {
        Weapon::ammo = ammoAmount;
    }

};




#endif //COURSEWORK_WEAPON_H
