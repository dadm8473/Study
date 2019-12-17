#include "DXUT.h"
#include "Header.h"
#include <ctime>

LPD3DXSPRITE gSprite = NULL;
CScene* gScene = NULL;

float tileWidth = 0;
int score = 0;

void ChangeScene(string sceneName)
{
	if (gScene)
		delete gScene;

	if (sceneName == "Title")
		gScene = new CTitleScene();
	else if (sceneName == "Game_Stage_1")
		gScene = new CGameScene(1);
	else if (sceneName == "Game_Stage_2")
		gScene = new CGameScene(2);
	else if (sceneName == "Ending_Win")
		gScene = new CEndingScene(true);
	else if (sceneName == "Ending_Lose")
		gScene = new CEndingScene(false);
}

void Init()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &gSprite);

	gAssetManager = new AssetManager();
	gAssetManager->LoadAssets();

	gScoreManager = new ScoreManager();

	tileWidth = gAssetManager->GetTexture("Tile")->width;

	gScene = new CTitleScene();
}

void Term()
{
	gAssetManager->ReleaseAssets();

	if (gSprite)
		gSprite->Release();

	if (gScene)
		delete gScene;
}

void Update(float deltaTIme)
{
	srand((unsigned int)time(0));

	if (gScene)
		gScene->Update(deltaTIme);
}

void Render()
{
	gSprite->Begin(D3DXSPRITE_ALPHABLEND);

	if (gScene)
		gScene->Render(gSprite);

	gSprite->End();
}

void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (gScene)
		gScene->MsgProc(uMsg, wParam, lParam);

	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_F4:
			ChangeScene("Title");
			break;
		case VK_F5:
			ChangeScene("Game_Stage_1");
			break;
		case VK_F6:
			ChangeScene("Game_Stage_2");
			break;
		case VK_F7:
			ChangeScene("Ending_Win");
			break;
		case VK_F8:
			ChangeScene("Ending_Lose");
			break;
		}
		break;
	}
}

float GetAngle(float x, float y)
{
	return D3DXToDegree(atan2(y, x)) + 90;
}
