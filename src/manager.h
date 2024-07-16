#pragma once
#include "traits/drawable.h"
#include "entity.h"
#include "system/renderPL.h"
#include "system/threadpool.h"
#include "components/CCamera.h"
#include "gamemode/GameMode.h"
#include "scene/scene.h"

class Spawnable;
class Manager
{
private:
	static int entity_count_; //keeps track of created entities of the current scene,even after deleting
	static std::vector<Entity*> entities_;
	static std::vector<int> removal_queue_;
	static std::vector<Spawnable*> spawn_queue_;
	static CCamera* active_camera_;
	static ThreadPool thread_pool_;
	static Scene* scene_;
	static GameMode* game_mode_;

public:
	static void Init();
	static void Uninit();
	static void Update();
	static void Draw();
	static Entity* MakeEntity(std::string name = "Entity");
	static bool RemoveEntity(int id);
	static Entity* FindEntityByID(int id);
	static Entity* FindEntityByName(std::string name);
	static std::vector<Entity*> FindEntitiesWithTag(std::string tag);
	static void QueueForRemoval(int id);
	static void QueueForSpawn(Spawnable* spawnable);
	static CCamera* GetActiveCamera();
	static void SetActiveCamera(CCamera* camera);
	static ThreadPool& GetThreadPool();
	static void LoadScene(Scene* scene);
	static void UnloadCurrentScene();
	static void SetGameMode(GameMode* game_mode);
	static GameMode* GetGameMode();
};
