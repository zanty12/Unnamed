#pragma once
#include "gameobject.h"

class Scene
{
private:
    int entityCount_ = 0;
    std::vector<GameObject*> gameObjects_;

public:
    Scene();
    ~Scene();

    int AddGameObject()
    {
        gameObjects_.push_back(new GameObject(entityCount_));
        entityCount_++;
        return entityCount_;
    }

    void Update()
    {
        for (auto gameObject : gameObjects_)
        {
            gameObject->Update();
        }
    }
};
