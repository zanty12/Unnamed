#include "JointCrush.h"
#include "physXtest.h"
#include "manager.h"
#include "system/PhysX_Impl.h"
#include "components/PhysX/CPhysXBox.h"
#include "components/PhysX/CPhysXSphere.h"
#include "components/PhysX/CPhysXRigidBody.h"
#include "components/CModelRenderer.h"
#include "components/Shapes/CPlane.h"
#include "components/CVideoTexture.h"
#include "prefab/cube.h"
#include "prefab/pinball.h"
#include "prefab/player.h"
#include "gamemode/GMCrush.h"

#include "components/CText2D.h"
#include "components/CTexture2D.h"

void CreateCubeGrid(physx::PxPhysics* physics, physx::PxScene* scene,
                    int gridSizeX, int gridSizeY, int gridSizeZ, float spacing);

void CreateCubeGridBreak(physx::PxPhysics* physics, physx::PxScene* scene, const physx::PxVec3& posOffset,
                         int gridSizeX, int gridSizeY, int gridSizeZ, float spacing, int breakForce, int breakTorque);

void JointCrush::Setup()
{
    int count = 100;

    CreateCubeGrid(PhysX_Impl::GetPhysics(), PhysX_Impl::GetScene(), 10, 10, 2, 1.1f);

    CreateCubeGridBreak(PhysX_Impl::GetPhysics(), PhysX_Impl::GetScene(), physx::PxVec3(-10, 0, 0), 10, 10, 2, 1.1f, 50,
                        50);

    if (GMCrush* gameMode = dynamic_cast<GMCrush*>(Manager::GetGameMode()))
    {
        gameMode->SetBlocks(count);
    }

    //Create a plane
    Entity* plane = Manager::MakeEntity("plane");
    Transform::MoveTo(plane->GetTransform(), XMFLOAT3(0, -0.5f, 0));
    Transform::ScaleTo(plane->GetTransform(), XMFLOAT3(7.5f, 1.0f, 7.5f));
    CPlane* planecomponent = new CPlane();
    CTexture2D* texture_2d = new CTexture2D(L"asset/texture/calibrate.png");
    planecomponent->SetTexture(texture_2d);
    plane->AddComponent(planecomponent);
    plane->AddComponent(planecomponent);
    //add rigidbody
    CPhysXRigidBody* plane_rigid_body = new CPhysXRigidBody(false);
    plane->AddComponent(plane_rigid_body);
    CPhysXBox* plane_physXBox = new CPhysXBox();
    plane_physXBox->SetDebugView(false);
    plane->AddComponent(plane_physXBox);
    Transform::ScaleTo(plane_physXBox->GetLocalTransform(), XMFLOAT3(4.0f, 1.0f, 4.0f));
    plane->Start();
    planecomponent->SetEndUV(XMFLOAT2(1.0f, 1.0f));

    //skybox
    Entity* skybox = Manager::MakeEntity("skybox");
    skybox->GetTransform().scale = XMFLOAT3(100, 100, 100);
    CModelRenderer* skybox_renderer = new CModelRenderer();
    skybox_renderer->Load("asset\\model\\sky.obj");
    skybox->AddComponent(skybox_renderer);
    skybox->Start();

    Pinball* player = new Pinball();
    player->Start();
    //delete setup object after creating entity
    delete player;

    //Create Surrounding Walls
    Entity* wall1 = Manager::MakeEntity("wall");
    Transform::MoveTo(wall1->GetTransform(), XMFLOAT3(-15.0f, 5.0f, 0));
    Transform::ScaleTo(wall1->GetTransform(), XMFLOAT3(0.1f, 15.0f, 30.0f));
    CPhysXRigidBody* wall_rigid_body = new CPhysXRigidBody(false);
    wall1->AddComponent(wall_rigid_body);
    CPhysXBox* wall_physXBox = new CPhysXBox();
    wall_physXBox->SetDebugView(true);
    wall1->AddComponent(wall_physXBox);
    wall1->Start();

    Entity* wall2 = Manager::MakeEntity("wall");
    Transform::MoveTo(wall2->GetTransform(), XMFLOAT3(15.0f, 5.0f, 0));
    Transform::ScaleTo(wall2->GetTransform(), XMFLOAT3(0.1f, 15.0f, 30.0f));
    CPhysXRigidBody* wall_rigid_body2 = new CPhysXRigidBody(false);
    wall2->AddComponent(wall_rigid_body2);
    CPhysXBox* wall_physXBox2 = new CPhysXBox();
    wall_physXBox2->SetDebugView(true);
    wall2->AddComponent(wall_physXBox2);
    wall2->Start();

    Entity* wall3 = Manager::MakeEntity("wall");
    Transform::MoveTo(wall3->GetTransform(), XMFLOAT3(0, 5.0f, -15.0f));
    Transform::ScaleTo(wall3->GetTransform(), XMFLOAT3(30.0f, 15.0f, 0.1f));
    CPhysXRigidBody* wall_rigid_body3 = new CPhysXRigidBody(false);
    wall3->AddComponent(wall_rigid_body3);
    CPhysXBox* wall_physXBox3 = new CPhysXBox();
    wall_physXBox3->SetDebugView(true);
    wall3->AddComponent(wall_physXBox3);
    wall3->Start();

    Entity* wall4 = Manager::MakeEntity("wall");
    Transform::MoveTo(wall4->GetTransform(), XMFLOAT3(0, 5.0f, 15.0f));
    Transform::ScaleTo(wall4->GetTransform(), XMFLOAT3(30.0f, 15.0f, 0.1f));
    CPhysXRigidBody* wall_rigid_body4 = new CPhysXRigidBody(false);
    wall4->AddComponent(wall_rigid_body4);
    CPhysXBox* wall_physXBox4 = new CPhysXBox();
    wall_physXBox4->SetDebugView(true);
    wall4->AddComponent(wall_physXBox4);
    wall4->Start();

    //add a top wall
    Entity* wall5 = Manager::MakeEntity("wall");
    Transform::MoveTo(wall5->GetTransform(), XMFLOAT3(0, 15.0f, 0));
    Transform::ScaleTo(wall5->GetTransform(), XMFLOAT3(30.0f, 0.1f, 30.0f));
    CPhysXRigidBody* wall_rigid_body5 = new CPhysXRigidBody(false);
    wall5->AddComponent(wall_rigid_body5);
    CPhysXBox* wall_physXBox5 = new CPhysXBox();
    wall_physXBox5->SetDebugView(true);
    wall5->AddComponent(wall_physXBox5);
    wall5->Start();

    Entity* text = Manager::MakeEntity("score");
    Transform::MoveTo(text->GetTransform(), XMFLOAT3(0, 0, 0.0f));
    Transform::ScaleTo(text->GetTransform(), XMFLOAT3(200.0f, 100.0f, 0.0f));
    CText2D* textComponent = new CText2D();
    textComponent->SetFontColor(XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f));
    textComponent->SetFontWeight(DWRITE_FONT_WEIGHT_BOLD);
    textComponent->SetFontSize(50);
    textComponent->SetText(L"Score: 0");
    textComponent->SetAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    text->AddComponent(textComponent);
    text->Start();
}

void CreateCubeGrid(physx::PxPhysics* physics, physx::PxScene* scene,
                    int gridSizeX, int gridSizeY, int gridSizeZ, float spacing)
{
    std::vector<std::vector<std::vector<Entity*>>> grid(gridSizeX,
                                                        std::vector<std::vector<Entity*>>(
                                                            gridSizeY, std::vector<Entity*>(gridSizeZ, nullptr)));

    // Create cubes and place them in the grid
    for (int x = 0; x < gridSizeX; ++x)
    {
        for (int y = 0; y < gridSizeY; ++y)
        {
            for (int z = 0; z < gridSizeZ; ++z)
            {
                // Calculate the position for the current cube
                physx::PxVec3 position(x * spacing, y * spacing, z * spacing);

                // Create a Cube instance
                Cube* cube = new Cube();
                cube->SetTransform(Transform{
                    XMFLOAT3(position.x, position.y, position.z),
                    XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)
                });
                cube->Start(); // Start will initialize everything
                grid[x][y][z] = cube->GetEntity(); // Save only the entity
                delete cube; // Cube object should be deleted after Start()
            }
        }
    }

    // Create PxFixedJoints between adjacent cubes
    for (int x = 0; x < gridSizeX; ++x)
    {
        for (int y = 0; y < gridSizeY; ++y)
        {
            for (int z = 0; z < gridSizeZ; ++z)
            {
                Entity* currentEntity = grid[x][y][z];
                physx::PxRigidDynamic* currentBody = currentEntity->GetComponent<CPhysXRigidBody>()->GetActor()->is<
                    physx::PxRigidDynamic>();

                // Connect to the cube on the +X axis
                if (x + 1 < gridSizeX)
                {
                    Entity* neighborEntity = grid[x + 1][y][z];
                    physx::PxRigidDynamic* neighborBody = neighborEntity->GetComponent<CPhysXRigidBody>()->GetActor()->
                                                                          is<physx::PxRigidDynamic>();
                    physx::PxFixedJoint* joint = physx::PxFixedJointCreate(*physics, currentBody,
                                                                           physx::PxTransform(
                                                                               physx::PxVec3(spacing / 2, 0, 0)),
                                                                           neighborBody,
                                                                           physx::PxTransform(
                                                                               physx::PxVec3(-spacing / 2, 0, 0)));
                }

                // Connect to the cube on the +Y axis
                if (y + 1 < gridSizeY)
                {
                    Entity* neighborEntity = grid[x][y + 1][z];
                    physx::PxRigidDynamic* neighborBody = neighborEntity->GetComponent<CPhysXRigidBody>()->GetActor()->
                                                                          is<physx::PxRigidDynamic>();
                    physx::PxFixedJoint* joint = physx::PxFixedJointCreate(*physics, currentBody,
                                                                           physx::PxTransform(
                                                                               physx::PxVec3(0, spacing / 2, 0)),
                                                                           neighborBody,
                                                                           physx::PxTransform(
                                                                               physx::PxVec3(0, -spacing / 2, 0)));
                }

                // Connect to the cube on the +Z axis
                if (z + 1 < gridSizeZ)
                {
                    Entity* neighborEntity = grid[x][y][z + 1];
                    physx::PxRigidDynamic* neighborBody = neighborEntity->GetComponent<CPhysXRigidBody>()->GetActor()->
                                                                          is<physx::PxRigidDynamic>();
                    physx::PxFixedJoint* joint = physx::PxFixedJointCreate(*physics, currentBody,
                                                                           physx::PxTransform(
                                                                               physx::PxVec3(0, 0, spacing / 2)),
                                                                           neighborBody,
                                                                           physx::PxTransform(
                                                                               physx::PxVec3(0, 0, -spacing / 2)));
                }
            }
        }
    }
}

void CreateCubeGridBreak(physx::PxPhysics* physics, physx::PxScene* scene, const physx::PxVec3& posOffset,
                         int gridSizeX, int gridSizeY, int gridSizeZ, float spacing, int breakForce, int breakTorque)
{
    std::vector<std::vector<std::vector<Entity*>>> grid(gridSizeX,
                                                        std::vector<std::vector<Entity*>>(
                                                            gridSizeY, std::vector<Entity*>(gridSizeZ, nullptr)));

    // Create cubes and place them in the grid
    for (int x = 0; x < gridSizeX; ++x)
    {
        for (int y = 0; y < gridSizeY; ++y)
        {
            for (int z = 0; z < gridSizeZ; ++z)
            {
                // Calculate the position for the current cube
                physx::PxVec3 position(x * spacing + posOffset.x, y * spacing + posOffset.y, z * spacing + posOffset.z);

                // Create a Cube instance
                Cube* cube = new Cube();
                cube->SetTransform(Transform{
                    XMFLOAT3(position.x, position.y, position.z),
                    XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT4(0.0f, 0.0f, 0.0f, 1.0f)
                });
                cube->Start(); // Start will initialize everything
                grid[x][y][z] = cube->GetEntity(); // Save only the entity
                delete cube; // Cube object should be deleted after Start()
            }
        }
    }

    // Create PxFixedJoints between adjacent cubes
    for (int x = 0; x < gridSizeX; ++x)
    {
        for (int y = 0; y < gridSizeY; ++y)
        {
            for (int z = 0; z < gridSizeZ; ++z)
            {
                Entity* currentEntity = grid[x][y][z];
                physx::PxRigidDynamic* currentBody = currentEntity->GetComponent<CPhysXRigidBody>()->GetActor()->is<
                    physx::PxRigidDynamic>();

                // Connect to the cube on the +X axis
                if (x + 1 < gridSizeX)
                {
                    Entity* neighborEntity = grid[x + 1][y][z];
                    physx::PxRigidDynamic* neighborBody = neighborEntity->GetComponent<CPhysXRigidBody>()->GetActor()->
                                                                          is<physx::PxRigidDynamic>();
                    physx::PxFixedJoint* joint = physx::PxFixedJointCreate(*physics, currentBody,
                                                                           physx::PxTransform(
                                                                               physx::PxVec3(spacing / 2, 0, 0)),
                                                                           neighborBody,
                                                                           physx::PxTransform(
                                                                               physx::PxVec3(-spacing / 2, 0, 0)));
                    //set break force
                    joint->setBreakForce(breakForce, breakTorque);
                }

                // Connect to the cube on the +Y axis
                if (y + 1 < gridSizeY)
                {
                    Entity* neighborEntity = grid[x][y + 1][z];
                    physx::PxRigidDynamic* neighborBody = neighborEntity->GetComponent<CPhysXRigidBody>()->GetActor()->
                                                                          is<physx::PxRigidDynamic>();
                    physx::PxFixedJoint* joint = physx::PxFixedJointCreate(*physics, currentBody,
                                                                           physx::PxTransform(
                                                                               physx::PxVec3(0, spacing / 2, 0)),
                                                                           neighborBody,
                                                                           physx::PxTransform(
                                                                               physx::PxVec3(0, -spacing / 2, 0)));
                    joint->setBreakForce(breakForce, breakTorque);
                }

                // Connect to the cube on the +Z axis
                if (z + 1 < gridSizeZ)
                {
                    Entity* neighborEntity = grid[x][y][z + 1];
                    physx::PxRigidDynamic* neighborBody = neighborEntity->GetComponent<CPhysXRigidBody>()->GetActor()->
                                                                          is<physx::PxRigidDynamic>();
                    physx::PxFixedJoint* joint = physx::PxFixedJointCreate(*physics, currentBody,
                                                                           physx::PxTransform(
                                                                               physx::PxVec3(0, 0, spacing / 2)),
                                                                           neighborBody,
                                                                           physx::PxTransform(
                                                                               physx::PxVec3(0, 0, -spacing / 2)));
                    joint->setBreakForce(breakForce, breakTorque);
                }
            }
        }
    }
}
