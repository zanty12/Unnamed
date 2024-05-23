#pragma once

class Scene
{
private:
public:
    Scene() = default;
    virtual ~Scene() = default;
    virtual void Setup() = 0;

};
