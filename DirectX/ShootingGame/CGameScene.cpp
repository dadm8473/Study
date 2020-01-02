#include "DXUT.h"
#include "Header.h"

CGameScene::CGameScene()
	: CScene(), playerBulletList(),
	enemyEntryInfo(), enemyList(), enemyEntryTimer(0)
{
	mainCamera = new CCamera();		// Camera Create
	map = new CMap(mainCamera);				// Map Create

	player = new CPlayer(D3DXVECTOR2(384, 700), mainCamera);	// Player Create
	player->parentScene = this;

	mainCamera->SetTarget(player);	// Camera Set

	enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(10, -64), 0, 0));
	enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(50, -64), 1, 0));
	enemyEntryInfo.push_back(EnemyEntryInfo(D3DXVECTOR2(90, -64), 2, 0));
}

CGameScene::~CGameScene()
{
	// Player Delete
	if (player)
		delete player;

	// Player Bullet List delete
	for (auto it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		if (*it)
			delete (*it);
	playerBulletList.clear();

	// Enemy List delete
	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
		if (*it)
			delete(*it);

	// Camera Delete
	delete mainCamera;
	delete map;
}

void CGameScene::Update(float deltaTime)
{
	// Map Update
	map->Update(deltaTime);

	// Player Update
	player->Update(deltaTime);

	// Bullet Update
	BulletUpdate(deltaTime);

	// Enemy Update
	EnemyUpdate(deltaTime);

	// Rect Update
	RectUpdate(deltaTime);

	// Camera Update
	mainCamera->Update(deltaTime);

	// CScene Update
	CScene::Update(deltaTime);
}

void CGameScene::Render(LPD3DXSPRITE sprite)
{
	// Map Render
	map->Render(sprite);

	// Player Bullet Render
	for (auto it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
		(*it)->Render(sprite);

	// Enemy List Render
	for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
		(*it)->Render(sprite);

	// Player Render;
	player->Render(sprite);

	// CScene Render;
	CScene::Render(sprite);
}

void CGameScene::MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	CScene::MsgProc(uMsg, wParam, lParam);
}

void CGameScene::BulletUpdate(float deltaTime)
{
	// player Bullet List Update
	for (auto it = playerBulletList.begin(); it != playerBulletList.end();)
	{
		(*it)->Update(deltaTime);

		if ((*it)->isDestroy)
		{
			delete (*it);
			it = playerBulletList.erase(it);
		}
		else
			++it;
	}
}

void CGameScene::EnemyUpdate(float deltaTime)
{
	// EnemyEntryTimer Update
	enemyEntryTimer += deltaTime;

	// EnemyEntryInfo Update
	for (int i = 0; i < enemyEntryInfo.size(); i++)
	{
		if (!enemyEntryInfo[i].summoned)
		{
			if (enemyEntryTimer >= enemyEntryInfo[i].time)
			{
				CEnemy* enemy = new CEnemy(enemyEntryInfo[i].position, enemyEntryInfo[i].type, mainCamera);
				enemy->parentScene = this;

				enemyList.push_back(enemy);
				enemyEntryInfo[i].summoned = true;
			}
		}
	}
	
	// Enemy Update
	for (list<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end();)
	{
		(*it)->Update(deltaTime);

		// Enemy Hp
		if ((*it)->hp <= 0)
			(*it)->isDie = true;

		// Enemy Die & Destroy
		if ((*it)->isDie)
		{

		}
		if ((*it)->isDestroy || (*it)->isDie)
		{
			delete(*it);
			it = enemyList.erase(it);
		}
		else
			++it;
	}
}

void CGameScene::RectUpdate(float deltaTime)
{
	// player <- enemy
	if (player)
	{
		// enemy
		for (auto it = enemyList.begin(); it != enemyList.end(); ++it)
		{
			RECT ref;

			if (IntersectRect(&ref, &player->rect, &(*it)->rect))
			{
				player->isDie = true;
				(*it)->isDie = true;
			}
		}
	}

	// playerBullet -> enemy
	for (auto it = playerBulletList.begin(); it != playerBulletList.end(); ++it)
	{
		// enemy
		for (auto it2 = enemyList.begin(); it2 != enemyList.end(); ++it2)
		{
			RECT ref;

			if (IntersectRect(&ref, &(*it2)->rect, &(*it)->rect))
			{
				(*it2)->hp--;
				(*it)->isDestroy = true;
			}
		}
	}
}