#include "main.h"
#include "manager.h"

#include "camera.h"
#include "renderer.h"
#include "imgui_impl_hal.h"
#include "testscene.h"

TestScene* testScene;
int Manager::entity_count_ = 0;
std::vector<Entity*> Manager::entities_ = std::vector<Entity*>();
std::vector<Drawable*> Manager::drawables_ = std::vector<Drawable*>();

void Manager::Init()
{
	Renderer::Init();
	testScene = new TestScene();
	testScene->Setup();
}


void Manager::Uninit()
{
	Renderer::Uninit();
	delete testScene;
	for (auto& entity : entities_)
	{
		if (entity != nullptr)
		{
			delete entity;
		}
	}
	entities_.clear();
}

void Manager::Update()
{
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
	for(auto& drawable : drawables_)
	{
		if(drawable != nullptr)
		{
			drawable->Draw();
		}
	}
	ImGui_Hal::BeginDraw();
	ImGui::Begin("test");
	ImGui::Text("Hello, world!");
	ImGui::End();
	ImGui_Hal::EndDraw();
	Renderer::End();
}

Entity* Manager::MakeEntity(std::string name)
{
	Entity* entity = new Entity(entity_count_);
	entity->SetName(name);
	entities_.push_back(entity);
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

void Manager::AddDrawable(Drawable* drawable)
{
	drawables_.push_back(drawable);
}
;
