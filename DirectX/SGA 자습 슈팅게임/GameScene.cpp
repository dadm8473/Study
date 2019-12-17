#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene(int stage)
	:CScene(), enemyEntryInfo(), playerBulletList(), enemyBulletList(), enemyList(), effectList(), itemList(), bossASList(), boss(NULL),
	addonList(), player(new CPlayer(D3DXVECTOR2(0, 0))), rebirthTime(2), rebirthTimer(0), stage(stage), map(new CMap(stage)), timer(0), 
	isMoveTimer(0), tempTimer(0), count(0)
{
	gCamera->position = D3DXVECTOR2(0, 0);

	player = new CPlayer(D3DXVECTOR2(384, 700));
	player->parrentScene = this;

	map->center = D3DXVECTOR2(512, 384);
	//map->SetCameraObject(gCamera);

	// 스코어 초기화
	for (int i = 0; i < 6; i++)
	{
		scoreNumUI[i] = CMatrix();
		scoreNumUI[i].position.x = 500 + (40 * i);
		scoreNumUI[i].position.y = 950;

		scoreNumUI[i].scale.x = 0.7f;
		scoreNumUI[i].scale.y = 0.7f;
	}

	// 플레이어 생명 초기화
	for (int i = 0; i < 5; i++)
	{
		playerLifeUI[i] = CMatrix();
		playerLifeUI[i].position.x = 32 + (40 * i);
		playerLifeUI[i].position.y = 900;

		playerLifeUI[i].scale.x = 0.25f;
		playerLifeUI[i].scale.y = 0.25f;
	}

	// 특수공격 초기화
	for (int i = 0; i < 10; i++)
	{
		clearAttackUI[i] = CMatrix();
		clearAttackUI[i].position.x = 32 + (50 * i);
		clearAttackUI[i].position.y = 930;

		clearAttackUI[i].scale.x = 0.7f;
	}

	// 보스 체력바 초기화
	bossHpBG = CMatrix();
	bossHpBG.center = D3DXVECTOR2(256, 64);
	bossHpBG.position = D3DXVECTOR2(384, 32);
	bossHpBG.a = 190;

	bossHpValue = CMatrix();
	bossHpValue.center = D3DXVECTOR2(256, 64);
	bossHpValue.position = D3DXVECTOR2(390, 32);
	bossHpValue.a = 190;

	// 타임라인
	TimeLine(stage);
}

CGameScene::~CGameScene()
{
	// Player Bullet delete
	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		if (*it)
			delete (*it);
	playerBulletList.clear();
	// Enemy Bullet delete
	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		if (*it)
			delete (*it);
	enemyBulletList.clear();
	// Player delete
	if (player)
		delete player;
	// map
	if (map)
		delete map;
	// Enemy List
	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
		if (*it)
			delete(*it);
	enemyList.clear();
	// Boss Attack Suppot
	for (list<CBossAttackSuppot*>::iterator it = bossASList.begin(); it != bossASList.end(); ++it)
		if (*it)
			delete(*it);
	bossASList.clear();
	// Addon List
	for (list<CAddon*>::iterator it = addonList.begin(); it != addonList.end(); ++it)
		if (*it)
			delete(*it);
	addonList.clear();
	// item
	for (list<CItem*>::iterator it = itemList.begin(); it != itemList.end(); ++it)
		if (*it)
			delete(*it);
	itemList.clear();
	// Effect
	for (list<CEffect*>::iterator it = effectList.begin(); it != effectList.end(); ++it)
		if (*it)
			delete (*it);
	effectList.clear();
	// Boss
	if (boss)
		delete boss;
}

void CGameScene::Update(float deltaTime)
{
	CScene::Update(deltaTime);

	// map Update
	map->Update(deltaTime);

	if (!boss)
		// timer Update
		timer += deltaTime;
	else
	{
		timer = 0;
		// 보스 체력바
		float ratio = (float)boss->hp / boss->maxHp;
		SetRect(&bossHpRect, 0, 0, 524 * ratio, 64);
		bossHpBG.Update(deltaTime);
		bossHpValue.Update(deltaTime);
	}

	// 점수 설정
	int tempScore = score;
	for (int i = 5; i >= 0; i--)
	{
		scoreNumUI[i].currentScene = tempScore % 10;
		tempScore /= 10;
	}
	// 점수 업데이트
	for (int i = 0; i < 6; i++)
	{
		scoreNumUI[i].Update(deltaTime);
	}
	// 플레이어 생명 업데이트
	for (int i = 0; i < 5; i++)
	{
		playerLifeUI[i].Update(deltaTime);
	}
	// 특수 공격 업데이트
	for (int i = 0; i < 3; i++)
	{
		clearAttackUI[i].Update(deltaTime);
	}

	// EnemyEntryInfo Update
	EnemySpawn();

	// classic Update
	classicUpdate(deltaTime);

	// classic Rect
	ClassicRect();

	// Player Update
	if (player)
	{
		isMoveTimer += deltaTime;
		if (isMoveTimer >= 0.1f)
		{
			player->isMove = false;
		}

		// Player Move
		if (GetKeyState(VK_LEFT) & 0x8000)
			player->position.x -= 300 * deltaTime;
		if (GetKeyState(VK_RIGHT) & 0x8000)
			player->position.x += 300 * deltaTime;
		if (GetKeyState(VK_UP) & 0x8000)
			player->position.y -= 300 * deltaTime;
		if (GetKeyState(VK_DOWN) & 0x8000)
			player->position.y += 300 * deltaTime;

		if (GetKeyState(VK_LEFT) & 0x8000 || GetKeyState(VK_RIGHT) & 0x8000 || (GetKeyState(VK_UP) & 0x8000) || (GetKeyState(VK_DOWN) & 0x8000))
		{
			player->isMove = true;
			isMoveTimer = 0;
		}

		if (GetKeyState('X') & 0x8000)
		{
			player->Attack();
			for (list<CAddon*>::iterator it = addonList.begin(); it != addonList.end(); ++it)
				(*it)->Attack();
		}
		else if (boss)
			mainTime = 0.7f;
		
		if (GetKeyState('C') & 0x8000)
		{
			player->SpecialAttack();
		}

		player->Update(deltaTime);
		//gCamera->position.x = player->position.x;

		if (player->isDie)
		{
			// 사망 이펙트
			for (int i = 0; i < attackPower; ++i)
			{
				itemList.push_back(new CItem(player->position + D3DXVECTOR2(getRandomNumber(-100, 100), getRandomNumber(-100, 100)), 2));
			}

			// 애드온 있으면 꺼주기
			player = NULL;
		}
	}
	else
	{
		// 플레이어 부활
		rebirthTimer += deltaTime;
		if (rebirthTimer >= rebirthTime)
		{
			rebirthTimer = 0;
			// 플레이어 라이프가 적다면
			if (--playerLife >= 0)
			{
				player = new CPlayer(D3DXVECTOR2(384, 700));
				player->parrentScene = this;
			}
			else
			{
				// 게임 패배
				ChangeScene(3);
				return;
			}
		}
	}
}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
	// map Render
	if (map)
		map->Render(sprite);
	// Player Bullet Render
	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		(*it)->Render(sprite);
	// Player Render
	if (player)
		player->Render(sprite);
	// Enemy Bullet Render
	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end(); ++it)
		(*it)->Render(sprite);
	// Enemy Render
	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
		(*it)->Render(sprite);
	// BossAS Render
	for (list<CBossAttackSuppot*>::iterator it = bossASList.begin(); it != bossASList.end(); ++it)
		(*it)->Render(sprite);
	// Addon Render
	for (list<CAddon*>::iterator it = addonList.begin(); it != addonList.end(); ++it)
		(*it)->Render(sprite);
	// item Render
	for (list<CItem*>::iterator it = itemList.begin(); it != itemList.end(); ++it)
		(*it)->Render(sprite);
	// Boss Render
	if (boss)
		boss->Render(sprite);
	// Effect Render
	for (list<CEffect*>::iterator it = effectList.begin(); it != effectList.end(); ++it)
		(*it)->Render(sprite);
	// 점수
	for (int i = 0; i < 6; i++)
	{
		scoreNumUI[i].Draw(sprite, gAssetManager->GetTexture("number"));
	}
	// 플레이어 생명
	for (int i = 0; i < 5; i++)
	{
		if (playerLife > i)
			playerLifeUI[i].Draw(sprite, gAssetManager->GetTexture("player"));
	}
	// 특수공격
	for (int i = 0; i < 5; i++)
	{
		if (special > i)
			clearAttackUI[i].Draw(sprite, gAssetManager->GetTexture("player"));
	}
	// 보스 체력바
	if (boss)
	{
		bossHpValue.Draw(sprite, gAssetManager->GetTexture("bossHpValue"), &bossHpRect);
		bossHpBG.Draw(sprite, gAssetManager->GetTexture("bossHpBar"));
	}
}

void CGameScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CScene::MsgProc(uMsg, wParam, lParam);

	switch (uMsg)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		// Cheat
		case VK_F1:
			// invincible
			if (player)
				player->invincible = !player->invincible;
			break;
		case VK_F2:
			itemList.push_back(new CItem(D3DXVECTOR2(384, 200), 2));
			break;
		case VK_SHIFT:
			mainTime = 5;
			break;
		case VK_F5:
			if(player)
				addonList.push_back(new CAddon(player->position, 1));
			break;
		case VK_F6:
			if (player)
				addonList.push_back(new CAddon(player->position, 2));
			break;
		case VK_F7:
			if (player)
				addonList.push_back(new CAddon(player->position, 3));
			break;
		case VK_F8:
			if (player)
				addonList.push_back(new CAddon(player->position, 4));
			break;
		}
		break;
	case WM_KEYUP:
		switch (wParam)
		{
		case VK_SHIFT:
			mainTime = 1;
			break;
		}
	}
}

void CGameScene::classicUpdate(float deltaTime)
{
	// Player Bullet Update
	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end();)
	{
		(*it)->parentScene = this;
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed)
		{
			delete (*it);
			it = playerBulletList.erase(it);
		}
		else
			++it;
	}

	// Enemy Bullet Update
	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList.end();)
	{
		(*it)->parentScene = this;
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed)
		{
			delete (*it);
			it = enemyBulletList.erase(it);
		}
		else
			++it;
	}

	// Enemy Update
	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end();)
	{
		(*it)->parrentScene = this;
		(*it)->Update(deltaTime);

		if ((*it)->isDie || (*it)->isDestroyed)
		{
			if ((*it)->isDestroyed)
			{
				delete(*it);
				it = enemyList.erase(it);
				return;
			}

			// 이펙트
			effectList.push_back(new CEffect((*it)->position, 1, 0.02f));

			// 아이템 특공템은 안나옴 나중에 추가하셈
			if ((*it)->type == 90)
				itemList.push_back(new CItem((*it)->position, 2));
			else if((*it)->type != 11)
				itemList.push_back(new CItem((*it)->position, 1));

			delete(*it);
			it = enemyList.erase(it);
		}
		else
			++it;
	}

	// Boss SA Update
	for (list<CBossAttackSuppot*>::iterator it = bossASList.begin(); it != bossASList.end();)
	{
		(*it)->parrentScene = this;
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed)
		{
			delete(*it);
			it = bossASList.erase(it);
		}
		else
			++it;
	}

	// Addon Update
	for (list<CAddon*>::iterator it = addonList.begin(); it != addonList.end();)
	{
		(*it)->parrentScene = this;
		(*it)->Update(deltaTime);

		if ((*it)->isDestroyed)
		{
			delete(*it);
			it = addonList.erase(it);
		}
		else
			++it;
	}

	// item Update
	for (list<CItem*>::iterator it = itemList.begin(); it != itemList.end();)
	{
		(*it)->parentScene = this;
		(*it)->Update(deltaTime);
		
		if ((*it)->isDestroyed)
		{
			delete(*it);
			it = itemList.erase(it);
		}
		else
			++it;
	}

	// Boss Update
	if (boss)
	{
		boss->Update(deltaTime);

		if (boss->isDie)
		{
			// 사망 이펙트 콰코아쾈와ㅗㅋ아ㅏㅋㅇ
					// 점수 아이템 랜덤 스폰 샤샤샤샥

			// 이펙트
			tempTimer += deltaTime;
			if (0.05f < tempTimer)
			{
				tempTimer = 0;
				effectList.push_back(new CEffect(
					D3DXVECTOR2(boss->position.x + getRandomNumber(-256, 256), boss->position.y + getRandomNumber(-256, 256)),
					1, 0.02f));
				itemList.push_back(new CItem(
					D3DXVECTOR2(boss->position.x + getRandomNumber(-256, 256), boss->position.y + getRandomNumber(-256, 256)
					), 1));
				count++;
			}

			switch (boss->type)
			{
			case 1:
				// 첫 스테이지 2페이즈 시작하기
				// 두번재 보스 등장 애니메이션

				enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 1, -2));

				break;
			case 2:
				// 2스테이지로 넘어가기
				tempTimer += deltaTime;
				if (tempTimer >= 3)
				{
					tempTimer = 0;
					ChangeScene(12);
				}
				break;
			case 3:
				// 둘째 스테이지 2페이즈 시작하기
				// 두번재 보스 등장 애니메이션

				enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 1, -4));
				break;
			case 4:
				// 승리
				tempTimer += deltaTime;
				if (tempTimer >= 3)
				{
					tempTimer = 0;
					ChangeScene(2);
				}
				break;
			}

			// 끝내기
			if (count >= 50)
			{
				// 보스 없애깅
				delete boss;
				boss = NULL;
				count = 0;
			}
		}
	}

	// Effect Update
	for (list<CEffect*>::iterator it = effectList.begin(); it != effectList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isAniEnd)
		{
			delete(*it);
			it = effectList.erase(it);
		}
		else
			++it;
	}
}

void CGameScene::ClassicRect()
{
	// Rect Cheack
	// enemy <- playerBullet
	for (list<CBullet*>::iterator it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		// Boss
		if (boss)
		{
			RECT ref;
			if (IntersectRect(&ref, &(*it)->rect, &boss->rect))
			{
				// player bullet delete
				(*it)->isDestroyed = true;

				// 보스가 맞을 때 마다 이펙트
				effectList.push_back(new CEffect((*it)->position, 1, 0.02f, D3DXVECTOR2(0.3f, 0.3f)));

				// 보스 데미지 입음
				boss->hp--;
				if (boss->hp <= 0)
				{
					boss->hp = 0;
					boss->isDie = true;
				}
			}
		}

		// Enemy
		for (list<CEnemy*>::iterator it2 = enemyList.begin(); it2 != enemyList.end(); ++it2)
		{
			RECT ref;
			if (IntersectRect(&ref, &(*it)->rect, &(*it2)->rect))
			{
				// player bullet delete
				(*it)->isDestroyed = true;

				// behit
				if (!(*it2)->beHit && (*it2)->type != 11)
				{
					(*it2)->beHit = true;
					(*it2)->hitRedTimer = 0;
				}

				// 적 데미지 입음
				(*it2)->hp--;

				if ((*it2)->hp <= 0)
				{
					(*it2)->isDie = true;
				}
			}
		}
	}

	// Item
	for (list<CItem*>::iterator it = itemList.begin(); it != itemList.end(); ++it)
	{
		if (player)
		{
			RECT ref;

			if (IntersectRect(&ref, &player->rect, &(*it)->rect))
			{
				// 아이템 효과 적용
				(*it)->isDestroyed = true;
			}
		}
	}
	

	// player <- enemyBullet
	for (list<CBullet*>::iterator it = enemyBulletList.begin(); it != enemyBulletList
		.end(); ++it)
	{
		if (player)
		{
			RECT ref;
			if (IntersectRect(&ref, &player->rect, &(*it)->rect) && (!player->invincible && !player->isInvincible))
			{
				effectList.push_back(new CEffect((*it)->position, 1, 0.02f));
				player->isDie = true;
				(*it)->isDestroyed = true;
			}
		}
	}

	// player <- enemy
	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
	{
		if (player)
		{
			RECT ref;
			if (IntersectRect(&ref, &player->rect, &(*it)->rect) && (!player->isInvincible && !player->invincible))
			{
				effectList.push_back(new CEffect((*it)->position, 1, 0.02f));
				// 보물 상자 맞아 뒤지진 않게
				if((*it)->type != 90)
					player->isDie = true;
				(*it)->isDie = true;
			}
		}
	}

	// player <- BossAS
	for (list<CBossAttackSuppot*>::iterator it = bossASList.begin(); it != bossASList.end(); ++it)
	{
		if (player)
		{
			RECT ref;
			if (IntersectRect(&ref, &player->rect, &(*it)->rect) && (!player->isInvincible && !player->invincible))
			{
				player->isDie = true;
				(*it)->isDestroyed = true;
			}
		}
	}
}

void CGameScene::EnemySpawn()
{
	// EnemyEntryInfo Update
	for (int i = 0; i < enemyEntryInfo.size(); i++)
	{
		if (!enemyEntryInfo[i].summoned)
		{
			if (timer >= enemyEntryInfo[i].time)
			{
				switch (enemyEntryInfo[i].type)
				{
					// 1 Stage Side Boss
				case -1:
					boss = new CBoss(1);
					boss->parrentScene = this;

					enemyEntryInfo[i].summoned = true;
					break;
					// 1 Stage Boss
				case -2:
					boss = new CBoss(2);
					boss->parrentScene = this;

					enemyEntryInfo[i].summoned = true;
					break;
					// 2 Stage Side Boss
				case -3:
					boss = new CBoss(3);
					boss->parrentScene = this;

					enemyEntryInfo[i].summoned = true;
					break;
					// 2 Stage Boss
				case -4:
					boss = new CBoss(4);
					boss->parrentScene = this;

					enemyEntryInfo[i].summoned = true;
					break;
					// Enemy Spawn
				default:
					CEnemy* enemy = new CEnemy(enemyEntryInfo[i].position, enemyEntryInfo[i].type);

					enemyList.push_back(enemy);
					enemyEntryInfo[i].summoned = true;
					break;
				}
			}
		}
	}
}

void CGameScene::TimeLine(int num)
{
	switch (num)
	{
	case 1:
	{
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(0, 0), 3, 0));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(768, 0), 3, 1));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(0, 0), 5, 0));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(0, 0), 6, 0));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(768, 0), 8, 1));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(768, 0), 9, 1));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 11, 10));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 12, 90));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(768, 0), 14, 1));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(0, 0), 14, 0));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 17, 20));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(128, 0), 23, 30));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(256, 0), 23.5f, 30));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(512, 0), 24, 30));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(640, 0), 24.5f, 30));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 25, 90));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(640, 0), 28, 30));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(512, 0), 28.5f, 30));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(256, 0), 29, 30));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(128, 0), 29.5f, 30));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(0, 0), 32, 0));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(768, 0), 32, 1));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(0, 0), 33, 0));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(768, 0), 33, 1));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(0, 0), 34, 0));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(0, 0), 35, 0));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(0, 0), 34.5f, 0));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(0, 0), 35.5f, 0));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(768, 0), 37, 1));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(768, 0), 38, 1));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(768, 0), 37.5f, 1));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(768, 0), 38.5f, 1));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(512, 0), 40, 10));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(256, 0), 40, 10));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 41, 90));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(768, 0), 43, 1));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(0, 0), 43, 0));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 46, 20));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(128, 0), 52, 30));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(256, 0), 52.5f, 30));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(512, 0), 53, 30));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(640, 0), 53.5f, 30));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 54, 90));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(640, 0), 57, 30));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(512, 0), 57.5f, 30));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(256, 0), 58, 30));
		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(128, 0), 58.5f, 30));

		enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(128, 0), 63, -1));
		}
		break;
	case 2:
	{
		{
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 3, 10));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(0, 0), 4, 0));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(0, 0), 5, 0));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(768, 0), 4, 1));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(768, 0), 5, 1));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 6, 10));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(128, 0), 7, 100));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(640, 0), 7, 100));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 7, 90));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(128, 0), 11, 20));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(640, 0), 11, 20));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(128, 0), 16, 30));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(256, 0), 16.5f, 30));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(512, 0), 17, 30));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(640, 0), 17.5f, 30));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 18, 100));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(640, 0), 21, 30));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(512, 0), 21.5f, 30));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(256, 0), 22, 30));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(128, 0), 22.5f, 30));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 23, 100));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 24, 90));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(0, 0), 26, 0));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(0, 0), 27, 0));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(640, 0), 26, 10));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(768, 0), 28, 1));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(768, 0), 29, 1));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(128, 0), 28, 10));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 31, 10));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(0, 0), 32, 0));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(0, 0), 33, 0));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(768, 0), 32, 1));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(768, 0), 33, 1));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 34, 10));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(128, 0), 35, 100));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(640, 0), 35, 100));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 35, 90));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(128, 0), 39, 20));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(640, 0), 39, 20));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(128, 0), 44, 30));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(256, 0), 44.5f, 30));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(512, 0), 45, 30));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(640, 0), 45.5f, 30));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 46, 100));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(640, 0), 49, 30));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(512, 0), 49.5f, 30));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(256, 0), 50, 30));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(128, 0), 50.5f, 30));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 51, 100));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(384, 0), 52, 90));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(0, 0), 54, 0));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(0, 0), 55, 0));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(640, 0), 54, 10));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(768, 0), 56, 1));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(768, 0), 57, 1));
			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(128, 0), 56, 10));

			enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(128, 0), 59, -3));
		}
	}
		break;
	}
}
