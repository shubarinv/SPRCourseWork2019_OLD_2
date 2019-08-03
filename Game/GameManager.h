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
	int elapsed = 0, current = 0, timeSinceSecond = 0, frames = 0, next, avgFPS = 100; //avgFPS - Avg fps per seconds
	int framerate = 59;
public:

	explicit GameManager(ScreenManager *screenMgr, list<Enemy> *EnemyShips) {
		screenManager = screenMgr;
		enemyShips = EnemyShips;
	}

	void setFramerate(int purposedFPS) {
		GameManager::framerate = purposedFPS;
	}

	void setWave(int wv) {
		cout << "Set wave was called...\nWave now " << wv << endl;
		GameManager::wave = wv;
		resetEnemyShips();
		spawnEnemyShips(wave);

	}

	static void checkForHits(Player *ship, Particle *particle) { ///< @bug Doesn't work somewhy
		if ((particle->location.x1 + particle->location.x2) / 2 >= ship->getCoords().x1 &&
		    (particle->location.x1 + particle->location.x2) / 2 <= ship->getCoords().x2 &&
		    particle->location.y1 >= ship->getCoords().y1 &&
		    particle->location.y2 <= ship->getCoords().y2) {
			ship->gotHit((particle->location.x1 + particle->location.x2) / 2);
			ship->setHealth(-25);
			cout << "Player (" << ship << ") got hit" << endl;
			cout << "Particle (" << particle << ") Will now be removed" << endl;
			particle->setIsOnScreem(false);
		}
	}

	static

	void checkForHits(Enemy *ship, Particle *particle) {
		if ((particle->location.x1 + particle->location.x2) / 2 >= ship->getCoords().x1 &&
		    (particle->location.x1 + particle->location.x2) / 2 <= ship->getCoords().x2 &&
		    particle->location.y1 >= ship->getCoords().y1 &&
		    particle->location.y2 <= ship->getCoords().y2) {
			ship->gotHit((particle->location.x1 + particle->location.x2) / 2);
			ship->setHealth(-25);
			cout << "Enemy (" << ship << ") got hit" << endl;
			cout << "Particle (" << particle << ") Will now be removed" << endl;
			particle->setIsOnScreem(false);
		}
	}

	void checkForNewWave() {
		if (enemyShips->empty()) {
			setWave(++wave);
			cout << "==================" << endl << "NEW Wave, now " << wave << endl << "==================" << endl;
		}
	}

	bool swtch = true;

	void capFPS() {
		if (swtch) {
			elapsed = SDL_GetTicks() - current;
			current += elapsed;
			timeSinceSecond += elapsed;
			frames++;
			if (timeSinceSecond >= 1000) {
				timeSinceSecond = 0;
				avgFPS = frames;
				frames = 0;
			}
		} else {
			next = SDL_GetTicks();
			if (next - current < 1000.0 / framerate) {
				SDL_Delay(1000.f / framerate - (next - current));
			}
		}
		swtch = !swtch;
	}

	void enemyShoot(Player *player, Enemy *enemy) {
		call++;
		if (call % 2000000 == 0) {
			if (abs((player->getCoords().x1 + player->getCoords().x2) / 2 -
			        (enemy->getCoords().x1 + enemy->getCoords().x2) / 2) >= 20 &&
			    (abs((player->getCoords().x1 + player->getCoords().x2) / 2 -
			         (enemy->getCoords().x1 + enemy->getCoords().x2) / 2) <= 240)) {
				enemy->weapon.shoot();
			}
		}
	}

private:
	int call = 0;
};


#endif //COURSEWORK_GAMEMANAGER_H
