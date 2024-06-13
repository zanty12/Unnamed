#pragma once
#include "traits/drawable.h"
#include "entity.h"
#include "renderPL.h"
#include "components/CCamera.h"

class Spawnable;
class Manager
{
private:
	static int entity_count_; //keeps track of created entities,even after deleting
	static std::vector<Entity*> entities_;
	static std::vector<int> removal_queue_;
	static std::vector<Spawnable*> spawn_queue_;
	static CCamera* active_camera_;

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static Entity* MakeEntity(std::string name = "Entity");
	static bool RemoveEntity(int id);
	static Entity* FindEntity(int id);
	static Entity* FindEntity(std::string name);
	static std::vector<Entity*> FindEntitiesWithTag(std::string tag);
	static void QueueForRemoval(int id);
	static void QueueForSpawn(Spawnable* spawnable);
	static CCamera* GetActiveCamera();
	static void SetActiveCamera(CCamera* camera);
};
