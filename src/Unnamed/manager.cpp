#include "main.h"
#include "manager.h"
#include "renderer.h"
#include <iostream>
#include <stdbool.h>

#include "imgui_impl_hal.h"
#include "system/input.h"
#include "system/physicssystem3D.h"
#include "system/PhysX_Impl.h"
#include "system/textureLoader.h"
#include "system/timesystem.h"

#include "components/CAudio.h"
#include "components/CCamera.h"
#include "components/CModelRenderer.h"
#include "components/CText2D.h"
#include "Game/gamemode/GMDefaultGamemode.h"
#include "Game/scene/physXtest.h"
#include "Game/scene/title.h"
#include "traits/debugmenu.h"
#include "traits/object/spawnable.h"

int Manager::entity_count_ = 0;
std::vector<Entity*> Manager::entities_ = std::vector<Entity*>();
std::vector<int> Manager::removal_queue_ = std::vector<int>();
std::vector<Spawnable*> Manager::spawn_queue_ = std::vector<Spawnable*>();
std::vector<DebugMenu*> Manager::debug_menu_;
CCamera* Manager::active_camera_ = nullptr;
ThreadPool Manager::thread_pool_;
Scene* Manager::scene_ = nullptr;
GameMode* Manager::game_mode_ = nullptr;

void Manager::Init()
{
    Renderer::Init();
    Input::Init();
    Time::Start();
    CAudio::StartMaster();
    CText2D::CreatePublicResources();
    if(!PhysX_Impl::Start())
        std::cout << "PhysX failed to start" << std::endl;
    LoadScene(scene_);
}

void Manager::Uninit()
{
    thread_pool_.StopProcessing();
    Renderer::Uninit();
    Input::Uninit();
    Time::CleanUp();
    CText2D::DiscardPublicResources();
    UnloadCurrentScene();
    PhysX_Impl::CleanUp();
    CAudio::CleanUpMaster();
}

void Manager::Update()
{
    Input::Update();

    //Update physics in 60fps
    if(Time::FixedUpdate())
    PhysX_Impl::Update();

    //update all entities
    for (auto& entity : entities_)
    {
        if (entity != nullptr)
        {
            entity->Update();
        }
    }
    //update physics
    PhysicsSystem3D::UpdateCollisions();
    PhysicsSystem3D::ApplyCollisions();

    thread_pool_.StartProcessing();
    //wait for all threads to finish
    while (true)
    {
        if (thread_pool_.GetWorkingThreads() <= 0 && thread_pool_.GetTasksCount() <= 0)
            break;
    }
    thread_pool_.StopProcessing();

    //delete entities in the removal queue
    for (auto& id : removal_queue_)
    {
        if (entities_[id] != nullptr)
        {
            RemoveEntity(id);
        }
    }
    //spawn entities
    for (auto& spawnable : spawn_queue_)
    {
        spawnable->Spawn();
        delete spawnable;
    }
    //clean up spawn queue
    spawn_queue_.clear();

    game_mode_->Update();
}

void Manager::Draw()
{
    Renderer::Begin();
    CText2D::TextStart();
    Renderer::LoadState();
    active_camera_->Draw();
    RenderPL::Draw();
    CText2D::TextEnd();

    ImGui_Hal::BeginDraw();

    ImGui::Begin("FPS");
    ImGui::Text("Hello, world!");
    //ImGui::Text(u8"ƒeƒXƒg");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
    ImGui::Text("Mouse Pos: %d, %d", Input::GetMousePos().x, Input::GetMousePos().y);
    ImGui::Text("delta time: %f", Time::GetDeltaTime());
    ImGui::End();

    for (auto& debug_menu : debug_menu_)
    {
        debug_menu->DrawMenu();
    }

    ImGui_Hal::EndDraw();

    Renderer::End();
    Time::Update();
}

Entity* Manager::MakeEntity(std::string name)
{
    Entity* entity = new Entity(entity_count_);
    entity->SetName(name);
    entities_.push_back(entity);
    entity_count_++;
    return entity;
}

bool Manager::RemoveEntity(int id)
{
    if (entities_[id])
    {
        delete entities_[id];
        entities_[id] = nullptr;
        return true;
    }
    return false;
}

Entity* Manager::FindEntityByID(int id)
{
    return entities_[id];
}

Entity* Manager::FindEntityByName(std::string name)
{
    for (auto entity : entities_)
    {
        if(entity == nullptr)
            continue;
        if (entity->GetName() == name)
        {
            return entity;
        }
    }
    return nullptr;
}

std::vector<Entity*> Manager::FindEntitiesWithTag(std::string tag)
{
    std::vector<Entity*> result;
    for (auto entity : entities_)
    {
        if (entity->GetTag() == tag)
        {
            result.push_back(entity);
        }
    }
    return result;
}

void Manager::QueueForRemoval(int id)
{
    removal_queue_.push_back(id);
}

void Manager::QueueForSpawn(Spawnable* spawnable)
{
    spawn_queue_.push_back(spawnable);
}

CCamera* Manager::GetActiveCamera()
{
    return active_camera_;
}

void Manager::SetActiveCamera(CCamera* camera)
{
    if (active_camera_)
        active_camera_->Deactivate();
    active_camera_ = camera;
}

ThreadPool& Manager::GetThreadPool()
{
    return thread_pool_;
}

void Manager::SetScene(Scene* scene)
{
    if(scene_ != scene)
        scene_ = scene;
}

void Manager::LoadScene(Scene* scene)
{
    SetScene(scene);
    scene_->Setup();
}

void Manager::UnloadCurrentScene()
{
    delete scene_;
    for (auto& entity : entities_)
    {
        if (entity != nullptr)
        {
            delete entity;
        }
    }
    RenderPL::CleanUp();
    TextureLoader::CleanUp();
    PhysicsSystem3D::CleanUp();
    CModelRenderer::UnloadAll();
    entities_.clear();
    removal_queue_.clear();
    //clean up spawn queue
    for (auto& spawnable : spawn_queue_)
    {
        delete spawnable;
    }
    spawn_queue_.clear();
    entity_count_ = 0;
}

void Manager::SetGameMode(GameMode* game_mode)
{
    game_mode_ = game_mode;
}

GameMode* Manager::GetGameMode()
{
    return game_mode_;
}

void Manager::RegisterDebugMenu(DebugMenu* debug_menu){
    debug_menu_.push_back(debug_menu);
   
}
