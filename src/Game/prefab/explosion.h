#pragma once
#include "entity.h"
#include "manager.h"
#include "components/Shapes/CPlane.h"
#include "components/CSprite2D.h"
#include "components/CExplosionBehaviour.h"
#include "traits/object/spawnable.h"

class Explosion : public Spawnable
{
private:
    Entity* entity_ = nullptr;
    XMFLOAT3 position_ = XMFLOAT3(0.0f,0.0f,0.0f);
public:
    Explosion() = default;
    ~Explosion() = default;
    void Start()
    {
        entity_ = Manager::MakeEntity("explosion");
        Transform::RotateTo(entity_->GetTransform(),XMFLOAT3(-3.14f/2.0f,0.0,0.0f));
        Transform::MoveTo(entity_->GetTransform(),position_);
        CPlane* plane = new CPlane();
        CSprite2D* sprite2d = new CSprite2D();
        sprite2d->SetWidth(4);
        sprite2d->SetHeight(4);
        sprite2d->SetLoop(false);
        sprite2d->SetFPS(16);
        plane->SetBillboard(1);
        plane->SetTexture(sprite2d);
        entity_->AddComponent(plane);
        entity_->AddComponent(sprite2d);
		entity_->AddComponent(new CExplosionBehaviour());
        entity_->Start();
    }
    void SetPosition(XMFLOAT3 position)
    {
        position_ = position;
    }

	void Spawn()
	{
		Start();
	}
};
