#pragma once
#include <unordered_map>
#include <string>

/*const std::unordered_map<std::string, int> process_priority = {
    //components that moves the entity
    {"Controller", 8},
    {"RigidBody", 7},
    {"PhysXRigidBody",7},
    //collision update
    {"Collider2D", 6},
    {"Collider3D", 6},
    {"PhysXPrimitive",6},
    //collision
    {"CollisionCheck", 5},
    {"CollisionApply", 4},
    //components that changes the entity after physics
    {"TransformConstraint", 3},
    {"BulletBehaviour", 3},
    {"EnemyBehaviour", 3},
    {"GridCell", 3},
    //textures goes first
    {"Texture", 3},
    {"ParticleEmitter", 2},
    //components that draws the entity
    {"ModelRenderer", 2},
    {"AnimationModel",2},
    {"Primitive2D", 2},
    {"Primitive3D", 2},
    {"Text2D", 2},
    {"MouseCursor",2},
    {"Camera", 1},
    //components that changes the scene
    {"TitleControl", 0},
    //dont care
    {"Audio", 0},
    {"Grid",0},
};*/

enum Process_Level
{
    Controller = 8,
    Kinematic = 7,
    PhysicsBehaviour = 6,
    PostPhysicsBehaviour = 5,
    RenderResources = 4,
    DrawCallers = 3,
    Camera = 2,
    DontCare = 1,
    SceneControl = 0,
};


