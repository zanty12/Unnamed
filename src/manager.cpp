#include "main.h"
#include "manager.h"

#include <iostream>
#include <stdbool.h>

#include "renderer.h"
#include "input.h"
#include "timesystem.h"

#include "components/CCamera.h"
#include "imgui_impl_hal.h"
#include "physicssystem3D.h"
#include "textureLoader.h"
#include "scene/testscene.h"
#include "scene/title.h"
#include "traits/object/spawnable.h"

int Manager::entity_count_ = 0;
std::vector<Entity*> Manager::entities_ = std::vector<Entity*>();
std::vector<int> Manager::removal_queue_ = std::vector<int>();
std::vector<Spawnable*> Manager::spawn_queue_ = std::vector<Spawnable*>();
CCamera* Manager::active_camera_ = nullptr;
ThreadPool Manager::thread_pool_;
Scene* Manager::scene_ = nullptr;

void Manager::Init()
{
    Renderer::Init();
    Input::Init();
    Time::Start();

    LoadScene(new Title());
}

void Manager::Uninit()
{
    Renderer::Uninit();
    Input::Uninit();
    Time::CleanUp();
    UnloadCurrentScene();
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
    }
    //clean up spawn queue
    spawn_queue_.clear();
}

void Manager::Draw()
{
    Renderer::Begin();
    RenderPL::Draw();

    ImGui_Hal::BeginDraw();
    ImGui::Begin("FPS");
    ImGui::Text("Hello, world!");
    ImGui::Text(u8"ƒeƒXƒg");
    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate,
                ImGui::GetIO().Framerate);
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

Entity* Manager::FindEntity(int id)
{
    return entities_[id];
}

Entity* Manager::FindEntity(std::string name)
{
    for (auto entity : entities_)
    {
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

void Manager::LoadScene(Scene* scene)
{
    scene_ = scene;
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
    entities_.clear();
    removal_queue_.clear();
    spawn_queue_.clear();
    entity_count_ = 0;
}

;
