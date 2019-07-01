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

};


#endif //COURSEWORK_GAMEMANAGER_H
