#pragma once
#ifndef PRIORITIES_H
#define PRIORITIES_H
#include <map>
#include <string>

const std::map<std::string, int> component_priority = {
    //components that moves the entity
    {"Controller", 6},
    {"RigidBody",5},
    {"TransformConstraint", 4},
    {"BulletBehaviour",3},
    //textures goes first
    {"Texture2D", 3},
    {"VideoPlayer", 3},
    {"Sprite2D",3},
    {"Sprite3D", 3},
    //components that draws the entity
    {"ModelRenderer", 2},
    {"Primitive2D",2},
    {"Primitive3D",2},
    {"Camera", 1}
};

#endif // !PRIORITES_H