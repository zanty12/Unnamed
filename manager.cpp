#include "main.h"
#include "manager.h"

#include "camera.h"
#include "renderer.h"
#include "imgui_impl_hal.h"
#include "plane.h"
#include "rect2D.h"

Rect2D* rect2D = nullptr;
Camera* camera = nullptr;
Plane* plane = nullptr;
void Manager::Init()
{
	entity_count_ = 0;
	Renderer::Init();



	rect2D = new Rect2D();
	rect2D->Start();
	camera = new Camera();
	camera->Start();
	plane = new Plane();
	plane->Start();
}


void Manager::Uninit()
{
	Renderer::Uninit();
	rect2D->CleanUp();
	delete rect2D;
	camera->CleanUp();
	delete camera;
	plane->CleanUp();
	delete plane;
}

void Manager::Update()
{

}

void Manager::Draw()
{
	Renderer::Begin();
	ImGui_Hal::BeginDraw();
	ImGui::Begin("test");
	ImGui::Text("Hello, world!");
	ImGui::End();
	ImGui_Hal::EndDraw();
	rect2D->Draw();
	camera->Draw();
	plane->Draw();
	Renderer::End();
}

void Manager::MakeEntity()
{
	entities_.push_back(new Entity(entity_count_));
}

void Manager::RemoveEntity(int id)
{

}

Entity* Manager::FindEntity(int id)
{
}

Entity* Manager::FindEntity(std::string name)
{
}

std::vector<Entity*> Manager::FindEntitiesWithTag(std::string tag)
{
}
;
