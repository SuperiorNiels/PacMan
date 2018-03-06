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
    // Add a pacman
    manager->registerEntity(factory->createPacMan(283,283));
    manager->registerEntity(factory->createGhost(0,0));
}

void Game::run()
{
    while(events->getRunning())
    {
        manager->updateSystems();
    }
}

Game::~Game()
{
    delete manager;
    delete factory;
}

