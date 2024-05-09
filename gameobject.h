#pragma once
#include <vector>

#include "Component.h"
#include "transform.h"

class GameObject
{
private:
    int id_;
    Transform transform_;
    std::vector<Component*> components_;
public:
    GameObject();
    ~GameObject();
    void Update()
    {
        for(auto component : components_)
        {
            component->Update();
        }
    }
};
