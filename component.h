#pragma once

class Component
{
public:
    Component() = default;
    virtual ~Component() = default;
    virtual void Start() = 0;
    virtual void Update() = 0;
    virtual void CleanUp() = 0;
};
