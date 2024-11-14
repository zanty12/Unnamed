#include "entity.h"

#include "manager.h"
#include "components/CPhysXRigidBody.h"

void Entity::Update()
{
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
    TaskScheduler::RemoveTask(id_);
}