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
    Game::render = factory->createRenderSystem(world,config->getScreen_x(),config->getScreen_y());
    Game::events = factory->createEventSystem();
    manager->registerSystem(Game::events);
    //manager->registerSystem(new AISystem());
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
        timer->start();
        manager->updateSystems();
        manager->updateEntities();
        for(auto event : events->getEvents())
        {
            if(event == R_BUTTON)
            {
                manager->clearEntities();
                createGame();
                //std::cout << "Game reset!" << std::endl;
            }
            else if(event == P_BUTTON)
            {
                manager->removeSystem(Game::render);
                delete Game::render;
                Game::render = factory->createRenderSystem(world,224,248);
                manager->registerSystem(Game::render);
                manager->clearEntities();
                createGame();
            }
            else if(event == O_BUTTON)
            {
                manager->removeSystem(Game::render);
                delete Game::render;
                Game::render = factory->createRenderSystem(world,224*3,248*3);
                manager->registerSystem(Game::render);
                manager->clearEntities();
                createGame();
            }
            else if(event == M_BUTTON)
            {
                manager->lol();
                manager->updateEntities();
            }
        }
        timer->cap();
    }
}

void Game::clear()
{
    delete manager;
    delete world;
    delete timer;
}

Game::~Game()
{
    clear();
    delete config;
    delete factory;
}

