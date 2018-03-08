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
    manager->registerSystem(factory->createTimerSystem());

    std::vector<Entity*> world = factory->createWorld();
    for(auto* e : world)
        manager->registerEntity(e);

    manager->registerEntity(factory->createPacMan(106, 182));
    manager->registerEntity(factory->createGhost(0, 0, RED_GHOST));
    manager->registerEntity(factory->createGhost(0, 0, PINK_GHOST));
    manager->registerEntity(factory->createGhost(0, 0, BLUE_GHOST));
    manager->registerEntity(factory->createGhost(0, 0, ORANGE_GHOST));
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

