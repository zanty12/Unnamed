#pragma once
#include <map>
#include <string>

const std::map<std::string, int> process_priority = {
    //components that moves the entity
    {"Controller", 8},
    {"RigidBody",7},
    //collision update
    {"Collider2D",6},
    {"Collider3D",6},
    //collision
    {"CollisionCheck",5},
    {"CollisionApply",4},
    //components that changes the entity after physics
    {"TransformConstraint", 3},
    {"BulletBehaviour",3},
    {"EnemyBehaviour",3},
    //textures goes first
    {"Texture", 3},
    //components that draws the entity
    {"ModelRenderer", 2},
    {"Primitive2D",2},
    {"Primitive3D",2},
    {"Camera", 1},
    {"TitleControl",0},
};
