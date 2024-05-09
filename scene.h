#pragma once
#include "gameobject.h"

class Scene
{
private:
    int entityCount_;
    std::vector<GameObject*> gameObjects_;

public:
    Scene();
    ~Scene();

    int AddGameObject(GameObject* gameObject)
    {
        gameObjects_.push_back(gameObject);
        entityCount_++;
        return entityCount_ - 1;
    }

    void Update()
    {
        for (auto gameObject : gameObjects_)
        {
            gameObject->Update();
        }
    }
};
