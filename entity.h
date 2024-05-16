#pragma once
#include <vector>

#include "Component.h"
#include "transform.h"

class Entity
{
private:
    int id_;
    std::string name_;
    std::string tag_;
    Transform transform_;
    std::vector<Component*> components_;
public:
    Entity(int id) : id_(id) , transform_(Transform::Identity()){};
    ~Entity();
    void Update()
    {
        for(auto component : components_)
        {
            component->Update(this);
        }
    }

    Transform* GetTransform()
    {
        return &transform_;
    }
    int GetId()
    {
        return id_;
    }
    std::string GetName()
    {
        return name_;
    }
    void SetName(std::string name)
    {
        name_ = name;
    }
    std::string GetTag()
    {
        return tag_;
    }
    void SetTag(std::string tag)
    {
        tag_ = tag;
    }
};
