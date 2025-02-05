#include "JointDemo.h"

#include "entity.h"
#include "manager.h"
#include "components/CModelRenderer.h"
#include "components/PhysX/CPhysXBox.h"
#include "components/PhysX/CPhysXRigidBody.h"

void JointDemo::Setup()
{
    //make 2 cubes and connect them with a joint
    Entity* cube1 = Manager::MakeEntity("Cube1");
    Transform::MoveTo(cube1->GetTransform(), XMFLOAT3(0.0f, 6.0f, 0.0f));
    Transform::ScaleTo(cube1->GetTransform(), XMFLOAT3(0.2f, 0.2f, 0.2f));
    cube1->SetTag("Cube");
    //add a model renderer
    CModelRenderer* modelRenderer = new CModelRenderer();
    cube1->AddComponent(modelRenderer);
    modelRenderer->Load("asset\\model\\WoodenCrate.obj");
    //add a rigid body
    CPhysXRigidBody* rigidBody = new CPhysXRigidBody(true);
    cube1->AddComponent(rigidBody);
    //add a physx box
    CPhysXBox* physXBox = new CPhysXBox();
    physXBox->SetMaterial(1.0f, 1.0f, 0.0f);
    physXBox->SetSimulate(true);
    physXBox->SetQuery(false);
    cube1->AddComponent(physXBox);
    cube1->Start();


    //cube 2
    Entity* cube2 = Manager::MakeEntity("Cube2");
    Transform::MoveTo(cube2->GetTransform(), XMFLOAT3(0.0f, 3.0f, 0.0f));
    Transform::ScaleTo(cube2->GetTransform(), XMFLOAT3(0.2f, 0.2f, 0.2f));
    cube2->SetTag("Cube");
    //add a model renderer
    CModelRenderer* modelRenderer2 = new CModelRenderer();
    cube2->AddComponent(modelRenderer2);
    modelRenderer2->Load("asset\\model\\WoodenCrate.obj");
    //add a rigid body
    CPhysXRigidBody* rigidBody2 = new CPhysXRigidBody(true);
    cube2->AddComponent(rigidBody2);
    //add a physx box
    CPhysXBox* physXBox2 = new CPhysXBox();
    physXBox2->SetMaterial(1.0f, 1.0f, 0.0f);
    physXBox2->SetSimulate(true);
    physXBox2->SetQuery(false);
    cube2->AddComponent(physXBox2);
    cube2->Start();


    //Joint
    physx::PxRigidActor* actor1 = rigidBody->GetActor();
    physx::PxRigidActor* actor2 = rigidBody2->GetActor();
    physx::PxTransform local1 = physx::PxTransform(0, -3, 0);
    physx::PxTransform local2 = physx::PxTransform(0, 3, 0);
    physx::PxD6Joint* joint = physx::PxD6JointCreate(*PhysX_Impl::GetPhysics(), actor1, local1, actor2, local2);
    joint->setMotion(physx::PxD6Axis::eSWING1, physx::PxD6Motion::eFREE);
    joint->setMotion(physx::PxD6Axis::eSWING2, physx::PxD6Motion::eFREE);
    joint->setMotion(physx::PxD6Axis::eTWIST, physx::PxD6Motion::eFREE);
    joint->setMotion(physx::PxD6Axis::eX, physx::PxD6Motion::eFREE);
    joint->setMotion(physx::PxD6Axis::eY, physx::PxD6Motion::eFREE);
    joint->setMotion(physx::PxD6Axis::eZ, physx::PxD6Motion::eFREE);
    joint->setDrive(physx::PxD6Drive::eX, physx::PxD6JointDrive(1000, 1000, 1000, true));
    joint->setDrive(physx::PxD6Drive::eY, physx::PxD6JointDrive(1000, 1000, 1000, true));
    joint->setDrive(physx::PxD6Drive::eZ, physx::PxD6JointDrive(1000, 1000, 1000, true));
    joint->setDrive(physx::PxD6Drive::eSWING, physx::PxD6JointDrive(1000, 1000, 1000, true));
    joint->setDrive(physx::PxD6Drive::eTWIST, physx::PxD6JointDrive(1000, 1000, 1000, true));
    joint->setDrivePosition(physx::PxTransform(0, 0, 0));
    joint->setConstraintFlag(physx::PxConstraintFlag::eVISUALIZATION, true);

    //camera
    Entity* Camera = Manager::MakeEntity("Camera");
    CCamera* camera = new CCamera();
    Camera->AddComponent(camera);
    camera->Activate();
    camera->SetLookAtParent(true);
    camera->SetSmoothing(true);
    camera->SetOffset(XMFLOAT3(-8.0f, 10.0f, -1.0f));
    Camera->Start();

    //pxplane
    PhysX_Impl::GetScene()->addActor(*physx::PxCreatePlane(
        *PhysX_Impl::GetPhysics(), physx::PxPlane(0, 1, 0, 1.0f),
        *PhysX_Impl::GetPhysics()->createMaterial(0.5f, 0.5f, 1.0f))
    );
}
