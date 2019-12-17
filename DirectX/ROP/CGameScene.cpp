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
	// 카메라 생성
	mainCamera = new CCamera();
	// 맵 스테이지에 따라 생성
	map = new CMap(0, mainCamera);

	// 컨티뉴 애니메이션
	ctnUI->SetAnimation(1, 10, false);

	// 스테이지 시작 할 때 나오는 화면 UI 이거 Draw에서 오류나는 코드 위로 올린거임
	//stageUI->currentScene = gameStage - 1;

	// item Ui배치
	itemUI->position = D3DXVECTOR2(350, 200);
	itemUI->center = D3DXVECTOR2(64, 64);
	itemUI->currentScene = 0;

	// item 먹고 메세지 띄우는거 초기화
	getItemUI->currentScene = 0;

	// 스테이지 클리어 시 띄우는 창 미리 a 0으로 바꿔둠
	stageClearUI->a = 0;
	// 스테이지 2 클리어가 뜨게함
	stageClearUI->currentScene = gameStage - 1;

	// 스테이지 1일때 들어오면 스코어 초기화
	if(gameStage == 1)
		score = 0;

	// 스코어 UI
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

	// 플레이어 라이프 ui
	for (int i = 0; i < 3; ++i)
	{
		playerLifeUI[i] = new CMatrix;
		playerLifeUI[i]->position.x = 50 + (64 * i);
		playerLifeUI[i]->position.y = 100;
		playerLifeUI[i]->scale = D3DXVECTOR2(0.7f, 0.7f);
	}

	// 클리어 어택 UI
	for (int i = 0; i < 2; ++i)
	{
		clearAttackUI[i] = new CMatrix;
		clearAttackUI[i]->position.x = 50 + (64 * i);
		clearAttackUI[i]->position.y = 150;
		clearAttackUI[i]->scale = D3DXVECTOR2(0.4f, 0.4f);
	}

	// 타일 생성
	SetTile();

	// 적 생성
	SetEnemy();

	// 카메라 한계점 설정
	mainCamera->limitPos_Max.x = tileEntryInfo.size() * tileWidth - 1024;

	// 플레이어 소환
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

	// 클리어 어택 종료 업데이트
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
		// isStageClear가 true라면 플레이어 이동과 공격을 못하게 하고 
		// 클리어 메세지를 띄우고 2스테이지로 전환 & 클리어 메세지 깃발 잡을 때 띄움
		// 검은 창과 스코어 창 띄우고 엔터치면 넘어가게 함 검은창은 점점 거매지게
		if (stageClearUI->a >= 250)
		{
			stageClearUI->a = 255;
			// 스코어 집계 띄우기
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

		player->position.x += 250 * deltaTime; // clearTime 동안 자동으로 앞으로 이동하게 함

		// 클리어 하면 무적임
		invincible = true;

		clearTimer += deltaTime;
		if (clearTimer > clearTime)
		{
		}
		// 클리어 UI 업데이트
		stageClearUI->Update(deltaTime);
	}

	// 게임 재시작
	if (reStartGame)
	{
		// 스테이지에 따라 재시작이 다름
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

	// 승리
	if (isWin)
	{
		ChangeScene("Ending_Win");
		return;
	}

	// 패배
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
			// 플레이어가 있고 클리어가 아닐때
			if (player && !isStageClear)
				player->Jump();
			break;
		case VK_F1:
			// 클리어가 아닐때
			if(!isStageClear)
				invincible = !invincible;
			break;
		case VK_F2:
			// 플레이어 업그레이드 한계치를 넘지 않게 함
			if (player && player->upgrade < 2)
			{
				player->upgrade++;
				player->Reset();
			}
			break;
		case VK_F3:
			// 플레이어 업그래이드 한계치를 넘지 않게 함
			if (player && player->upgrade > 0)
			{
				player->upgrade--;
				player->Reset();
			}
			break;
		case VK_RETURN:
			// 컨티뉴 창에서 엔터치면 재시작
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
			// 플레이어 사망 치트키
			if (player)
				player->isDie = true;
			break;
		case 'S':
			// 버니합 치트키
			if (player)
				player->velocity_X = 3000;
			break;
		case 'C':
			// 클리어 어택
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
		// 스테이지 클리어 동작 중이 아닐때
		if (!isStageClear)
		{
			// 플레이어 이동
			if (GetKeyState(VK_LEFT) & 0x8000)
				player->Move(-1, deltaTime);
			if (GetKeyState(VK_RIGHT) & 0x8000)
				player->Move(1, deltaTime);
			// 플레이어 공격
			if (GetKeyState('X') & 0x8000)
				player->Attack();
			if (GetKeyState('Z') & 0x8000)
				player->OverAttack();
		}
		// 플레이어 타일 인덱스 받아아오기
		int tileIndex = player->position.x / tileWidth;
		// 타일 인덱스를 기반으로 체크포인트를 검사
		if (tileIndex >= 0 && tileIndex < tileEntryInfo.size())
			if (tileEntryInfo[tileIndex].checkPoint && tileIndex > checkPointIndex)
			{
				// 체크포인트 저장
				checkPointIndex = tileIndex;

				// 체크포인트 메세지 띄워주기
				getItemUI->currentScene = 8;
				getItemUI->a = 255;
			}
		// 플레이어 업데이트
		player->Update(deltaTime);

		// 무적일때 isDie는 무조건 false a 줄여줌
		if (invincible)
		{
			player->isDie = false;
			player->a = 150;
		}
		else
			player->a = 255;

		// 플레이어가 죽었다가 깨어나면 나오는게 뭔가 정신사납게나옴
		// 그래서 a 값을 0으로 만들어서 부활시키고 a 255까지 올려줌
		if (player->a != 255)
			player->a += deltaTime;
		else if (player->a > 255)
			player->a = 255;

		// 특수공격 카운트 관리
		if (clearAttackCount >= 3)
			clearAttackCount = 2;

		// 플레이어 사망
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
		// 부활
		if (rebirthTimer > rebirthTime)
		{
			rebirthTimer = 0;
			// 라이프 0과 같거나 0보다 클때만
			if (--playerLife >= 0)
			{
				// 체크포인트에서 부활
				D3DXVECTOR2 entryPos = tileList[checkPointIndex]->position;
				// 타일 포지션에서 부활하면 타일 센터가 없어서 왼쪽에서 부활함 128 늘려줌
				entryPos.x += 128;

				player = new CPlayer(entryPos, mainCamera);
				player->parentScene = this;
				mainCamera->SetTarget(player);
				player->a = 0;
			}
			else
				// 컨티뉴
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
		// 적 총알이랑 부딪치면 총알 삭제 플레이어 사망
		for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		{
			RECT ref;
			if (IntersectRect(&ref, &player->rect, &(*it)->rect))
			{
				player->isDie = true;
				(*it)->isDestoryed = true;
			}
		}
		// 오브젝트랑 부딪친 경우
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
					// 컨테이너 rect 꺼주기
					(*it)->isActive = false;
					// 아이템 UI 안보이게 해주기
					itemUI->currentScene = 0;
					// 업그레이드 메세지 띄워주기
					getItemUI->currentScene = 7;
					getItemUI->a = 255;
					break;
				case 777:
					// 클리어
					isStageClear = true;
					break;
				default:
					player->isDie = true;
					break;
				}
				// 오브젝트의 타입이 11 부터 19 사이일 경우 itemUI의 currentScene을 설정
				if ((*it)->type > 10 && (*it)->type < 20)
				{
					itemUI->currentScene = (*it)->type - 10;
					inputScale = 1;

					// 아이템 먹고 메세지 띄워주는것도 여기에다가 함
					getItemUI->currentScene = (*it)->type - 10;
					getItemUI->a = 255;
				}
				
				// 여기에 들어간건 안없어짐 2구멍 100컨테이너 777스테이지클리어
				if ((*it)->type != 2 && (*it)->type != 100 && (*it)->type != 777)
					(*it)->isDestroyed = true;
			}
		}
	}

	// playerBullet > enemy object
	for (auto it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		// 플레이어 총알에 에너미 맞으면 총알과 에너미 사망
		for (auto it2 = enemyList.begin(); it2 != enemyList.end(); ++it2)
		{
			RECT ref;
			if (IntersectRect(&ref, &(*it)->rect, &(*it2)->rect))
			{
				(*it)->isDestoryed = true;
				(*it2)->isDie = true;
			}
		}
		// 플레이어 총알에 오브젝트가 맞앗는데 1일경우만 둘다 사망
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
	// 이펙트
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
	// 입력받으면 새로 만들어줌
	clearAttack = new CMatrix();
	clearAttack->position = D3DXVECTOR2(player->position.x + 200, player->position.y);
	clearAttack->center = D3DXVECTOR2(64, 64);
	clearAttack->scale = D3DXVECTOR2(1.5f, 1.5f);
	clearAttack->SetAnimation(0.3f, 3, false);

	clearAttackCount--;
	isClearAttack = true;

	// 적, 적 총알 리스트 삭제
	for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
		if (*it)
			(*it)->isDie = true;

	for (auto it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		if (*it)
			(*it)->isDestoryed = true;
}

void CGameScene::UIUpdate(float deltaTime)
{
	// 점수 넣어주기
	int tempScore = score;
	for (int i = 5; i >= 0; --i)
	{
		scoreUI[i]->currentScene = tempScore % 10;
		tempScore /= 10;
	}

	// 점수, 특수공격, 라이프 띄우기
	for (int i = 0; i < 6; ++i)
	{
		scoreUI[i]->Update(deltaTime);
		if (i < 2)
			clearAttackUI[i]->Update(deltaTime);
		if (i < 3)
			playerLifeUI[i]->Update(deltaTime);
	}

	// 스테이지 UI
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

	// 컨티뉴
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

		// 플레이어가 있을때
		if (player)
		{
			// 스케일이 0이 아닐때만 줄임 자꾸 player reset 불러서 무한 점프함 & 점프랑 핵탄두는 안줄임
			if (inputScale != 0 && itemUI->currentScene != 2 && itemUI->currentScene != 6)
				inputScale -= (deltaTime / 5);
			// 0으로 만들어서 deltaTime 못하게 만듬
			if (inputScale < 0)
			{
				player->Reset();
				inputScale = 0;
			}
			// 0 될때까지 줄임
			itemUI->scale = D3DXVECTOR2(inputScale, inputScale);
		}
		else
			// 플레이어 죽으면 이상한거 뜨는데 없으면 0으로 만듬
			itemUI->currentScene = 0;
	}

	// 아이템 얻으면 메세지 창 띄워줌
	if (getItemUI)
	{
		// 알파값 점점 낮춰줌
		getItemUI->Update(deltaTime);

		if (getItemUI->a != 0)
			getItemUI->a -= 100 * deltaTime;
		else
			getItemUI->a = 0;
	}
}
