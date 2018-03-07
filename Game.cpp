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
    Game::manager = new SystemManager();
    Game::events = factory->createEventSystem();
    manager->registerSystem(factory->createRenderSystem());
    manager->registerSystem(Game::events);
    manager->registerSystem(new MovementSystem());
    manager->registerSystem(new AISystem());
    manager->registerSystem(factory->createCollisionSystem());

    std::vector<Entity*> world = factory->createWorld();
    for(auto* e : world)
        manager->registerEntity(e);

    manager->registerEntity(factory->createPacMan(106, 182));
    manager->registerEntity(factory->createGhost(0, 0, 0));
    manager->registerEntity(factory->createGhost(0, 0, 1));
    manager->registerEntity(factory->createGhost(0, 0, 2));
    manager->registerEntity(factory->createGhost(0, 0, 3));
}

void Game::run()
{
    while(events->getRunning())
        manager->updateSystems();
}

Game::~Game()
{
    delete manager;
    delete factory;
}

