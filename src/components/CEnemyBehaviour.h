#pragma once
#include <DirectXMath.h>

#include "CCollider3D.h"
#include "manager.h"
#include "Component.h"
#include "objects/explosion.h"

class CEnemyBehaviour : public Component
{
private:
public:
    CEnemyBehaviour() : Component("EnemyBehaviour")
    {
    };
    ~CEnemyBehaviour() override = default;

    void Start() override
    {
    }

    void Update() override
    {
        //if the enemy got hit by a bullet, remove it
        Entity* entity = Manager::FindEntity(parent_id_);
        if (entity->GetComponent<CCollider3D>()->GetCollided().size() > 0)
        {
            Manager::QueueForRemoval(parent_id_);
            Explosion* explosion = new Explosion();
            explosion->SetPosition(entity->GetTransform()->position);
            explosion->Start();
        }
    }

    void CleanUp() override
    {
    }
};
