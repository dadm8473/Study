#pragma once

class EnemyEntryInfo
{
public:
	int type;
	float time;
	D3DXVECTOR2 position;

	bool summoned;

	EnemyEntryInfo(D3DXVECTOR2 position, float time, int type)
		:position(position), time(time), type(type), summoned(false)
	{

	}
};

class CGameScene : public CScene
{
public:
	CCamera* mainCamera;
	CMap* map;

public:
	// Player
	CPlayer* player;

public:
	// Enemy
	vector<EnemyEntryInfo> enemyEntryInfo;
	list<CEnemy*> enemyList;
	float enemyEntryTimer;

public:
	// Bullet
	list<CBullet*> playerBulletList;

public:
	CGameScene();
	~CGameScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	void BulletUpdate(float deltaTime);
	void EnemyUpdate(float deltaTime);
	void RectUpdate(float deltaTime);
};

