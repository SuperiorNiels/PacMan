//
// Created by niels on 05/03/18.
//

#include "Game.h"

Game::Game(AbstractFactory *factory)
{
    Game::factory = factory;
}

void Game::init()
{
    Game::world = new World(collision_map);
    Game::manager = new SystemManager();
    Game::timer = factory->createTimerSystem(60);
    Game::render = factory->createRenderSystem(world,224*3,248*3);
    Game::events = factory->createEventSystem(1);
    manager->registerSystem(Game::events);
    manager->registerSystem(new AISystem());
    manager->registerSystem(new MovementSystem(world));
    manager->registerSystem(new CollisionSystem());
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
        }
        timer->cap();
    }
}

Game::~Game()
{
    delete manager;
    delete factory;
    delete world;
    delete timer;
}

