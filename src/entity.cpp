#include "entity.h"

#include "manager.h"

void Entity::Update()
{
    /*for(auto component : components_)
    {
        component->Update();
    }*/
    for(auto component : components_) {
        Manager::GetThreadPool().Enqueue(component->GetPriority(),[component](){
            component->Update();
        });
    }
}

Entity::~Entity()
{
    for(auto component : components_)
    {
        component->CleanUp();
        delete component;
    }

}