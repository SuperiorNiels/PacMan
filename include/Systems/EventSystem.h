//
// Created by niels on 06/03/18.
//

#ifndef ECS_EVENTSYSTEM_H
#define ECS_EVENTSYSTEM_H

#include "../ECS/ECS.h"
#include "../Pacman/PacMan_Components.h"

using namespace ECS;

namespace Systems {
    class EventSystem : public System {
    public:
        explicit EventSystem(std::map<Pacman::events_numbers, bool> *events) {
            // System settings
            component_types = {Pacman::PLAYER_INPUT_COMPONENT};
            pausable = false;
            EventSystem::events = events;
        }

        const bool getRunning() { return running; };
        std::map<Pacman::events_numbers, bool> *events = nullptr;
    protected:
        bool running = true;
    };
};

#endif //ECS_EVENTSYSTEM_H
