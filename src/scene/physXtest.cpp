#include "physXtest.h"
#include "manager.h"
#include "entity.h"
#include "components/CPhysXBox.h"
#include "components/CPhysXRigidBody.h"

void physXtest::Setup()
{
    Entity* box = Manager::MakeEntity();
    box->AddComponent(new CPhysXRigidBody(false));
    box->AddComponent(new CPhysXBox());
    box->Start();
}
