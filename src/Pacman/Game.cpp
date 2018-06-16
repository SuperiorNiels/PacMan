//
// Created by niels on 05/03/18.
//

#include "../../include/Pacman/Game.h"

namespace Pacman {

    Game::Game(Config *config) {
        Game::config = config;
        Game::factory = config->getFactory();
        Game::events = new std::map<events_numbers, bool>();
    }

    void Game::init() {
        clear();
        Game::world = new World(config->getWorld_map());
        Game::manager = new SystemManager();
        Game::timer = factory->createTimerSystem(config->getFps());
        Game::render = factory->createRenderSystem(world, config->getScreen_x(), config->getScreen_y(), timer);
        Game::eventSystem = factory->createEventSystem(Game::events);
        manager->registerSystem(Game::eventSystem);
        manager->registerSystem(new AISystem(world));
        manager->registerSystem(new CollisionSystem(Game::events));
        manager->registerSystem(new MovementSystem(world));
        manager->registerSystem(Game::render);
        Game::pause_text = factory->createTextComponent();
        pause_text->text = "Press space to start.";
        createEntities();
    }

    void Game::createEntities() {
        std::vector<Entity *> map = factory->createWorldEntities(world);
        for (auto &e : map) {
            if (e->hasComponentType(PLAYER_INPUT_COMPONENT))
                Game::player = e;
            manager->registerEntity(e);
        }
    }

    void Game::run() {
        player->addComponent(pause_text);
        paused = true; // start game paused
        manager->updateSystems();

        // Game loop
        while (eventSystem->getRunning()) {
            timer->fpsStart();
            checkEvents();
            if (!paused) {
                manager->updateSystems();
                manager->updateEntities();
            } else {
                manager->updateUnpausableSystems();
            }
            timer->fpsCap();
        }
    }

    void Game::checkEvents() {
        auto *player_component = player->getComponentByType<PlayerComponent>(PLAYER_COMPONENT);

        if (events->find(PAUSE_GAME) != events->end()) {
            paused = !paused;
            if (paused) {
                pause_text->text = "Paused. Press space to resume.";
                Game::player->addComponent(pause_text);
                manager->updateEntities();
                manager->updateSystems();
            } else {
                Game::player->removeComponentByType(TEXT_COMPONENT);
                if (player_component->lives <= 0)
                    events->operator[](RESTART) = true;
            }
        }

        if (events->find(RESTART) != events->end()) {
            pause_text->text = "Press space to start.";
            Game::player->removeComponentByType(TEXT_COMPONENT);
            manager->clearEntities();
            createEntities();
            player->addComponent(pause_text);
            paused = true; // start game paused
            manager->updateSystems();
        }

        // if game paused, do not check further events
        if (paused)
            return;

        if (events->find(RESET) != events->end()) {
            reset();
            player_component->lives--;
            if (player_component->lives <= 0 && !paused) {
                pause_text->text = "Game Over!";
            } else {
                pause_text->text = "You died! Press space to start.";
            }
            paused = true;
            Game::player->addComponent(pause_text);
            manager->updateEntities();
            manager->updateSystems();
        }

        if (manager->entitiesWithComponent(POINTS_COMPONENT) - 4 == 0 &&
            manager->entitiesWithComponent(ENERGIZER_COMPONENT) == 0) {
            // all points are taken, go to next level
            player_component->level++;
            Game::player->removeComponentByType(TEXT_COMPONENT);
            Game::player->removeComponentByType(PLAYER_COMPONENT);

            manager->clearEntities();
            createEntities();
            player->destoryComponentByType(PLAYER_COMPONENT);
            player->addComponent(player_component);

            for (auto e : manager->entities) {
                if (e.second->hasComponentType(AI_COMPONENT)) {
                    auto *ac = e.second->getComponentByType<AIComponent>(AI_COMPONENT);
                    ac->time_scale += 50;
                }
            }

            pause_text->text = "New Level! Press space to start.";
            player->addComponent(pause_text);
            paused = true; // start game paused
            manager->updateSystems();
        }

        if (events->find(TEST) != events->end()) {
            for (auto e : manager->entities) {
                if (e.second->hasComponentType(POINTS_COMPONENT) || e.second->hasComponentType(ENERGIZER_COMPONENT)) {
                    auto *pc = e.second->getComponentByType<PositionComponent>(POSITION_COMPONENT);
                    auto *ac = new AIComponent();
                    ac->player = player;
                    ac->timer = factory->createTimerSystem(config->getFps());
                    ac->state = CHASE;
                    ac->time_to_wait = 10000000;
                    ac->home_x = pc->x;
                    ac->home_y = pc->y;
                    e.second->addComponent(ac);
                    auto *mc = new MovableComponent();
                    mc->speed = 60;
                    mc->animate = true;
                    e.second->addComponent(mc);
                }

            }
        }
    }

    void Game::reset() {
        auto *player_component = player->getComponentByType<PlayerComponent>(PLAYER_COMPONENT);
        auto *pc = player->getComponentByType<PositionComponent>(POSITION_COMPONENT);
        pc->x = player_component->start_x;
        pc->y = player_component->start_y;
        auto *mc = player->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
        mc->state = IDLE;
        mc->time = 0;
        for (auto entity : manager->entities) {
            // Reset Ghosts
            if (entity.second->hasComponentType(AI_COMPONENT)) {
                auto *pc = entity.second->getComponentByType<PositionComponent>(POSITION_COMPONENT);
                auto *ai = entity.second->getComponentByType<AIComponent>(AI_COMPONENT);
                auto *mc = entity.second->getComponentByType<MovableComponent>(MOVABLE_COMPONENT);
                mc->state = IDLE;
                mc->time = 0;
                pc->x = ai->home_x;
                pc->y = ai->home_y;
                ai->state = HOME;
            }
        }
    }

    void Game::clear() {
        delete manager;
        delete world;
    }

    Game::~Game() {
        clear();
        delete config;
        delete factory;
    }

};
