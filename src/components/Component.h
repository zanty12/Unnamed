#pragma once
#include <string>
#define PRIORITIES_H_
#include "processpriority.h"


class Entity;
class Component
{
protected:
    int parent_id_ = -1;
    std::string type_;
    int priority_;
public:
    Component() = delete;
    Component(std::string type) : type_(std::move(type)),priority_(process_priority.at(type_)){}
    virtual ~Component() = default;
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void CleanUp() = 0;
    int GetParentID() const { return parent_id_; }
    std::string GetType() const { return type_; }
    void AttachTo(int parent_id) { parent_id_ = parent_id; }
    void SetPriority(int priority) { priority_ = priority; }
    int GetPriority() const { return priority_; }
};
