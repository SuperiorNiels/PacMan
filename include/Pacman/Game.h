//
// Created by niels on 05/03/18.
//

#ifndef ECS_GAME_H
#define ECS_GAME_H

#include "World.h"
#include "../Config.h"
#include "../AbstractFactory.h"
#include "../ECS/SystemManager.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/AISystem.h"
#include "../Systems/EventSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/RenderSystem.h"

using namespace Systems;

namespace Pacman {
    class Game {
    public:
        Game() = delete;

        explicit Game(Config *config);

        void init();

        void run();

        ~Game();

    private:
        void clear();

        void createEntities();

        void checkEvents();

        void reset();

        bool paused = false;
        World *world = nullptr;
        Config *config = nullptr;
        Entity *player = nullptr;
        TimerSystem *timer = nullptr;
        TextComponent *pause_text = nullptr;
        AbstractFactory *factory = nullptr;
        SystemManager *manager = nullptr;
        RenderSystem *render = nullptr;
        EventSystem *eventSystem = nullptr;
        std::map<events_numbers, bool> *events;
    };
};

#endif //ECS_GAME_H
