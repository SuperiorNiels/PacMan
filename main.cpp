#include <iostream>
#include "ECS/ECS.h"
#include "SystemManager.h"
#include "SDL_RenderSystem.h"

int main() {
    SystemManager manager = SystemManager();
    manager.registerSystem(new SDL_RenderSystem());
    manager.registerEntity(new Entity());
    return 0;
}