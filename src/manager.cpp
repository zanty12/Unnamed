#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "time.h"

#include "components/camera.h"
#include "imgui_impl_hal.h"
#include "scene/testscene.h"

TestScene* testScene;
int Manager::entity_count_ = 0;
std::vector<Entity*> Manager::entities_ = std::vector<Entity*>();

void Manager::Init()
{
	Renderer::Init();
	Input::Init();
	Time::Start();

	testScene = new TestScene();
	testScene->Setup();
}


void Manager::Uninit()
{
	Renderer::Uninit();
	Input::Uninit();
	Time::CleanUp();
	delete testScene;
	for (auto& entity : entities_)
	{
		if (entity != nullptr)
		{
			delete entity;
		}
	}
	RenderPL::CleanUp();
	entities_.clear();
}

void Manager::Update()
{
	Input::Update();
	Time::Update();

	//update all entities
	for (auto& entity : entities_)
	{
		if (entity != nullptr)
		{
			entity->Update();
		}
	}
}

void Manager::Draw()
{
	Renderer::Begin();
	RenderPL::Draw();

	ImGui_Hal::BeginDraw();
	ImGui::Begin("FPS");
	ImGui::Text("Hello, world!");
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
	ImGui_Hal::EndDraw();

	Renderer::End();
}

Entity* Manager::MakeEntity(std::string name)
{
	Entity* entity = new Entity(entity_count_);
	entity->SetName(name);
	entities_.push_back(entity);
	entity_count_++;
	return entity;
}

void Manager::RemoveEntity(int id)
{
	delete entities_[id];
	entities_[id] = nullptr;
}

Entity* Manager::FindEntity(int id)
{
	return entities_[id];
}

Entity* Manager::FindEntity(std::string name)
{
	for(auto entity : entities_)
	{
		if(entity->GetName() == name)
		{
			return entity;
		}
	}
	return nullptr;
}

std::vector<Entity*> Manager::FindEntitiesWithTag(std::string tag)
{
	std::vector<Entity*> result;
	for(auto entity : entities_)
	{
		if(entity->GetTag() == tag)
		{
			result.push_back(entity);
		}
	}
	return result;
}

;
