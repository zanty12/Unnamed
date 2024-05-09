#pragma once
#include <vector>

#include "Component.h"
#include "transform.h"

class GameObject
{
private:
    int id_;
    std::string name_;
    std::string tag_;
    Transform transform_;
    std::vector<Component*> components_;
public:
    GameObject(int id) : id_(id) , transform_(Transform::Identity()){};
    ~GameObject();
    void Update()
    {
        for(auto component : components_)
        {
            component->Update();
        }
    }

};
