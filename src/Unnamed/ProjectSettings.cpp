#include "ProjectSettings.h"

#include "manager.h"
#include "gamemode/GMDefaultGamemode.h"
#include "scene/physXtest.h"
#include "scene/testscene.h"

void ProjectSettings::InitializeManager()
{
    Manager::SetGameMode(new DefaultGameMode());
    Manager::SetScene(new physXtest());
}
