
#include "Game.h"
#include "SDL_Factory.h"
#include "Config.h"

int main()
{
    auto* game = new Game(new Config("../data/config.xml"));
    game->init();
    game->run();
    delete game;
    return 0;
}