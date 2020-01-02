#include "DXUT.h"
#include "Header.h"

CTitleScene::CTitleScene()
	: titleImage(new CMatrix), introimage(new CMatrix), isIntro(true)
{
	introimage->SetAnimation(0.3f, 3, false);
}

CTitleScene::~CTitleScene()
{
	delete titleImage;
	delete introimage;
}

void CTitleScene::Update(float deltaTime)
{
	if (isIntro)
	{
		introimage->Update(deltaTime);
		if (introimage->isAniEnd)
			isIntro = false;
	}
	else
	{
		titleImage->Update(deltaTime);
	}
}

void CTitleScene::Render(LPD3DXSPRITE sprite)
{
	if (isIntro)
		introimage->Draw(sprite, gAssetManager->GetTexture("Intro"));
	else
		titleImage->Draw(sprite, gAssetManager->GetTexture("Title"));
}

void CTitleScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (!isIntro)
		{
			switch (wParam)
			{
			case VK_UP:
				if (titleImage->currentScene > 0)
					titleImage->currentScene--;
				else
					titleImage->currentScene = 1;
				break;
			case VK_DOWN:
				if (titleImage->currentScene < 1)
					titleImage->currentScene++;
				else
					titleImage->currentScene = 0;
				break;
			case VK_RETURN:
				switch (titleImage->currentScene)
				{
				case 0:
					// 게임 시작
					ChangeScene("Game_Stage_1");
					break;
				case 1:
					// 게임 종료
					PostQuitMessage(0);
					break;
				}
				break;
			}
		}
		break;
	}
}
