#include "CCubeBehaviour.h"
#include "components/PhysX/CPhysXRigidBody.h"
#include "manager.h"
#include "prefab/explosion.h"
#include "gamemode/GMCrush.h"

void CCubeBehaviour::Start()
{
    //std::cout << "Cube Start" << std::endl;
    Entity* parent = Manager::FindEntityByID(parent_id_);
    if(parent)
    {
        rigid_body_ = parent->GetComponent<CPhysXRigidBody>()->GetActor()->is<physx::PxRigidDynamic>();
        if(!rigid_body_)
        {
            std::cerr << "Cube has no rigid body" << std::endl;
        }
    }
}

void CCubeBehaviour::Update()
{
    //if rigidbody got hit with a certain level of force, destroy the cube
    if(rigid_body_)
    {
		if (rigid_body_->isSleeping())
		{
			return;
		}
        //Get collision data
        PhysXUserData* userData = static_cast<PhysXUserData*>(rigid_body_->userData);
        for(auto id : userData->collision_ids)
        {
            Entity* entity = Manager::FindEntityByID(id);
            if (entity || rigid_body_->getLinearVelocity().magnitude() >= 4.0f)
            {
                if (entity->GetName() == "Pinball")
                {
                    //Manager::QueueForRemoval(parent_id_);
					destroyed_ = true;
                }
            }
        }

        if (destroyed_ && rigid_body_->getLinearVelocity().magnitude() < 3.0f)
        {
			Explosion* explosion = new Explosion();
			XMFLOAT3 pos = Manager::FindEntityByID(parent_id_)->GetTransform().position;
			explosion->SetPosition(pos);
			Manager::QueueForSpawn(explosion);
            GMCrush* gameMode = dynamic_cast<GMCrush*> (Manager::GetGameMode());
            if (gameMode) {
                gameMode->SetBlocks(gameMode->GetBlocks() - 1);
            }
            Manager::QueueForRemoval(parent_id_);
        }
    }

	
}