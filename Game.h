//
// Created by niels on 05/03/18.
//

#ifndef ECS_GAME_H
#define ECS_GAME_H


#include "AbstractFactory.h"
#include "SystemManager.h"
#include "MovementSystem.h"
#include "AISystem.h"
#include "EventSystem.h"

class Game {
public:
    explicit Game(AbstractFactory* factory);
    void init();
    void run();
    ~Game();
private:
    Game() = default;
    AbstractFactory* factory = nullptr;
    SystemManager* manager = nullptr;
    EventSystem* events = nullptr;
};


#endif //ECS_GAME_H
