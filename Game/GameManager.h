//
// Created by vhundef on 01.07.19.
//

#ifndef COURSEWORK_GAMEMANAGER_H
#define COURSEWORK_GAMEMANAGER_H


#include "Enemy.h"

class GameManager {
private:
    void resetEnemyShips() {
        enemyShips->clear();
    }

    void spawnEnemyShips(int wv) {
        for (int i = 0; i < wv * 2; ++i) {
            enemyShips->push_back(*new Enemy());
        }

        for (auto &enemyShip : *enemyShips) {
            enemyShip.init(screenManager);
        }
    }


    int wave{0};
    ScreenManager *screenManager;
    list<Enemy> *enemyShips;
public:
    explicit GameManager(ScreenManager *screenMgr, list<Enemy> *EnemyShips) {
        screenManager = screenMgr;
        enemyShips = EnemyShips;
    }

    void setWave(int wv) {
        cout << "Set wave was called...\nWave now " << wv << endl;
        GameManager::wave = wv;
        resetEnemyShips();
        spawnEnemyShips(wave);

    }

    static void checkForHits(Player *ship, Particle *particle) {
        if ((particle->location.x1 + particle->location.x2) / 2 >= ship->getCoords().x1 &&
            (particle->location.x1 + particle->location.x2) / 2 <= ship->getCoords().x2 &&
            particle->location.y1 >= ship->getCoords().y1 &&
            particle->location.y2 <= ship->getCoords().y2) {
            ship->setHealth(-25);
            cout << "Player (" << ship << ") got hit" << endl;
            cout << "Particle (" << particle << ") Will now be removed" << endl;
            particle->setIsOnScreem(false);
        }
    }

    static void checkForHits(Enemy *ship, Particle *particle) {
        if ((particle->location.x1 + particle->location.x2) / 2 >= ship->getCoords().x1 &&
            (particle->location.x1 + particle->location.x2) / 2 <= ship->getCoords().x2 &&
            particle->location.y1 >= ship->getCoords().y1 &&
            particle->location.y2 <= ship->getCoords().y2) {
            ship->setHealth(-25);
            cout << "Enemy (" << ship << ") got hit" << endl;
            cout << "Particle (" << particle << ") Will now be removed" << endl;
            particle->setIsOnScreem(false);
        }
    }
    void checkForNewWave(){
    	if(enemyShips->empty())
    		setWave(++wave);
    }

};


#endif //COURSEWORK_GAMEMANAGER_H
