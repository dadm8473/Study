#include "DXUT.h"
#include "Header.h"

CTitleScene::CTitleScene()
	: titleImage(new CMatrix), howToImage_1(new CMatrix), howToImage_2(new CMatrix), howToImage_3(new CMatrix), rankImage(new CMatrix), isHowTo(false), isRank(false),
	idImage(new CMatrix), kreditImage(new CMatrix), isIntro(true), isId(false), isKredit(false), intro(new CMatrix), currentHowto(0), titleBG(new CMatrix), titleBG_2(new CMatrix)
{
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 6; ++j)
		{
			num[i][j] = new CMatrix();
			num[i][j]->scale = D3DXVECTOR2(1.6f, 1.6f);
			num[i][j]->position.x = (390 + 32 * 3) + (32 * j);
			num[i][j]->position.y = 230 + 150 * i;
		}

		for (int j = 0; j < 3; ++j)
		{
			initial[i][j] = new CMatrix();
			initial[i][j]->scale = D3DXVECTOR2(1.6f, 1.6f);
			initial[i][j]->position.x = 290 + 32 * j;
			initial[i][j]->position.y = 230 + 150 * i;
		}
	}

	howToImage_1->SetAnimation(0.05f, 5, true);
	howToImage_2->SetAnimation(0.05f, 5, true);
	howToImage_3->SetAnimation(0.05f, 5, true);

	titleBG->SetAnimation(0.04f, 20, true);

	intro->SetAnimation(0.03f, 40, false);

	gScoreManager->Load();
}

CTitleScene::~CTitleScene()
{
	delete titleImage;
	delete howToImage_1;
	delete howToImage_2;
	delete howToImage_3;
	delete rankImage;
	delete intro;
	delete idImage;
	delete kreditImage;
	delete titleBG;
	delete titleBG_2;

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
	titleBG_2->Update(deltaTime);

	if (isIntro)
	{
		intro->Update(deltaTime);

		if (intro->isAniEnd)
			isIntro = false;
	}
	else
	{
		titleBG->Update(deltaTime);

		if (isHowTo)
		{
			switch (currentHowto)
			{
			case 0:
				howToImage_1->Update(deltaTime);
				break;
			case 1:
				howToImage_2->Update(deltaTime);
				break;
			case 2:
				howToImage_3->Update(deltaTime);
				break;
			}
		}
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
	gAssetManager->GetSoundAsset("Main")->Play();

	titleBG_2->Draw(sprite, gAssetManager->GetTexture("Sky"));
	if (isIntro)
		intro->Draw(sprite, gAssetManager->GetTexture("Intro"));
	else
	{
		titleBG->Draw(sprite, gAssetManager->GetTexture("TitleBG"));

		if (isHowTo)
		{
			switch (currentHowto)
			{
			case 0:
				howToImage_1->Draw(sprite, gAssetManager->GetTexture("HowTo1"));
				break;
			case 1:
				howToImage_2->Draw(sprite, gAssetManager->GetTexture("HowTo2"));
				break;
			case 2:
				howToImage_3->Draw(sprite, gAssetManager->GetTexture("HowTo3"));
				break;
			}
		}
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
					titleImage->currentScene = 5;
				break;
			case VK_DOWN:
				if (isHowTo || isRank || isId || isKredit)
					return;
				else if (titleImage->currentScene < 5)
					titleImage->currentScene++;
				else
					titleImage->currentScene = 0;
				break;

			case VK_LEFT:
				if (!isHowTo)
					return;
				else if (currentHowto > 0)
					currentHowto--;
				break;
			case VK_RIGHT:
				if (!isHowTo)
					return;
				else if (currentHowto < 2)
					currentHowto++;
				break;

			case VK_RETURN:
				switch (titleImage->currentScene)
				{
				case 0:
					// 게임 소개
					ChangeScene("Game_Stage_1");
					break;
				case 1:
					isId = !isId;
					break;
				case 2:
					isHowTo = !isHowTo;
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
