#pragma once
#include "entity.h"


class Manager
{
private:
	static int entity_count_;
	static std::vector<Entity*> entities_;

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static void MakeEntity();
	static void RemoveEntity(int id);
	static Entity* FindEntity(int id);
	static Entity* FindEntity(std::string name);
	static std::vector<Entity*> FindEntitiesWithTag(std::string tag);
};
