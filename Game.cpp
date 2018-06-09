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
    manager->registerSystem(new GameplaySystem());
    manager->registerSystem(Game::events);
    manager->registerSystem(new AISystem(world));
    manager->registerSystem(new CollisionSystem());
    manager->registerSystem(new MovementSystem(world));
    manager->registerSystem(Game::render);
    createEntities();
}

void Game::createEntities()
{
    std::vector<Entity*> map = factory->createWorldEntities(world);
    for(auto& e : map)
    {
        if(e->hasComponentType(PLAYER_INPUT_COMPONENT))
            Game::player = e;
        manager->registerEntity(e);
    }

}

void Game::run()
{
    auto* pause_text = factory->createTextComponent("../data/Joystix.TTF", 22);
    pause_text->text = "Press space to start.";
    player->addComponent(pause_text);
    paused = true; // start game paused
    manager->updateSystems();
    
    while(events->getRunning())
    {
        if(events->events.find(PAUSE_GAME) != events->events.end())
        {
            paused = !paused;
            if(paused) {
                Game::player->addComponent(pause_text);
                manager->updateEntities();
                manager->updateSystems();
            } else {
                Game::player->removeComponentByType(TEXT_COMPONENT);
            }
        }

        timer->fpsStart();
        if(!paused) {
            manager->updateSystems();
            manager->updateEntities();
        } else {
            manager->updateUnpausableSystems();
        }
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

