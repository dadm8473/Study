#include "DXUT.h"
#include "Header.h"

CTitleScene::CTitleScene()
	:CScene(), isHowTo(false), titleImage(new CMatrix), howToImage(new CMatrix), rankImage(new CMatrix)
{
	mouseX = 0;
	mouseY = 0;
	leftMouseClicked = false;
	isRank = false;
	titleImage->currentScene = 0;
	mainTime = 1;

	SetRect(&startRect, 645, 415, 765, 455);
	SetRect(&howToRect, 645, 505, 815, 545);
	SetRect(&rankRect, 645, 595, 845, 645);
	SetRect(&exitRect, 645, 680, 740, 720);
	SetRect(&leaveRect, 0, 0, 1024, 768);
}

CTitleScene::~CTitleScene()
{
	delete titleImage;
	delete howToImage;
}

void CTitleScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);

	howToImage->Update(deltaTime);
	titleImage->Update(deltaTime);
	rankImage->Update(deltaTime);

	SetRect(&mouseRect, mouseX - 1, mouseY - 1, mouseX + 1, mouseY + 1);

	if (leftMouseClicked)
	{
		leftMouseClicked = false;
		RECT ref;

		if (isHowTo)
		{
			if (IntersectRect(&ref, &mouseRect, &leaveRect))
				isHowTo = !isHowTo;
		}

		if (isRank)
		{
			if (IntersectRect(&ref, &mouseRect, &leaveRect))
				isRank = !isRank;
		}

		if (IntersectRect(&ref, &mouseRect, &startRect))
			ChangeScene(1);

		if (IntersectRect(&ref, &mouseRect, &howToRect))
			isHowTo = !isHowTo;

		if (IntersectRect(&ref, &mouseRect, &rankRect))
			isRank = !isRank;

		if (IntersectRect(&ref, &mouseRect, &exitRect))
			PostQuitMessage(0);
	}
	else
	{
		RECT ref;
		if (IntersectRect(&ref, &mouseRect, &startRect))
			titleImage->currentScene = 0;

		if (IntersectRect(&ref, &mouseRect, &howToRect))
			titleImage->currentScene = 1;

		if (IntersectRect(&ref, &mouseRect, &rankRect))
			titleImage->currentScene = 2;

		if (IntersectRect(&ref, &mouseRect, &exitRect))
			titleImage->currentScene = 3;

		if (isHowTo)
		{
			if (leftMouseClicked)
				if (IntersectRect(&ref, &mouseRect, &leaveRect))
					howToImage->currentScene = 1;
				else
					howToImage->currentScene = 0;
		}

		if (isRank)
		{
			if (leftMouseClicked)
				if (IntersectRect(&ref, &mouseRect, &leaveRect))
					rankImage->currentScene = 1;
				else
					rankImage->currentScene = 0;
		}
	}
}

void CTitleScene::Render(LPD3DXSPRITE sprite)
{
	CScene::Render(sprite);

	if (isHowTo)
		howToImage->Draw(sprite, gAssetManager->GetTexture("howTo"));
	else if (isRank)
		rankImage->Draw(sprite, gAssetManager->GetTexture("ranking"));
	else
		titleImage->Draw(sprite, gAssetManager->GetTexture("title"));
}

void CTitleScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_MOUSEMOVE:
		mouseX = LOWORD(lParam);
		mouseY = HIWORD(lParam);
		break;
	case WM_LBUTTONDOWN:
		leftMouseClicked = true;
		break;
	}
}
