//
// Created by niels on 05/03/18.
//

#include "Game.h"

Game::Game(Config* config)
{
    Game::config = config;
    Game::factory = config->getFactory();
}

void Game::init()
{
    clear();
    Game::world = new World(config->getCollision_map());
    Game::manager = new SystemManager();
    Game::timer = factory->createTimerSystem(config->getFps());
    Game::render = factory->createRenderSystem(world,config->getScreen_x(),config->getScreen_y(),timer);
    Game::events = factory->createEventSystem();
    manager->registerSystem(Game::events);
    manager->registerSystem(new AISystem());
    manager->registerSystem(new CollisionSystem());
    manager->registerSystem(new MovementSystem(world));
    manager->registerSystem(Game::render);
    createGame();
}

void Game::createGame()
{
    std::vector<Entity*> map = factory->createWorldEntities(world);
    for(auto& e : map)
        manager->registerEntity(e);
}

void Game::run()
{
    while(events->getRunning())
    {
        timer->fpsStart();
        manager->updateSystems();
        manager->updateEntities();
        timer->fpsCap();
    }
}

void Game::clear()
{
    delete manager;
    delete world;
}

Game::~Game()
{
    clear();
    delete config;
    delete factory;
}

