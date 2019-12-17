#include "DXUT.h"
#include "Header.h"

CTitleScene::CTitleScene()
	: titleImage(new CMatrix), howToImage(new CMatrix), rankImage(new CMatrix), isHowTo(false), isRank(false),
	idImage(new CMatrix), kreditImage(new CMatrix), isIntro(true), isId(false), isKredit(false), intro(new CMatrix)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			num[i][j] = new CMatrix();
			num[i][j]->position.x = 512 + 32 * j;
			num[i][j]->position.y = 100 + 100 * i;
		}

		for (int j = 0; j < 3; ++j)
		{
			initial[i][j] = new CMatrix();
			initial[i][j]->position.x = 100 + 32 * j;
			initial[i][j]->position.y = 100 + 100 * i;
		}
	}

	intro->SetAnimation(0.5f, 3, false);

	gScoreManager->Load();
}

CTitleScene::~CTitleScene()
{
	delete titleImage;
	delete howToImage;
	delete rankImage;
	delete intro;
	delete idImage;
	delete kreditImage;

	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 6; ++j)
			delete num[i][j];

		for (int j = 0; j < 3; ++j)
			delete initial[i][j];
	}
}

void CTitleScene::Update(float deltaTime)
{
	if (isIntro)
	{
		intro->Update(deltaTime);

		if (intro->isAniEnd)
			isIntro = false;
	}
	else
	{
		if (isHowTo)
			howToImage->Update(deltaTime);
		else if (isRank)
		{
			rankImage->Update(deltaTime);

			for (int i = 0; i < 3; ++i)
			{
				int tempScore = gScoreManager->scoreData[i].score;
				for (int j = 5; j >= 0; --j)
				{
					num[i][j]->currentScene = tempScore % 10;
					tempScore /= 10;
				}

				for (int j = 0; j < 6; ++j)
					num[i][j]->Update(deltaTime);

				for (int j = 0; j < 3; ++j)
				{
					initial[i][j]->currentScene = gScoreManager->scoreData[i].initial[j];
					initial[i][j]->Update(deltaTime);
				}
			}
		}
		else if (isId)
			idImage->Update(deltaTime);
		else if (isKredit)
			kreditImage->Update(deltaTime);
		else
			titleImage->Update(deltaTime);
	}
}

void CTitleScene::Render(LPD3DXSPRITE sprite)
{
	if (isIntro)
		intro->Draw(sprite, gAssetManager->GetTexture("Intro"));
	else
	{
		if (isHowTo)
			howToImage->Draw(sprite, gAssetManager->GetTexture("HowTo"));
		else if (isRank)
		{
			rankImage->Draw(sprite, gAssetManager->GetTexture("Rank"));

			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 6; ++j)
					num[i][j]->Draw(sprite, gAssetManager->GetTexture("Num"));

				for (int j = 0; j < 3; ++j)
					initial[i][j]->Draw(sprite, gAssetManager->GetTexture("Apb"));
			}
		}
		else if (isId)
			idImage->Draw(sprite, gAssetManager->GetTexture("Id"));
		else if (isKredit)
			kreditImage->Draw(sprite, gAssetManager->GetTexture("Kredit"));
		else
			titleImage->Draw(sprite, gAssetManager->GetTexture("Title"));
	}
}

void CTitleScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (!isIntro)
			switch (wParam)
			{
			case VK_UP:
				if (isHowTo || isRank || isId || isKredit)
					return;
				else if (titleImage->currentScene > 0)
					titleImage->currentScene--;
				else
					titleImage->currentScene = 7;
				break;
			case VK_DOWN:
				if (isHowTo || isRank || isId || isKredit)
					return;
				else if (titleImage->currentScene < 7)
					titleImage->currentScene++;
				else
					titleImage->currentScene = 0;
				break;

			case VK_LEFT:
				if (!isHowTo)
					return;
				else if (howToImage->currentScene > 0)
					howToImage->currentScene--;
				else
					howToImage->currentScene = 2;
				break;
			case VK_RIGHT:
				if (!isHowTo)
					return;
				else if (howToImage->currentScene < 2)
					howToImage->currentScene++;
				else
					howToImage->currentScene = 0;
				break;

			case VK_RETURN:
				switch (titleImage->currentScene)
				{
				case 0:
					// 게임 소개
					isId = !isId;
					break;
				case 1:
					isHowTo = !isHowTo;
					break;
				case 2:
					ChangeScene("Game_Stage_1");
					break;
				case 3:
					isRank = !isRank;
					break;
				case 4:
					// 크레딧
					isKredit = !isKredit;
					break;
				case 5:
					PostQuitMessage(0);
					break;
				}
				break;
			}
		break;
	}
}
