#pragma once

#include "PhysX/PxPhysicsAPI.h"
#pragma comment(lib, "PhysX_64.lib")
#pragma comment(lib, "PhysXCommon_64.lib")
#pragma comment(lib, "PhysXCooking_64.lib")
#pragma comment(lib, "PhysXExtensions_static_64.lib")
#pragma comment(lib, "PhysXFoundation_64.lib")
#pragma comment(lib, "PhysXPvdSDK_static_64.lib")
#pragma comment(lib, "PhysXTask_static_64.lib")
#pragma comment(lib, "SceneQuery_static_64.lib")
#pragma comment(lib, "SimulationController_static_64.lib")


class PhysX_Impl
{
private:
    // PhysX内で利用するアロケーター
    static physx::PxDefaultAllocator m_defaultAllocator;
    // エラー時用のコールバックでエラー内容が入ってる
    static physx::PxDefaultErrorCallback m_defaultErrorCallback;
    // 上位レベルのSDK(PxPhysicsなど)をインスタンス化する際に必要
    static physx::PxFoundation* m_pFoundation;
    // 実際に物理演算を行う
    static physx::PxPhysics* m_pPhysics;
    // シミュレーションをどう処理するかの設定でマルチスレッドの設定もできる
    static physx::PxDefaultCpuDispatcher* m_pDispatcher;
    // シミュレーションする空間の単位でActorの追加などもここで行う
    static physx::PxScene* m_pScene;
    // PVDと通信する際に必要
    static physx::PxPvd* m_pPvd;
    //CUDA
    static physx::PxCudaContextManager* m_pCudaCtxMgr;
public:
    static bool Start();
    static void Update();
    static void CleanUp();
    static physx::PxPhysics* GetPhysics() { return m_pPhysics; }
    static physx::PxScene* GetScene() { return m_pScene; }
};
