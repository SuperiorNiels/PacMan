
#include "Game.h"
#include "SDL_Factory.h"

int main() {
    auto* game = new Game(new SDL_Factory());
    game->init();
    game->run();
    return 0;
}