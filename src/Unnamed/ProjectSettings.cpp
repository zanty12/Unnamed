#include "ProjectSettings.h"

#include "manager.h"
#include "gamemode/GMDefaultGamemode.h"
#include "gamemode/GMShooting.h"
#include "gamemode/GMCrush.h"
#include "scene/CrushGame.h"
#include "scene/JointDemo.h"
#include "scene/physXtest.h"
#include "scene/testscene.h"

void ProjectSettings::InitializeManager()
{
    Manager::SetGameMode(new GMCrush());
    Manager::SetScene(new TestScene());
}
