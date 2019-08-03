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
    ScreenManager *screenManager;
    SDL_Rect particle;
    bool bIsEnemy{true};
public:
    Particle() {
        bIsOnScreen = true;
        initialsed = false;
    }

    void init(ScreenManager *screenMgr, coords loc, bool isEnemy) {
        cout << "Particle was spawned: " << this << endl;
        particle.h = 10;
        particle.w = 5;
        particle.x = (loc.x1 + loc.x2) / 2;
        particle.y = (loc.y1 + loc.y2) / 2;
        bIsEnemy = isEnemy;
        screenManager = screenMgr;
        location.x1 = particle.x;
        location.x2 = particle.x + particle.w;
        initialsed = true;
    }

    bool isOnScreen() const {
        return bIsOnScreen;
    }

    void setIsOnScreem(bool OnScreen) {
        Particle::bIsOnScreen = OnScreen;
    }

    void reDraw() {
        if (!initialsed) throw runtime_error("Error: Particle is UNINITIALISED, but got reDraw command");
        if (initialsed && bIsOnScreen) {
            updatelocation();
            SDL_FillRect(screenManager->getMainSurface(), &particle, 0xff0000);
        } else {
            throw runtime_error("Error: Particle Should have been deleted, but got reDraw command");
        }
    }

private:
    void updatelocation() {
        if (bIsOnScreen) {
            if (particle.y >= screenManager->getScreenHeight() || particle.y <= 0)
                bIsOnScreen = false;
            if (bIsEnemy) particle.y++;
            else particle.y--;
            location.y1 = particle.y;
            location.y2 = particle.y + particle.h;
        }
    }
public:
    static bool removalCheck(Particle prtcl) {
        return !prtcl.isOnScreen();
    }
};




class Weapon : public GameObject {
private:
    int ammo{40}, power{1};
    ScreenManager *screenManager{};
    bool bIsEnemy{true};
public:
    void init(ScreenManager *screenMgr, bool isEnemy) {
        cout << "Weapon was spawned: " << this << endl;
        screenManager = screenMgr;
        bIsEnemy = isEnemy;
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
        particles.push_back(*new Particle());
        particles.back().init(screenManager, location, bIsEnemy);
    }

    int getAmmo() const {
        return ammo;
    }

    void setAmmo(int ammoAmount) {
        Weapon::ammo = ammoAmount;
    }

    void update(coords newloc) {
        location = newloc;
        if (!particles.empty()) {
            for (auto &particle : particles) {
                particle.reDraw();
            }

        }
    }

    list <Particle> particles;
};


#endif //COURSEWORK_WEAPON_H
