#include <iostream>
#include "Component.h"
#include "Ghost.h"
#include "PositionSystem.h"

int main() {
    PositionSystem ps = PositionSystem();
    //Ghost g1 = Ghost();
    ps.addEntity(new Ghost());
    for(int i=0;i<10;i++)
    {
        ps.update();
    }
    // Get position component from 6 ghosts and print its id
    //auto* p = g1.getComponentByType<PositionComponent>(0);
    //std::cout << "Position of ghost entity: x: " << p->x << " y: " << p->y << std::endl;
    return 0;
}