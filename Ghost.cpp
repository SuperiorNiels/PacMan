//
// Created by niels on 04/03/18.
//

#include "Ghost.h"

Ghost::Ghost()
{
    addComponent(new PositionComponent);
    addComponent(new RenderComponent);
}