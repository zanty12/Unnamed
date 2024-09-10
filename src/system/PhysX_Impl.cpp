#include "main.h"
#include "renderer.h"
#include <iostream>
#include "timesystem.h"
#include "PhysX_Impl.h"

// PhysX内で利用するアロケーター
physx::PxDefaultAllocator PhysX_Impl::m_defaultAllocator;
// エラー時用のコールバックでエラー内容が入ってる
physx::PxDefaultErrorCallback PhysX_Impl::m_defaultErrorCallback;
// 上位レベルのSDK(PxPhysicsなど)をインスタンス化する際に必要
physx::PxFoundation* PhysX_Impl::m_pFoundation = nullptr;
// 実際に物理演算を行う
physx::PxPhysics* PhysX_Impl::m_pPhysics = nullptr;
// シミュレーションをどう処理するかの設定でマルチスレッドの設定もできる
physx::PxDefaultCpuDispatcher* PhysX_Impl::m_pDispatcher = nullptr;
// シミュレーションする空間の単位でActorの追加などもここで行う
physx::PxScene* PhysX_Impl::m_pScene = nullptr;
// PVDと通信する際に必要
physx::PxPvd* PhysX_Impl::m_pPvd = nullptr;
//CUDA
physx::PxCudaContextManager* PhysX_Impl::m_pCudaCtxMgr = nullptr;

bool PhysX_Impl::Start()
{
    // Foundationのインスタンス化
    m_pFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, m_defaultAllocator, m_defaultErrorCallback);
    if (!m_pFoundation)
    {
        std::cerr << "Failed to create PxFoundation" << std::endl;
        return false;
    }

    // PVDと接続する設定
    m_pPvd = physx::PxCreatePvd(*m_pFoundation);
    if (m_pPvd)
    {
        physx::PxPvdTransport* transport = physx::PxDefaultPvdSocketTransportCreate("127.0.0.1", 5425, 10);
        m_pPvd->connect(*transport, physx::PxPvdInstrumentationFlag::eALL);
    }

    // Physicsのインスタンス化
    m_pPhysics = PxCreatePhysics(PX_PHYSICS_VERSION, *m_pFoundation, physx::PxTolerancesScale(), true, m_pPvd);
    if (!m_pPhysics)
    {
        std::cerr << "Failed to create PxPhysics" << std::endl;
        return false;
    }

    // 拡張機能用
    if (!PxInitExtensions(*m_pPhysics, m_pPvd))
    {
        std::cerr << "Failed to initialize PhysX extensions" << std::endl;
        return false;
    }

    // 処理に使うスレッドを指定する
    m_pDispatcher = physx::PxDefaultCpuDispatcherCreate(8);
    if (!m_pDispatcher)
    {
        std::cerr << "Failed to create CPU dispatcher" << std::endl;
        return false;
    }

    // 空間の設定
    physx::PxSceneDesc scene_desc(m_pPhysics->getTolerancesScale());
    scene_desc.gravity = physx::PxVec3(0, -9, 0);
    scene_desc.filterShader = physx::PxDefaultSimulationFilterShader;
    scene_desc.cpuDispatcher = m_pDispatcher;

    // GPUを使う場合はここで設定
    physx::PxCudaContextManagerDesc cuda_ctx_mgr_desc;
    ID3D11Device* dev = Renderer::GetDevice();
    cuda_ctx_mgr_desc.graphicsDevice = dev;

    m_pCudaCtxMgr = PxCreateCudaContextManager(*m_pFoundation, cuda_ctx_mgr_desc, PxGetProfilerCallback());
    if (m_pCudaCtxMgr)
    {
        if (!m_pCudaCtxMgr->contextIsValid())
        {
            m_pCudaCtxMgr->release();
        }
        else
        {
            scene_desc.cudaContextManager = m_pCudaCtxMgr;
            scene_desc.broadPhaseType = physx::PxBroadPhaseType::eGPU;
            scene_desc.flags |= physx::PxSceneFlag::eENABLE_PCM;
            scene_desc.flags |= physx::PxSceneFlag::eENABLE_GPU_DYNAMICS;
            scene_desc.flags |= physx::PxSceneFlag::eENABLE_STABILIZATION;
            scene_desc.gpuMaxNumPartitions = 8;
        }
    }

    // 空間のインスタンス化
    m_pScene = m_pPhysics->createScene(scene_desc);
    if (!m_pScene)
    {
        std::cerr << "Failed to create scene" << std::endl;
        return false;
    }

    // PVDの表示設定
    physx::PxPvdSceneClient* pvd_client = m_pScene->getScenePvdClient();
    if (pvd_client)
    {
        pvd_client->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONSTRAINTS, true);
        pvd_client->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_CONTACTS, true);
        pvd_client->setScenePvdFlag(physx::PxPvdSceneFlag::eTRANSMIT_SCENEQUERIES, true);
    }

    return true;
}

void PhysX_Impl::Update()
{
    // シミュレーション速度を指定する
    m_pScene->simulate(Time::GetDeltaTime());
    // PhysXの処理が終わるまで待つ
    m_pScene->fetchResults(true);
}

void PhysX_Impl::CleanUp()
{
    PxCloseExtensions();
    m_pScene->release();
    m_pDispatcher->release();
    m_pPhysics->release();
    if (m_pPvd)
    {
        m_pPvd->disconnect();
        physx::PxPvdTransport* transport = m_pPvd->getTransport();
        m_pPvd->release();
        transport->release();
    }
    m_pFoundation->release();
}
