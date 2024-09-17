#include "CLoadBehaviour.h"

#include "manager.h"
#include "scene/CrushGame.h"
#include "system/timesystem.h"


void CLoadBehaviour::Update()
{
    timer_ -= Time::GetDeltaTime();
    if(timer_ < 0.0f)
    {
        Manager::SceneChange(new CrushGame());
    }
}
