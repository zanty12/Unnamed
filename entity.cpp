#include "entity.h"

Entity::~Entity()
{
    for(auto component : components_)
    {
        component->CleanUp();
        delete component;
    }

}