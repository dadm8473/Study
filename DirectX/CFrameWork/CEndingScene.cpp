#include "DXUT.h"
#include "Header.h"

CEndingScene::CEndingScene(bool isWin)
	: winImage(new CMatrix), loseImage(new CMatrix), isWin(isWin)
{
}

CEndingScene::~CEndingScene()
{
	delete winImage;
	delete loseImage;
}

void CEndingScene::Update(float deltaTime)
{
	if (isWin)
		winImage->Update(deltaTime);
	else
		loseImage->Update(deltaTime);
}

void CEndingScene::Render(LPD3DXSPRITE sprite)
{
	if (isWin)
		winImage->Draw(sprite, gAssetManager->GetTexture("Win"));
	else
		loseImage->Draw(sprite, gAssetManager->GetTexture("Lose"));
}

void CEndingScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_RETURN:
			ChangeScene("Title");
			break;
		}
		break;
	}
}
