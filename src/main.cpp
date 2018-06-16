
#include "../include/Pacman/Game.h"

int main(int argc, char *argv[])
{
    auto* game = new Game(new Config("../data/config.xml"));
    game->init();
    game->run();
    delete game;
    return 0;
}