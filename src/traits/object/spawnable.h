#pragma once
#include "../trait.h"
#include "manager.h"

class Spawnable : public Trait
{
public:
     Spawnable() : Trait("Spawnable"){}
     virtual ~Spawnable() = default;
     virtual void Spawn() = 0;
     void QueueSpawn()
     {
          Manager::QueueForSpawn(this);
     }
};
