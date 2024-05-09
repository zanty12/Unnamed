#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "imgui_impl_hal.h"
#include "rect2D.h"

Rect2D* rect2D = nullptr;
void Manager::Init()
{
	Renderer::Init();
	rect2D = new Rect2D();
	rect2D->Start();
}


void Manager::Uninit()
{
	Renderer::Uninit();
	rect2D->CleanUp();
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
	Renderer::End();
}
;