#pragma once
#include <string>
#include "processpriority.h"
#include "transform.h"
#define PRIORITIES_H_

class Entity;
class Component
{
protected:
    int parent_id_ = -1;
    std::string type_;
    int priority_;
    Transform* local_transform_ = nullptr;
public:
    Component() = delete;
    Component(std::string type,Process_Level level) : type_(std::move(type)),priority_(level)
    {
        local_transform_ = Transform::Identity();
    }
    virtual ~Component()
    {
        delete local_transform_;
    };
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void CleanUp() = 0;
    int GetParentID() const { return parent_id_; }
    std::string GetType() const { return type_; }
    void AttachTo(int parent_id) { parent_id_ = parent_id; }
    void SetPriority(int priority) { priority_ = priority; }
    int GetPriority() const { return priority_; }
    Transform* GetLocalTransform() const { return local_transform_; }
    void SetLocalTransform(Transform transform) { Transform::Copy(local_transform_, &transform); }
    Transform GetWorldTransform() const;
};
