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
    Game::world = new World(config->getWorld_map());
    Game::manager = new SystemManager();
    Game::timer = factory->createTimerSystem(config->getFps());
    Game::render = factory->createRenderSystem(world,config->getScreen_x(),config->getScreen_y(),timer);
    Game::events = new std::map<events_numbers, bool>();
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
    player->addComponent(pause_text);
    paused = true; // start game paused
    manager->updateSystems();

    // Game loop
    while (eventSystem->getRunning())
    {
        timer->fpsStart();
        checkEvents();
        if(!paused) {
            manager->updateSystems();
            manager->updateEntities();
        } else {
            manager->updateUnpausableSystems();
        }
        timer->fpsCap();
    }
}

void Game::checkEvents() {
    if (events->find(PAUSE_GAME) != events->end()) {
        paused = !paused;
        if (paused) {
            pause_text->text = "Paused. Press space to resume.";
            Game::player->addComponent(pause_text);
            manager->updateEntities();
            manager->updateSystems();
        } else {
            Game::player->removeComponentByType(TEXT_COMPONENT);
        }
    }

    if (events->find(RESTART) != events->end()) {
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

    auto *sc = player->getComponentByType<ScoreComponent>(SCORE_COMPONENT);
    auto *lc = player->getComponentByType<LivesComponent>(LIVES_COMPONENT);

    if (events->find(RESET) != events->end()) {
        reset();
        lc->lives--;
        paused = true;
        pause_text->text = "You died! Press space to start.";
        Game::player->addComponent(pause_text);
        manager->updateEntities();
        manager->updateSystems();
    }

    if (manager->entitiesWithComponent(POINTS_COMPONENT) - 4 == 0 &&
        manager->entitiesWithComponent(ENERGIZER_COMPONENT) == 0) {
        struct timespec tim1{}, tim2{};
        tim1.tv_sec = 2;
        tim1.tv_nsec = 0L;
        nanosleep(&tim1, &tim2);

        // all points are taken, go to next level
        Game::player->removeComponentByType(TEXT_COMPONENT);
        int score = sc->score;
        int lives = lc->lives;

        manager->clearEntities();
        createEntities();

        auto *new_sc = player->getComponentByType<ScoreComponent>(SCORE_COMPONENT);
        auto *new_lc = player->getComponentByType<LivesComponent>(LIVES_COMPONENT);
        new_sc->score = score;
        new_lc->lives = lives;

        pause_text->text = "New Level! Press space to start.";
        player->addComponent(pause_text);
        paused = true; // start game paused
        manager->updateSystems();
    }

    if (events->find(TEST) != events->end()) {

        for (auto e : manager->entities) {
            if (e.second->hasComponentType(POINTS_COMPONENT)) {
                auto *ac = new AIComponent();
                ac->player = player;
                ac->timer = factory->createTimerSystem(config->getFps());
                ac->state = CHASE;
                ac->time_to_wait = 10000000;
                e.second->addComponent(ac);
                auto *mc = new MovableComponent();
                mc->speed = 80;
                e.second->addComponent(mc);
            }

        }
    }
}

void Game::reset() {
    auto *lc = player->getComponentByType<LivesComponent>(LIVES_COMPONENT);
    auto *pc = player->getComponentByType<PositionComponent>(POSITION_COMPONENT);
    pc->x = lc->start_x;
    pc->y = lc->start_y;
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

