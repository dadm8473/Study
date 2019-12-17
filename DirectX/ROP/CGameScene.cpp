#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene(int stage)
	: tileEntryInfo(), currentTileIndex(0), tileList(),
	playerLife(3), rebirthTime(3), rebirthTimer(0), checkPointIndex(0),
	enemyEntryInfo(), currentEnemyIndex(0), enemyList(), enemyEntryTimer(0),
	enemyBulletList(), playerBulletList(), effectList(), objectList(),
	clearAttack(NULL), clearAttackCount(2), isClearAttack(false), gameStage(stage),
	stageUI(new CMatrix), ctnUI(new CMatrix), isCtn(false), reStartGame(false),
	isWin(false), isLose(false), itemUI(new CMatrix), inputScale(0), invincible(false),
	isStageClear(false), clearTimer(0), clearTime(3), getItemUI(new CMatrix), stageClearUI(new CMatrix)
{
	// ī�޶� ����
	mainCamera = new CCamera();
	// �� ���������� ���� ����
	map = new CMap(0, mainCamera);

	// ��Ƽ�� �ִϸ��̼�
	ctnUI->SetAnimation(1, 10, false);

	// �������� ���� �� �� ������ ȭ�� UI �̰� Draw���� �������� �ڵ� ���� �ø�����
	//stageUI->currentScene = gameStage - 1;

	// item Ui��ġ
	itemUI->position = D3DXVECTOR2(350, 200);
	itemUI->center = D3DXVECTOR2(64, 64);
	itemUI->currentScene = 0;

	// item �԰� �޼��� ���°� �ʱ�ȭ
	getItemUI->currentScene = 0;

	// �������� Ŭ���� �� ���� â �̸� a 0���� �ٲ��
	stageClearUI->a = 0;
	// �������� 2 Ŭ��� �߰���
	stageClearUI->currentScene = gameStage - 1;

	// �������� 1�϶� ������ ���ھ� �ʱ�ȭ
	if(gameStage == 1)
		score = 0;

	// ���ھ� UI
	for (int i = 0; i < 6; ++i)
	{
		scoreUI[i] = new CMatrix;
		scoreUI[i]->position.x = (1024 - 256) + (32 * i);
		scoreUI[i]->position.y = 100;

		scoreUI_clear[i] = new CMatrix;
		scoreUI_clear[i]->a = 0;
		scoreUI_clear[i]->scale = D3DXVECTOR2(2, 2);
		scoreUI_clear[i]->position.x = 384 + 42 * i;
		scoreUI_clear[i]->position.y = 450;
	}

	// �÷��̾� ������ ui
	for (int i = 0; i < 3; ++i)
	{
		playerLifeUI[i] = new CMatrix;
		playerLifeUI[i]->position.x = 50 + (64 * i);
		playerLifeUI[i]->position.y = 100;
		playerLifeUI[i]->scale = D3DXVECTOR2(0.7f, 0.7f);
	}

	// Ŭ���� ���� UI
	for (int i = 0; i < 2; ++i)
	{
		clearAttackUI[i] = new CMatrix;
		clearAttackUI[i]->position.x = 50 + (64 * i);
		clearAttackUI[i]->position.y = 150;
		clearAttackUI[i]->scale = D3DXVECTOR2(0.4f, 0.4f);
	}

	// Ÿ�� ����
	SetTile();

	// �� ����
	SetEnemy();

	// ī�޶� �Ѱ��� ����
	mainCamera->limitPos_Max.x = tileEntryInfo.size() * tileWidth - 1024;

	// �÷��̾� ��ȯ
	player = new CPlayer(D3DXVECTOR2(200, 384), mainCamera);
	player->parentScene = this;
	mainCamera->SetTarget(player);
}

CGameScene::~CGameScene()
{
	for (auto it = tileList.begin(); it != tileList.end(); ++it)
		if (*it)
			delete (*it);
	tileList.clear();

	for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
		if (*it)
			delete (*it);
	enemyList.clear();

	for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		if (*it)
			delete (*it);
	enemyBulletList.clear();

	for (auto it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		if (*it)
			delete (*it);
	playerBulletList.clear();

	for (auto it = effectList.begin(); it != effectList.end(); ++it)
		if (*it)
			delete (*it);
	effectList.clear();

	for (auto it = objectList.begin(); it != objectList.end(); ++it)
		if (*it)
			delete (*it);
	objectList.clear();

	for (int i = 0; i < 6; ++i)
	{
		delete scoreUI[i];
		delete scoreUI_clear[i];

		if (i < 2)
			delete clearAttackUI[i];

		if (i < 3)
			delete playerLifeUI[i];
	}

	if (clearAttack)
		delete clearAttack;

	if (mainCamera)
		delete mainCamera;

	if (map)
		delete map;

	if (player)
		delete player;

	if (stageUI)
		delete stageUI;

	if (ctnUI)
		delete ctnUI;

	if (itemUI)
		delete itemUI;

	if (getItemUI)
		delete getItemUI;

	if (stageClearUI)
		delete stageClearUI;
}

void CGameScene::Update(float deltaTime)
{
	if (mainCamera)
		mainCamera->Update(deltaTime);

	if (map)
		map->Update(deltaTime);

	TileUpdate(deltaTime);

	PlayerUpdate(deltaTime);

	EnemyUpdate(deltaTime);

	BulletUpdate(deltaTime);

	ObjectUpdate(deltaTime);

	RectUpdate(deltaTime);

	EffectUpdate(deltaTime);

	// Ŭ���� ���� ���� ������Ʈ
	if (isClearAttack)
	{
		clearAttack->Update(deltaTime, mainCamera->position);

		if (clearAttack->isAniEnd)
		{
			delete clearAttack;

			isClearAttack = false;
		}
	}

	UIUpdate(deltaTime);

	if (isStageClear)
	{
		// isStageClear�� true��� �÷��̾� �̵��� ������ ���ϰ� �ϰ� 
		// Ŭ���� �޼����� ���� 2���������� ��ȯ & Ŭ���� �޼��� ��� ���� �� ���
		// ���� â�� ���ھ� â ���� ����ġ�� �Ѿ�� �� ����â�� ���� �Ÿ�����
		if (stageClearUI->a >= 250)
		{
			stageClearUI->a = 255;
			// ���ھ� ���� ����
			int tempScore = score;
			for (int i = 5; i >= 0; --i)
			{
				scoreUI_clear[i]->currentScene = tempScore % 10;
				tempScore /=10;
			}
			for (int i = 0; i < 6; ++i)
			{
				scoreUI_clear[i]->Update(deltaTime);
				if (scoreUI_clear[i]->a < 255)
					scoreUI_clear[i]->a += deltaTime * 255;
				else
					scoreUI_clear[i]->a = 255;
			}
		}
		else if (stageClearUI->a < 255)
			stageClearUI->a += 150 * deltaTime;

		player->position.x += 250 * deltaTime; // clearTime ���� �ڵ����� ������ �̵��ϰ� ��

		// Ŭ���� �ϸ� ������
		invincible = true;

		clearTimer += deltaTime;
		if (clearTimer > clearTime)
		{
		}
		// Ŭ���� UI ������Ʈ
		stageClearUI->Update(deltaTime);
	}

	// ���� �����
	if (reStartGame)
	{
		// ���������� ���� ������� �ٸ�
		switch (gameStage)
		{
		case 1:
			ChangeScene("Game_Stage_1");
			break;
		case 2:
			ChangeScene("Game_Stage_2");
			break;
		}
		reStartGame = false;
		return;
	}

	// �¸�
	if (isWin)
	{
		ChangeScene("Ending_Win");
		return;
	}

	// �й�
	if (isLose)
	{
		ChangeScene("Ending_Lose");
		return;
	}
}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
	if (map)
		map->Render(sprite);

	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Render(sprite);

	for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		(*it)->Render(sprite);

	for (auto it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		(*it)->Render(sprite);

	for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
		(*it)->Render(sprite);

	if (player)
		player->Render(sprite);

	if (isClearAttack)
		clearAttack->Draw(sprite, gAssetManager->GetTexture("Effect"));

	for (auto it = objectList.begin(); it != objectList.end(); ++it)
		(*it)->Render(sprite);

	for (auto it = effectList.begin(); it != effectList.end(); ++it)
		(*it)->Render(sprite);

	for (int i = 0; i < clearAttackCount; ++i)
		clearAttackUI[i]->Draw(sprite, gAssetManager->GetTexture("Player"));

	for (int i = 0; i < 6; ++i)
		scoreUI[i]->Draw(sprite, gAssetManager->GetTexture("Num"));

	for (int i = 0; i < playerLife; ++i)
		playerLifeUI[i]->Draw(sprite, gAssetManager->GetTexture("Player"));

	if (itemUI)
		itemUI->Draw(sprite, gAssetManager->GetTexture("Item"));

	if (getItemUI)
		getItemUI->Draw(sprite, gAssetManager->GetTexture("ItemUI"));

	if (stageUI)
		stageUI->Draw(sprite, gAssetManager->GetTexture("StageUI"));

	if (isCtn)
		ctnUI->Draw(sprite, gAssetManager->GetTexture("conUI"));

	if (isStageClear)
		stageClearUI->Draw(sprite, gAssetManager->GetTexture("StageClear"));

	if (isStageClear)
		for (int i = 0; i < 6; ++i)
			scoreUI_clear[i]->Draw(sprite, gAssetManager->GetTexture("Num"));
}

void CGameScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_SPACE:
			// �÷��̾ �ְ� Ŭ��� �ƴҶ�
			if (player && !isStageClear)
				player->Jump();
			break;
		case VK_F1:
			// Ŭ��� �ƴҶ�
			if(!isStageClear)
				invincible = !invincible;
			break;
		case VK_F2:
			// �÷��̾� ���׷��̵� �Ѱ�ġ�� ���� �ʰ� ��
			if (player && player->upgrade < 2)
			{
				player->upgrade++;
				player->Reset();
			}
			break;
		case VK_F3:
			// �÷��̾� ���׷��̵� �Ѱ�ġ�� ���� �ʰ� ��
			if (player && player->upgrade > 0)
			{
				player->upgrade--;
				player->Reset();
			}
			break;
		case VK_RETURN:
			// ��Ƽ�� â���� ����ġ�� �����
			if (isCtn)
				reStartGame = true;

			if (isStageClear)
			{
				if (gameStage == 1)
				{
					gameStage = 2;
					reStartGame = true;
				}
				else if (gameStage == 2)
					isWin = true;
			}
			break;
		case 'Q':
			// �÷��̾� ��� ġƮŰ
			if (player)
				player->isDie = true;
			break;
		case 'S':
			// ������ ġƮŰ
			if (player)
				player->velocity_X = 3000;
			break;
		case 'C':
			// Ŭ���� ����
			if (player && !isClearAttack && clearAttackCount > 0 && !isStageClear)
				ClearAttack();
			break;
		}
		break;
	}
}

void CGameScene::SetTile()
{
	for (int i = 0; i < 200; ++i)
	{
		int setTile = rand() % 10 + 1;

		if (i <= 3)
		{
			tileEntryInfo.push_back(TileEntryInfo(0));
			continue;
		}

		if (i % 30 == 0)
		{
			tileEntryInfo.push_back(TileEntryInfo(0, 100));
			tileEntryInfo.push_back(TileEntryInfo(0));
			tileEntryInfo.push_back(TileEntryInfo(0, -1, true));
			continue;
		}

		if (i == 198)
		{
			tileEntryInfo.push_back(TileEntryInfo(0, 777));
			tileEntryInfo.push_back(TileEntryInfo(0));
			tileEntryInfo.push_back(TileEntryInfo(0));
			tileEntryInfo.push_back(TileEntryInfo(0));
			continue;
		}

		if (setTile <= 8)
		{
			switch (setTile)
			{
			case 1:
			case 2:
			case 3:
			case 4:
				tileEntryInfo.push_back(TileEntryInfo(0));
				break;
			case 5:
			case 6:
				tileEntryInfo.push_back(TileEntryInfo(0, rand() % 6 + 1 + 10));
			case 7:
				tileEntryInfo.push_back(TileEntryInfo(0, rand() % 2 + 1));
				break;
			}
		}
		else if(setTile <= 9)
			tileEntryInfo.push_back(TileEntryInfo(1));
		else if(setTile <= 10)
			tileEntryInfo.push_back(TileEntryInfo(2));
	}
}

void CGameScene::SetEnemy()
{
	enemyEntryInfo.push_back(EnemyEntryInfo(0, 2));
}

void CGameScene::TileUpdate(float deltaTime)
{
	int currentTileLength = tileList.size() * tileWidth;

	while (currentTileLength < mainCamera->position.x + 1280)
	{
		if (currentTileIndex >= tileEntryInfo.size())
			break;

		D3DXVECTOR2 entryPos = D3DXVECTOR2(0, 0);

		if (currentTileIndex == 0)
			entryPos.y = 384;
		else
		{
			CTile* t = tileList[currentTileIndex - 1];

			entryPos.x = t->position.x + tileWidth;
			entryPos.y = t->position.y;

			switch (tileEntryInfo[currentTileIndex].type)
			{
			case 1:
				if (t->type != 2)
					entryPos.y -= 100;
				break;
			default:
				if (t->type == 2)
					entryPos.y += 100;
				break;
			}
		}

		CTile* tile = new CTile(entryPos, tileEntryInfo[currentTileIndex].type, mainCamera);
		tileList.push_back(tile);

		if (tileEntryInfo[currentTileIndex].objectType > 0)
		{
			D3DXVECTOR2	entryPos = D3DXVECTOR2(tileList[currentTileIndex]->position.x + 128, tileList[currentTileIndex]->position.y + 64);
			CObject* object = new CObject(entryPos, tileEntryInfo[currentTileIndex].objectType, mainCamera);
			objectList.push_back(object);
		}

		currentTileIndex++;
	}

	for (int i = 0; i < tileList.size(); ++i)
		tileList[i]->Update(deltaTime);
}

void CGameScene::PlayerUpdate(float deltaTime)
{
	if (player)
	{
		// �������� Ŭ���� ���� ���� �ƴҶ�
		if (!isStageClear)
		{
			// �÷��̾� �̵�
			if (GetKeyState(VK_LEFT) & 0x8000)
				player->Move(-1, deltaTime);
			if (GetKeyState(VK_RIGHT) & 0x8000)
				player->Move(1, deltaTime);
			// �÷��̾� ����
			if (GetKeyState('X') & 0x8000)
				player->Attack();
			if (GetKeyState('Z') & 0x8000)
				player->OverAttack();
		}
		// �÷��̾� Ÿ�� �ε��� �޾ƾƿ���
		int tileIndex = player->position.x / tileWidth;
		// Ÿ�� �ε����� ������� üũ����Ʈ�� �˻�
		if (tileIndex >= 0 && tileIndex < tileEntryInfo.size())
			if (tileEntryInfo[tileIndex].checkPoint && tileIndex > checkPointIndex)
			{
				// üũ����Ʈ ����
				checkPointIndex = tileIndex;

				// üũ����Ʈ �޼��� ����ֱ�
				getItemUI->currentScene = 8;
				getItemUI->a = 255;
			}
		// �÷��̾� ������Ʈ
		player->Update(deltaTime);

		// �����϶� isDie�� ������ false a �ٿ���
		if (invincible)
		{
			player->isDie = false;
			player->a = 150;
		}
		else
			player->a = 255;

		// �÷��̾ �׾��ٰ� ����� �����°� ���� ���Ż糳�Գ���
		// �׷��� a ���� 0���� ���� ��Ȱ��Ű�� a 255���� �÷���
		if (player->a != 255)
			player->a += deltaTime;
		else if (player->a > 255)
			player->a = 255;

		// Ư������ ī��Ʈ ����
		if (clearAttackCount >= 3)
			clearAttackCount = 2;

		// �÷��̾� ���
		if (player->isDie)
		{
			mainCamera->SetTarget(NULL);

			player = NULL;
			delete player;
		}
	}
	else
	{
		rebirthTimer += deltaTime;
		// ��Ȱ
		if (rebirthTimer > rebirthTime)
		{
			rebirthTimer = 0;
			// ������ 0�� ���ų� 0���� Ŭ����
			if (--playerLife >= 0)
			{
				// üũ����Ʈ���� ��Ȱ
				D3DXVECTOR2 entryPos = tileList[checkPointIndex]->position;
				// Ÿ�� �����ǿ��� ��Ȱ�ϸ� Ÿ�� ���Ͱ� ��� ���ʿ��� ��Ȱ�� 128 �÷���
				entryPos.x += 128;

				player = new CPlayer(entryPos, mainCamera);
				player->parentScene = this;
				mainCamera->SetTarget(player);
				player->a = 0;
			}
			else
				// ��Ƽ��
				isCtn = true;
		}
	}
}

void CGameScene::EnemyUpdate(float deltaTime)
{
	enemyEntryTimer += deltaTime;

	while (player && enemyEntryTimer > enemyEntryInfo[currentEnemyIndex].timer)
	{
		D3DXVECTOR2 entryPos = D3DXVECTOR2(mainCamera->position.x + 1024 + 128, player->ground_Y_Pos - 100 - rand() % 100);

		CEnemy* enemy = new CEnemy(entryPos, enemyEntryInfo[currentEnemyIndex].type, mainCamera);
		enemy->parentScene = this;
		enemyList.push_back(enemy);

		currentEnemyIndex++;

		if (currentEnemyIndex >= enemyEntryInfo.size())
		{
			currentEnemyIndex = 0;
			enemyEntryTimer = 0;
			break;
		}
	}
	
	for (auto it = enemyList.begin(); it != enemyList.end();)
	{
		(*it)->Updata(deltaTime);

		if (player)
			player->SetTarget(*it);

		if ((*it)->isDie)
		{
			// score & effect
			effectList.push_back(new CEffect((*it)->position, mainCamera));
			score += 50 + rand() % 50;
		}

		if ((*it)->isDestroyed || (*it)->isDie)
		{
			delete (*it);
			it = enemyList.erase(it);
		}
		else
			++it;
	}
}

void CGameScene::BulletUpdate(float deltaTime)
{
	for (auto it = enemyBulletList.begin(); it != enemyBulletList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestoryed)
		{
			delete (*it);
			it = enemyBulletList.erase(it);
		}
		else
			++it;
	}

	for (auto it = playerBulletList.begin(); it != playerBulletList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestoryed)
		{
			delete (*it);
			it = playerBulletList.erase(it);
		}
		else
			++it;
	}
}

void CGameScene::ObjectUpdate(float deltaTime)
{
	for (auto it = objectList.begin(); it != objectList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed)
		{
			delete (*it);
			it = objectList.erase(it);
		}
		else
			++it;
	}
}

void CGameScene::RectUpdate(float deltaTime)
{
	// player < enemyBullet object
	if (player)
	{
		// �� �Ѿ��̶� �ε�ġ�� �Ѿ� ���� �÷��̾� ���
		for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		{
			RECT ref;
			if (IntersectRect(&ref, &player->rect, &(*it)->rect))
			{
				player->isDie = true;
				(*it)->isDestoryed = true;
			}
		}
		// ������Ʈ�� �ε�ģ ���
		for (auto it = objectList.begin(); it != objectList.end(); ++it)
		{
			RECT ref;
			if (IntersectRect(&ref, &player->rect, &(*it)->rect))
			{
				player->Reset();

				switch ((*it)->type)
				{
				case 11:
					player->DoubleJump();
					break;
				case 12:
					player->SpeedUP();
					break;
				case 13:
					player->LongAttack();
					break;
				case 14:
					player->MultiAttack();
					break;
				case 15:
					player->HomingAttack();
					break;
				case 16:
					clearAttackCount++;
					break;
				case 100:
					if(player->upgrade < 2)
						player->upgrade++;
					// �����̳� rect ���ֱ�
					(*it)->isActive = false;
					// ������ UI �Ⱥ��̰� ���ֱ�
					itemUI->currentScene = 0;
					// ���׷��̵� �޼��� ����ֱ�
					getItemUI->currentScene = 7;
					getItemUI->a = 255;
					break;
				case 777:
					// Ŭ����
					isStageClear = true;
					break;
				default:
					player->isDie = true;
					break;
				}
				// ������Ʈ�� Ÿ���� 11 ���� 19 ������ ��� itemUI�� currentScene�� ����
				if ((*it)->type > 10 && (*it)->type < 20)
				{
					itemUI->currentScene = (*it)->type - 10;
					inputScale = 1;

					// ������ �԰� �޼��� ����ִ°͵� ���⿡�ٰ� ��
					getItemUI->currentScene = (*it)->type - 10;
					getItemUI->a = 255;
				}
				
				// ���⿡ ���� �Ⱦ����� 2���� 100�����̳� 777��������Ŭ����
				if ((*it)->type != 2 && (*it)->type != 100 && (*it)->type != 777)
					(*it)->isDestroyed = true;
			}
		}
	}

	// playerBullet > enemy object
	for (auto it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		// �÷��̾� �Ѿ˿� ���ʹ� ������ �Ѿ˰� ���ʹ� ���
		for (auto it2 = enemyList.begin(); it2 != enemyList.end(); ++it2)
		{
			RECT ref;
			if (IntersectRect(&ref, &(*it)->rect, &(*it2)->rect))
			{
				(*it)->isDestoryed = true;
				(*it2)->isDie = true;
			}
		}
		// �÷��̾� �Ѿ˿� ������Ʈ�� �¾Ѵµ� 1�ϰ�츸 �Ѵ� ���
		for (auto it2 = objectList.begin(); it2 != objectList.end(); ++it2)
		{
			RECT ref;
			if (IntersectRect(&ref, &(*it)->rect, &(*it2)->rect) && (*it2)->type == 1)
			{
				(*it)->isDestoryed = true;
				(*it2)->isDestroyed = true;
			}
		}
	}
}

void CGameScene::EffectUpdate(float deltaTime)
{
	// ����Ʈ
	for (auto it = effectList.begin(); it != effectList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed)
		{
			delete (*it);
			it = effectList.erase(it);
		}
		else
			++it;
	}
}

void CGameScene::ClearAttack()
{
	// �Է¹����� ���� �������
	clearAttack = new CMatrix();
	clearAttack->position = D3DXVECTOR2(player->position.x + 200, player->position.y);
	clearAttack->center = D3DXVECTOR2(64, 64);
	clearAttack->scale = D3DXVECTOR2(1.5f, 1.5f);
	clearAttack->SetAnimation(0.3f, 3, false);

	clearAttackCount--;
	isClearAttack = true;

	// ��, �� �Ѿ� ����Ʈ ����
	for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
		if (*it)
			(*it)->isDie = true;

	for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		if (*it)
			(*it)->isDestoryed = true;
}

void CGameScene::UIUpdate(float deltaTime)
{
	// ���� �־��ֱ�
	int tempScore = score;
	for (int i = 5; i >= 0; --i)
	{
		scoreUI[i]->currentScene = tempScore % 10;
		tempScore /= 10;
	}

	// ����, Ư������, ������ ����
	for (int i = 0; i < 6; ++i)
	{
		scoreUI[i]->Update(deltaTime);
		if (i < 2)
			clearAttackUI[i]->Update(deltaTime);
		if (i < 3)
			playerLifeUI[i]->Update(deltaTime);
	}

	// �������� UI
	if (stageUI)
	{
		stageUI->Update(deltaTime);
		
		if (stageUI->a <= 0)
			stageUI->a = 0;
		else
			stageUI->a -= 100 * deltaTime;
	}

	if (getItemUI->a > 0)
	{
		getItemUI->a -= 100 * deltaTime;
		if (getItemUI->a < 0)
		{
			getItemUI->a = 0;
		}
	}

	// ��Ƽ��
	if (isCtn)
	{
		ctnUI->Update(deltaTime);
		
		if (ctnUI->isAniEnd)
		{
			isCtn = false;
			isLose = true;
		}
	}

	if (itemUI)
	{
		itemUI->Update(deltaTime);

		// �÷��̾ ������
		if (player)
		{
			// �������� 0�� �ƴҶ��� ���� �ڲ� player reset �ҷ��� ���� ������ & ������ ��ź�δ� ������
			if (inputScale != 0 && itemUI->currentScene != 2 && itemUI->currentScene != 6)
				inputScale -= (deltaTime / 5);
			// 0���� ���� deltaTime ���ϰ� ����
			if (inputScale < 0)
			{
				player->Reset();
				inputScale = 0;
			}
			// 0 �ɶ����� ����
			itemUI->scale = D3DXVECTOR2(inputScale, inputScale);
		}
		else
			// �÷��̾� ������ �̻��Ѱ� �ߴµ� ������ 0���� ����
			itemUI->currentScene = 0;
	}

	// ������ ������ �޼��� â �����
	if (getItemUI)
	{
		// ���İ� ���� ������
		getItemUI->Update(deltaTime);

		if (getItemUI->a != 0)
			getItemUI->a -= 100 * deltaTime;
		else
			getItemUI->a = 0;
	}
}
