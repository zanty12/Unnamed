#include "PhysXSimulationCallBack.h"

#include <algorithm>

#include "components/CPhysXRigidBody.h"

#include <iostream>

void PhysXSimulationCallBack::onTrigger(physx::PxTriggerPair* pairs, physx::PxU32 count)
{
    //return the name of the trigger
    for (physx::PxU32 i = 0; i < count; i++)
    {
        physx::PxTriggerPair& pair = pairs[i];
        if (pair.status & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
        {
            PhysXUserData* userData0 = static_cast<PhysXUserData*>(pair.triggerActor->userData);
            PhysXUserData* userData1 = static_cast<PhysXUserData*>(pair.otherActor->userData);
            if (userData0 && userData1)
            {
                std::cout << "Trigger detected between " << userData0->name << " and " << userData1->name << std::endl;
            }
        }
    }
}

void PhysXSimulationCallBack::onContact(const physx::PxContactPairHeader& pairHeader, const physx::PxContactPair* pairs, physx::PxU32 nbPairs)
{
    //Got through all the pairs and clear the collision data
    /*for (physx::PxU32 i = 0; i < nbPairs; i++)
    {
        const physx::PxContactPair& cp = pairs[i];
        if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_LOST)
        {
            PhysXUserData* userData0 = static_cast<PhysXUserData*>(pairHeader.actors[0]->userData);
            PhysXUserData* userData1 = static_cast<PhysXUserData*>(pairHeader.actors[1]->userData);
            if (userData0 && userData1)
            {
                userData0->collision_ids.clear();
                userData1->collision_ids.clear();
            }
        }
    }*/
    for (physx::PxU32 i = 0; i < nbPairs; i++)
    {
        const physx::PxContactPair& cp = pairs[i];
        if (cp.events & physx::PxPairFlag::eNOTIFY_TOUCH_FOUND)
        {
            PhysXUserData* userData0 = static_cast<PhysXUserData*>(pairHeader.actors[0]->userData);
            PhysXUserData* userData1 = static_cast<PhysXUserData*>(pairHeader.actors[1]->userData);
            if (userData0 && userData1)
            {
                //if the one of the actor is in the ignore list, skip{
				for (auto tag : userData0->ignore_tags_)
				{
					if (tag == userData1->tag)
					{
						return;
					}
                }
				for (auto tag : userData1->ignore_tags_)
				{
					if (tag == userData0->tag)
					{
						return;
					}
				}
                //std::cout << "Collision detected between " << userData0->name << " and " << userData1->name << std::endl;
                userData0->collision_ids.push_back(userData1->id);
                auto it = std::unique(userData0->collision_ids.begin(), userData0->collision_ids.end());
                userData0->collision_ids.erase(it, userData0->collision_ids.end());

                userData1->collision_ids.push_back(userData0->id);
                it = std::unique(userData1->collision_ids.begin(), userData1->collision_ids.end());
                userData1->collision_ids.erase(it, userData1->collision_ids.end());
            }
        }
    }
}
