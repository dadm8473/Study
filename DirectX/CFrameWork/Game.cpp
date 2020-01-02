#include "DXUT.h"
#include "Header.h"

LPD3DXSPRITE gSprite = NULL;
CScene* gScene = NULL;

void ChangeScene(string sceneName)
{
	if (gScene)
		delete gScene;

	if (sceneName == "Title")
		gScene = new CTitleScene();
	else if (sceneName == "Game_Stage_1")
		gScene = new CGameScene();
	else if (sceneName == "Game_Stage_2")
		gScene = new CGameScene();
	else if (sceneName == "Ending_Win")
		gScene = new CEndingScene(true);
	else if (sceneName == "Ending_Lose")
		gScene = new CEndingScene(false);

}

void Init()
{
	D3DXCreateSprite(DXUTGetD3D9Device(), &gSprite);

	// AssetManager
	gAssetManager = new AssetManager;
	gAssetManager->LoadAssets();

	gScene = new CTitleScene();
}

void Term()
{
	// AssetManager
	gAssetManager->ReleaseAssets();

	if (gSprite)
		gSprite->Release();

	if (gScene)
		delete gScene;
}

void Update(float deltaTime)
{
	if (gScene)
		gScene->Update(deltaTime);
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