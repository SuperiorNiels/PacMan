//
// Created by niels on 05/03/18.
//

#ifndef ECS_GAME_H
#define ECS_GAME_H


#include "AbstractFactory.h"
#include "ECS/SystemManager.h"
#include "Systems/MovementSystem.h"
#include "Systems/AISystem.h"
#include "Systems/EventSystem.h"
#include "Systems/CollisionSystem.h"
#include "World.h"
#include "Systems/RenderSystem.h"

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
    TimerSystem* timer = nullptr;
    RenderSystem* render = nullptr;
    World* world = nullptr;
};


#endif //ECS_GAME_H
