#pragma once
#include "traits/drawable.h"
#include "entity.h"
#include "renderPL.h"

class Manager
{
private:
	static int entity_count_; //keeps track of created entities,even after deleting
	static std::vector<Entity*> entities_;

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static Entity* MakeEntity(std::string name = "Entity");
	static void RemoveEntity(int id);
	static Entity* FindEntity(int id);
	static Entity* FindEntity(std::string name);
	static std::vector<Entity*> FindEntitiesWithTag(std::string tag);

};
