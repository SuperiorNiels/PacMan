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
#include "Config.h"

class Game {
public:
    Game() = delete;
    Game(AbstractFactory* factory, Config* config);
    void init();
    void run();
    void createGame();
    ~Game();
private:
    Config* config = nullptr;
    AbstractFactory* factory = nullptr;
    SystemManager* manager = nullptr;
    EventSystem* events = nullptr;
    TimerSystem* timer = nullptr;
    RenderSystem* render = nullptr;
    World* world = nullptr;
};


#endif //ECS_GAME_H
