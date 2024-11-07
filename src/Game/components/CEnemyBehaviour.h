#pragma once
#include <DirectXMath.h>

#include "components/depreciated/CCollider3D.h"
#include "manager.h"
#include "components/Component.h"
#include "gamemode/GMShooting.h"
#include "prefab/explosion.h"

class CEnemyBehaviour : public Component
{
private:
public:
    CEnemyBehaviour() : Component("EnemyBehaviour",PhysicsBehaviour)
    {
    };
    ~CEnemyBehaviour() override = default;

    void Start() override
    {
    }

    void Update() override
    {
        //if the enemy got hit by a bullet, remove it
        Entity* entity = Manager::FindEntityByID(parent_id_);
        std::vector<CCollider3D*> collided = entity->GetComponent<CCollider3D>()->GetCollided();
        for(auto other : collided)
        {
            if(Manager::FindEntityByID(other->GetParentID())->GetTag() == "Bullet")
            {
                Manager::QueueForRemoval(parent_id_);
                //add point to the player
                Shooting* game_mode = dynamic_cast<Shooting*>(Manager::GetGameMode());
                if(game_mode)
                    game_mode->AddPoint();
                Explosion* explosion = new Explosion();
                explosion->SetPosition(entity->GetTransform().position);
                explosion->Start();
            }
        }
        /*if (collided.size() > 0)
        {
            if(entity->GetComponent<CCollider3D>()->GetCollided()[0]->GetParentID()GetTag() == "Bullet"))
            Manager::QueueForRemoval(parent_id_);
            //add point to the player
            DefaultGameMode* game_mode = dynamic_cast<DefaultGameMode*>(Manager::GetGameMode());
            if(game_mode)
                game_mode->AddPoint();
            Explosion* explosion = new Explosion();
            explosion->SetPosition(entity->GetTransform()->position);
            explosion->Start();
        }*/
    }

    void CleanUp() override
    {
    }
};
