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

    void checkForHits(Player *ship, Particle *particle) {
        if ((particle->location.x1 + particle->location.x2) / 2 >= ship->getCoords().x1 &&
            (particle->location.x1 + particle->location.x2) / 2 <= ship->getCoords().x2 &&
            particle->location.y1 >= ship->getCoords().y1 &&
            particle->location.y2 <= ship->getCoords().y2) {
            cout << "Player (" << ship << ") got hit" << endl;
            cout << "Particle (" << particle << ") Will now be removed" << endl;
            particle->setIsOnScreem(false);
        }
    }

    void checkForHits(Enemy *ship, Particle *particle) {
        /*  cout<<"____________________________________"<<endl;
          if((particleLoc.x1 + particleLoc.x2) / 2 >= ship->getCoords().x1)
              cout<<"By X1- OK"<<endl;
          if((particleLoc.x1 + particleLoc.x2) / 2 <= ship->getCoords().x2)
              cout<<"By X2- OK"<<endl;
          if(particleLoc.y1 >= ship->getCoords().y1)
              cout<<"By Y1- OK"<<endl;
          if(particleLoc.y2 <= ship->getCoords().y2)
              cout<<"By Y2- OK"<<endl;
          cout<<"X1 "<<particleLoc.x1<<" "<<ship->getCoords().x1<<endl;
          cout<<"X2 "<<particleLoc.x2<<" "<<ship->getCoords().x2<<endl;
          cout<<"Y1 "<<particleLoc.y1<<" "<<ship->getCoords().y1<<endl;
          cout<<"Y2 "<<particleLoc.y2<<" "<<ship->getCoords().y2<<endl;
          cout<<"____________________________________"<<endl;*/
        if ((particle->location.x1 + particle->location.x2) / 2 >= ship->getCoords().x1 &&
            (particle->location.x1 + particle->location.x2) / 2 <= ship->getCoords().x2 &&
            particle->location.y1 >= ship->getCoords().y1 &&
            particle->location.y2 <= ship->getCoords().y2) {
            cout << "Enemy (" << ship << ") got hit" << endl;
            cout << "Particle (" << particle << ") Will now be removed" << endl;
            particle->setIsOnScreem(false);
        }
    }

};


#endif //COURSEWORK_GAMEMANAGER_H
