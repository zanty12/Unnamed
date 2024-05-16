#pragma once
#include <string>

class Entity;
class Component
{
protected:
    int parent_id_ = -1;
    std::string type_;
public:
    Component(std::string type) : type_(std::move(type)){}
    virtual ~Component() = default;
    virtual void Start() = 0;
    virtual void Update(Entity* parent) = 0;
    virtual void CleanUp() = 0;
    int GetParentID() const { return parent_id_; }
    std::string GetType() const { return type_; }
    void AttachTo(int parent_id) { parent_id_ = parent_id; }
};
