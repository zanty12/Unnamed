#include "ProjectSettings.h"

#include "manager.h"
#include "gamemode/GMDefaultGamemode.h"
#include "gamemode/GMShooting.h"
#include "scene/physXtest.h"
#include "scene/testscene.h"

void ProjectSettings::InitializeManager()
{
    Manager::SetGameMode(new Shooting());
    Manager::SetScene(new physXtest());
}
