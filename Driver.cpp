//
// Created by vhundef on 25.06.19.
//

#include "Game/ScreenManager.h"
#include "Game/UI_Manager.h"
#include "Game/EventManager.h"
#include "Game/Player.h"
#include "Game/Enemy.h"
#include "Game/GameManager.h"

/*
 * global vars
 * */
// ===== GameManagers initialisation ==== //
ScreenManager screenManager;
UI_Manager uiManager(&screenManager);
EventManager eventManager;
SDL_Event event;
Player player(&screenManager);
list<Enemy> enemyShips;
GameManager gmManager(&screenManager, &enemyShips);

bool stopThreads = false;

/**
 * @brief Draws background(sky, water)
 **/
void drawBg(ScreenManager *screenMgr) {
    screenMgr->draw_Rect(0, 0, screenMgr->getScreenWidth(), 100, 0x87CEEB);
    screenMgr->draw_Rect(0, 100, screenMgr->getScreenWidth(), screenMgr->getScreenHeight(), 0x006994);
}

int showMainMenu(EventManager *eventMgr, ScreenManager *screenMgr, UI_Manager *UI_Mgr) {
    screenMgr->draw_Rect(0, 0, screenMgr->getScreenWidth(), screenMgr->getScreenHeight(), 0xffffff);
    UI_Mgr->createButton(screenMgr->getScreenWidth() / 2 - 120, 180, 250, 60, "Start new game", 0xb791d8, 0x0);
    UI_Mgr->createButton(screenMgr->getScreenWidth() / 2 - 120, 280, 250, 60, "Leader Board", 0xb791d8, 0x0);
    UI_Mgr->createButton(screenMgr->getScreenWidth() / 2 - 120, 380, 250, 60, "Quit", 0xb791d8, 0x0);
    screenMgr->updateScreen();
    SDL_Event event;
    while (true) {
        event = eventMgr->getEvent();
        if (event.type == SDL_QUIT) {
            cout << "EventManager: got ESC button press. Quiting..." << endl;
            return -1;
        }

        if ((eventMgr->getMousePosX() > screenMgr->getScreenWidth() / 2 - 120) &&
            (eventMgr->getMousePosX() < screenMgr->getScreenWidth() / 2 + 130) && (eventMgr->getMousePosY() > 180) &&
            (eventMgr->getMousePosY() < 240) &&
            (event.type == SDL_MOUSEBUTTONDOWN)) {
            break;
        }
        if ((eventMgr->getMousePosX() > screenMgr->getScreenWidth() / 2 - 120) &&
            (eventMgr->getMousePosX() < screenMgr->getScreenWidth() / 2 + 130) && (eventMgr->getMousePosY() > 280) &&
            (eventMgr->getMousePosY() < 340) &&
            (event.type == SDL_MOUSEBUTTONDOWN)) {
            throw runtime_error("NOT YET IMPLEMENTED");
        }
        if ((eventMgr->getMousePosX() > screenMgr->getScreenWidth() / 2 - 120) &&
            (eventMgr->getMousePosX() < screenMgr->getScreenWidth() / 2 + 130) && (eventMgr->getMousePosY() > 380) &&
            (eventMgr->getMousePosY() < 440) &&
            (event.type == SDL_MOUSEBUTTONDOWN)) {
            cout << "MainMenu: Quit button pressed. Quiting..." << endl;
            stopThreads = true;
            return -1;
        }
    }
    return 0;
}

int th_checkHitsPlayer(void *unused) {
    while (!stopThreads) {
        for (auto &enemyShip : enemyShips) {
            for (auto &particle : player.weapon.particles) {
                if (particle.isOnScreen())
                    gmManager.checkForHits(&enemyShip, &particle);
            }
        }
    }
    cout << "Thread (checkHitsPlayer) got stop command... Quiting" << endl;
}

int th_checkHitsEnemy(void *unused) {
    while (!stopThreads) {
        for (auto &enemyShip : enemyShips) {
            for (auto &particle : enemyShip.weapon.particles) {
                gmManager.checkForHits(&player, &particle);
            }
        }
    }
    cout << "Thread (checkHitsEnemy) got stop command... Quiting" << endl;
}

int main() {

    gmManager.setWave(1);

    SDL_Thread *checkHitsPlayer_Thread;
    checkHitsPlayer_Thread = SDL_CreateThread(th_checkHitsPlayer, nullptr);
    if (checkHitsPlayer_Thread == nullptr) {
        fprintf(stderr, "Unable to create thread: %s\n", SDL_GetError());
        throw;
    }

    SDL_Thread *checkHitsEnemy_Thread;
    checkHitsEnemy_Thread = SDL_CreateThread(th_checkHitsEnemy, nullptr);
    if (checkHitsEnemy_Thread == nullptr) {
        fprintf(stderr, "Unable to create thread: %s\n", SDL_GetError());
        throw;
    }

    // ===== Show mainMenu ===== //

    if (showMainMenu(&eventManager, &screenManager, &uiManager) == -1) return 0;

    // ===== Game itself ====== //
    while (true) {

        drawBg(&screenManager);
        uiManager.drawHUD(player.getHealth(), player.getMoney());

        event = eventManager.getEvent();
        {
            if (event.type == SDL_QUIT) {
                cout << "EventManager: got ESC button press. Quiting..." << endl;
                stopThreads = true;
                SDL_WaitThread(checkHitsPlayer_Thread, nullptr);
                SDL_WaitThread(checkHitsEnemy_Thread, nullptr);
                break;
            }
            if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_LEFT)
                player.setMovementDirection(-1);

            if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_RIGHT)
                player.setMovementDirection(1);

            if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_DOWN)
                player.setMovementSpeed(0);

            if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_UP)
                player.setMovementSpeed(1);
            if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE)
                player.shoot();
        }
        player.reDraw();

        ///@brief reDraws all enemy ships
        for (auto &enemyShip : enemyShips) {
            enemyShip.reDraw();
        }
        screenManager.updateScreen();


    }
    return 0;
}