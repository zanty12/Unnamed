/**
* @file entity.h
 * @brief This file contains the Entity class.
 */

#pragma once
#include <vector>

#include "components/Component.h"
#include "transform.h"
#include "traits/unique.h"

/**
 * @class Entity
 * @brief A class that represents an entity in the game.
 *
 * This class contains various properties and methods that are common to all entities in the game.
 * It has a unique id, a name, a tag, a transform, and a list of components.
 */
class Entity
{
private:
    /**
     * @brief The unique id of the Entity.
     */
    int id_;

    /**
     * @brief The name of the Entity.
     */
    std::string name_;

    /**
     * @brief The tag of the Entity.
     */
    std::string tag_;

    /**
     * @brief The transform of the Entity.
     */
    Transform transform_;

    /**
     * @brief The list of components attached to the Entity.
     */
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
            component->Update();
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

    void SetId(int id)
    {
        id_ = id;
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

    /**
     * @brief Add a component to the Entity.
     *
     * This method adds a component to the Entity's list of components.
     * If the component implements the Unique trait, it checks if a component of the same type is already attached to the Entity.
     * If a component of the same type is already attached, it does not add the new component.
     *
     * @param component A pointer to the component to add.
     */
    void AddComponent(Component* component)
    {
        //check if component implements unique
        Unique* unique = dynamic_cast<Unique*>(component);
        if(unique)
        {
            for(auto comp : components_)
            {
                Unique* other = dynamic_cast<Unique*>(comp);
                if(other)
                {
                    if(comp->GetType() == component->GetType())
                    {
                        return;
                    }
                }
            }
        }
        component->AttachTo(id_);
        components_.push_back(component);
    }

    std::vector<Component*> GetComponents()
    {
        return components_;
    }

    template<class T>
    T* GetComponent()
    {
        for(auto component : components_)
        {
            T* t = dynamic_cast<T*>(component);
            if(t)
            {
                return t;
            }
        }
        return nullptr;
    }

};
