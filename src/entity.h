#pragma once
#include <vector>

#include "components/component.h"
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

    void Start()
    {
        for(auto component : components_)
        {
            component->Start();
        }
    }

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
    void SetName(const std::string &name)
    {
        name_ = std::move(name);
    }
    std::string GetTag()
    {
        return tag_;
    }
    void SetTag(std::string tag)
    {
        tag_ = tag;
    }
    void AddComponent(Component* component)
    {
        components_.push_back(component);
    }
    std::vector<Component*> GetComponents()
    {
        return components_;
    }
};
