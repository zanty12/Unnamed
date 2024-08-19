#pragma once
#include <vector>

#include "traits/physics3D.h"

class PhysicsSystem3D
{
private:
    static std::vector<Physics3D*> physics3D_;
public:
    static void AddCollider3D(Physics3D* physics3D);
    static void RemoveCollider3D(Physics3D* physics3D);
    static std::vector<Physics3D*> GetPhysics3D();
    static void UpdateCollisions();
    static void ApplyCollisions();
    static void CleanUp();
};
