#include "GMCrush.h"
#include "manager.h"
#include "scene/Clear.h"
#include "components/CText2D.h"

void GMCrush::Update()
{
	if (blocks_ == 0)
	{
		// Game Over
		blocks_ = 10000;
		/*Manager::UnloadCurrentScene();
		Manager::LoadScene(new Clear());*/
		Manager::SceneChange(new Clear());
	}
}

void GMCrush::SetBlocks(int blocks)
{
	blocks_ = blocks;
	Entity* score = Manager::FindEntityByName("score");
	if (score)
	{
		score->GetComponent<CText2D>()->SetText(L"Score: " + std::to_wstring(blocks_));
	}
}
