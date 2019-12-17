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
	vector<EnemyEntryInfo> enemyEntryInfo;

public:
	list<CBullet*>playerBulletList;
	list<CBullet*>enemyBulletList;

	list<CEffect*> effectList;

	list<CEnemy*>enemyList;
	list<CItem*>itemList;
	list<CBossAttackSuppot*> bossASList;
	list<CAddon*> addonList;

public:
	CBoss* boss;

public:
	CMatrix bossHpValue;
	CMatrix bossHpBG;
	RECT bossHpRect;

	CMatrix scoreNumUI[6];
	CMatrix playerLifeUI[5];
	CMatrix clearAttackUI[10];

public:
	CPlayer * player;
	int playerLife;
	float rebirthTimer;
	float rebirthTime;

public:
	int stage;
	CMap* map;
	float timer;
	float isMoveTimer;
	float tempTimer;
	int count;

	bool isWin;

public:
	bool isShakingCamera;
	float shakeTime;
	int shakeAmount;
	D3DXVECTOR2 shakePosition;

public:
	CGameScene(int stage);
	virtual ~CGameScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	void classicUpdate(float detlaTime);
	void ClassicRect();
	void EnemySpawn();
	void TimeLine(int num);
};