#include "entity.h"

#include "manager.h"
#include "components/CPhysXRigidBody.h"

void Entity::Update()
{
    /*for(auto component : components_)
    {
        component->Update();
    }*/
    for (auto component : components_) {
        Manager::GetThreadPool().Enqueue(component->GetPriority(), [component]() {
            component->Update();
            });
    }
}

Entity::~Entity()
{
    Component* rigidBody = nullptr;
    for (auto component : components_)
    {
        if (component->GetType() != "CPhysXRigidBody")
        {
            component->CleanUp();
            delete component;
        }
        else
        {
            rigidBody = component;
        }
    }
    //delete rigidBody lasts
    delete rigidBody;
}