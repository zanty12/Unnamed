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
    // PhysX���ŗ��p����A���P�[�^�[
    static physx::PxDefaultAllocator m_defaultAllocator;
    // �G���[���p�̃R�[���o�b�N�ŃG���[���e�������Ă�
    static physx::PxDefaultErrorCallback m_defaultErrorCallback;
    // ��ʃ��x����SDK(PxPhysics�Ȃ�)���C���X�^���X������ۂɕK�v
    static physx::PxFoundation* m_pFoundation;
    // ���ۂɕ������Z���s��
    static physx::PxPhysics* m_pPhysics;
    // �V�~�����[�V�������ǂ��������邩�̐ݒ�Ń}���`�X���b�h�̐ݒ���ł���
    static physx::PxDefaultCpuDispatcher* m_pDispatcher;
    // �V�~�����[�V���������Ԃ̒P�ʂ�Actor�̒ǉ��Ȃǂ������ōs��
    static physx::PxScene* m_pScene;
    // PVD�ƒʐM����ۂɕK�v
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
