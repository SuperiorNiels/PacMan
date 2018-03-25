//
// Created by niels on 05/03/18.
//

#ifndef ECS_GAME_H
#define ECS_GAME_H

#include "World.h"
#include "Config.h"
#include "AbstractFactory.h"
#include "ECS/SystemManager.h"
#include "Systems/MovementSystem.h"
#include "Systems/AISystem.h"
#include "Systems/EventSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/RenderSystem.h"

class Game
{
public:
    Game() = delete;
    explicit Game(Config* config);
    void init();
    void run();
    void createGame();
    ~Game();
private:
    void clear();
    Config* config = nullptr;
    AbstractFactory* factory = nullptr;
    SystemManager* manager = nullptr;
    EventSystem* events = nullptr;
    TimerSystem* timer = nullptr;
    RenderSystem* render = nullptr;
    World* world = nullptr;
};

#endif //ECS_GAME_H
