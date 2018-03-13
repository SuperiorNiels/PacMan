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
    // Create systemmanager and add rendersystem
    Game::world = new World(collision_map);
    Game::manager = new SystemManager();
    Game::timer = factory->createTimerSystem(60);
    Game::render = factory->createRenderSystem(world,224*4,248*4);
    Game::events = factory->createEventSystem((1.f/render->getTile_width())*2);
    manager->registerSystem(Game::events);
    //manager->registerSystem(new AISystem());
    manager->registerSystem(new MovementSystem(world));
    manager->registerSystem(new CollisionSystem());
    manager->registerSystem(Game::render);

    std::vector<Entity*> map = factory->createWorld(world);
    for(auto& e : map)
        manager->registerEntity(e);

    manager->registerEntity(factory->createPacMan(1, 1));
    //manager->registerEntity(factory->createGhost(120, 105, RED_GHOST));
    //manager->registerEntity(factory->createGhost(88, 105, PINK_GHOST));
    //manager->registerEntity(factory->createGhost(88, 115, BLUE_GHOST));
    //manager->registerEntity(factory->createGhost(120, 115, ORANGE_GHOST));
}

void Game::run()
{
    while(events->getRunning())
    {
        timer->start();
        manager->updateSystems();
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

