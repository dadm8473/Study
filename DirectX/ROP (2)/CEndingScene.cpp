#include "DXUT.h"
#include "Header.h"

CEndingScene::CEndingScene(bool isWin)
	: winImage(new CMatrix), loseImage(new CMatrix), isWin(isWin), isRank(false), rankMessage(new CMatrix),
	isEnter(false), noRankMessage(new CMatrix), currentInputIndex(0), blinkTimer(0)
{
	for (int i = 0; i < 6; ++i)
	{
		num[i] = new CMatrix;
		num[i]->position.x = 348 + 50 * i;
		num[i]->position.y = 382;
		num[i]->scale = D3DXVECTOR2(2.5f, 2.5f);
	}

	for (int i = 0; i < 3; ++i)
	{
		initial[i] = new CMatrix;
		initial[i]->position.x = 337 + 137 * i;
		initial[i]->position.y = 535;
		initial[i]->scale = D3DXVECTOR2(2.3f, 2.3f);
	}

	gScoreManager->Load();
	if (gScoreManager->scoreData[2].score < score)
	{
		isRank = true;

		ScoreInfo myData;
		myData.score = score;

		gScoreManager->scoreData.push_back(myData);
	}
}

CEndingScene::~CEndingScene()
{
	delete winImage;
	delete loseImage;

	for (int i = 0; i < 6; ++i)
		delete num[i];

	for (int i = 0; i < 3; ++i)
		delete initial[i];

	delete noRankMessage;
	delete rankMessage;
}

void CEndingScene::Update(float deltaTime)
{
	if (isWin)
	{
		winImage->Update(deltaTime);
		gAssetManager->GetSoundAsset("Win")->Play();
	}
	else
	{
		loseImage->Update(deltaTime);
		gAssetManager->GetSoundAsset("Lose")->Play();
	}

	if (isRank)
	{
		rankMessage->Update(deltaTime);

		int tempScore = score;
		for (int i = 5; i >= 0; --i)
		{
			num[i]->currentScene = tempScore % 10;
			tempScore /= 10;
		}

		for (int i = 0; i < 6; ++i)
			num[i]->Update(deltaTime);

		blinkTimer += deltaTime * 3;

		for (int i = 0; i < 3; ++i)
		{
			initial[i]->currentScene = gScoreManager->scoreData[3].initial[i];
			initial[i]->Update(deltaTime);
		}
	}
	else
		noRankMessage->Update(deltaTime);

	if (isEnter)
	{
		gScoreManager->Save();
		ChangeScene("Title");
		return;
	}
}

void CEndingScene::Render(LPD3DXSPRITE sprite)
{
	if (isWin)
		winImage->Draw(sprite, gAssetManager->GetTexture("Win"));
	else
		loseImage->Draw(sprite, gAssetManager->GetTexture("Lose"));

	if (isRank)
	{
		rankMessage->Draw(sprite, gAssetManager->GetTexture("Rank_End"));
		for (int i = 0; i < 6; ++i)
			num[i]->Draw(sprite, gAssetManager->GetTexture("Num"));

		for (int i = 0; i < 3; ++i)
			if (currentInputIndex >= i)
				if (currentInputIndex != i || (currentInputIndex == i && (int)blinkTimer % 2 == 0))
					initial[i]->Draw(sprite, gAssetManager->GetTexture("Apb"));
	}
	else
		noRankMessage->Draw(sprite, gAssetManager->GetTexture("noRank"));
}

void CEndingScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		if (isRank)
		{
			if (wParam >= 65 && wParam <= 90)
				gScoreManager->scoreData[3].initial[currentInputIndex] = wParam - 65;
		}

		switch (wParam)
		{
		case VK_RETURN:
			currentInputIndex++;
			if (currentInputIndex == 4 || !isRank)
				isEnter = true;
			break;
		}
		break;
	}
}
