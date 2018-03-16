
#include "Game.h"
#include "SDL_Factory.h"
#include "Config.h"

int main()
{
    Config* config = new Config("../data/config.xml");
    auto* game = new Game(new SDL_Factory(config), config);
    game->init();
    game->run();
    delete game;
    return 0;
}