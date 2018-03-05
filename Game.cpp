//
// Created by niels on 05/03/18.
//

#include <zconf.h>
#include "Game.h"

Game::Game(AbstractFactory *factory)
{
    Game::factory = factory;
}

void Game::init()
{
    // Create systemmanager and add rendersystem
    Game::manager = new SystemManager();
    manager->registerSystem(factory->createRenderSystem());
    manager->registerSystem(new MovementSystem());
    // Add a pacman
    manager->registerEntity(factory->createPacMan());
}

void Game::run()
{
    for(int i=0;i<10;i++)
    {
        manager->updateSystems();
        usleep(1000000);
    }
}

Game::~Game()
{
    delete factory;
    delete manager;
}

