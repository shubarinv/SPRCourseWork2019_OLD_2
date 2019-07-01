//
// Created by vhundef on 01.07.19.
//

#ifndef COURSEWORK_WEAPON_H
#define COURSEWORK_WEAPON_H


#include "GameObject.h"
#include "Ship.h"

class Weapon : public GameObject {
private:
    int ammo{40}, power{1};
    bool initialsed{false};
    ScreenManager *screenManager;
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

class Particle : public GameObject {
private:
    bool isOnScreem{true};
public:
    bool isOnScreem1() const {
        return isOnScreem;
    }

    void setIsOnScreem(bool OnScreem) {
        Particle::isOnScreem = OnScreem;
    }
};


#endif //COURSEWORK_WEAPON_H
