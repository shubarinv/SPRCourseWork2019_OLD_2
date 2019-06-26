//
// Created by vhundef on 25.06.19.
//

#include "Game/ScreenManager.h"
#include "Game/UI_Manager.h"
#include "Game/EventManager.h"
#include "Game/Player.h"

int main() {
    ScreenManager screenManager;
    UI_Manager uiManager(&screenManager);
    EventManager eventManager;
    SDL_Event event;
    Player player(&screenManager);
    while (true) {
        event = eventManager.getEvent();
        if (event.type == SDL_QUIT) {
            cout << "EventManager: got ESC button press. Quiting..." << endl;
            break;
        }


    }
    return 0;
}