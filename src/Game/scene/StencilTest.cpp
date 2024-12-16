#include "StencilTest.h"
#include "manager.h"
#include "components/CAudio.h"
#include "prefab/player.h"
#include "components/CCamera.h"
#include "components/CPlane.h"
#include "components/CRect2D.h"
#include "components/CSprite2D.h"
#include "components/CText2D.h"
#include "components/CTexture2D.h"
#include "components/CVideoTexture.h"
#include <components/CModelRenderer.h>

#include "components/CScreenStencil.h"
#include "components/CShadowVolume.h"


void StencilTest::Setup()
{
    Entity* plane = Manager::MakeEntity("Water");
    plane->GetTransform().scale = XMFLOAT3(100, 1.0, 100);
    CPlane* water = new CPlane();
    CTexture2D* texture_2d = new CTexture2D(L"asset/texture/water.png");
    water->SetTexture(texture_2d);
    plane->AddComponent(water);
    plane->AddComponent(texture_2d);
    plane->Start();
    water->SetEndUV(XMFLOAT2(1.0f, 1.0f));

    //camera
    Entity* cam = Manager::MakeEntity("Camera");
    Transform::MoveBy(cam->GetTransform(), XMFLOAT3(0.0f, 2.0f, 0.0f));
    CCamera* camera = new CCamera();
    cam->AddComponent(camera);
    camera->SetLookAtParent(true);
    camera->SetSmoothing(true);
    camera->Activate();
    camera->SetOffset(XMFLOAT3(0.0f, 3.0f, -10.0f));
    cam->Start();

    Entity* shadow = Manager::MakeEntity("shadow");
    CModelRenderer* animModel = new CModelRenderer();
    animModel->Load("asset\\model\\cube.obj");
    Transform::ScaleTo(animModel->GetLocalTransform(), XMFLOAT3(0.8f, 0.8f, 0.8f));
    Transform::MoveTo(animModel->GetLocalTransform(), XMFLOAT3(0.0f, 0.8f, 0.0f));
    shadow->AddComponent(animModel);
    CShadowVolume* shadow_component = new CShadowVolume();
    shadow->AddComponent(shadow_component);
    shadow->Start();

    //stencil
    Entity* stencil = Manager::MakeEntity("stencil");
    CScreenStencil* stencil_component = new CScreenStencil();
    stencil->AddComponent(stencil_component);
    stencil->Start();
}


