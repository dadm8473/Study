#pragma once

class TileEntryInfo
{
public:
	int type;
	int objectType;
	bool checkPoint;

	TileEntryInfo(int type, int objectType = -1, bool checkPoint = false)
		: type(type), checkPoint(checkPoint), objectType(objectType)
	{

	}
};

class EnemyEntryInfo
{
public:
	int type;
	float timer;

	EnemyEntryInfo(int type, float timer)
		: type(type), timer(timer)
	{

	}
};

class CGameScene : public CScene
{
public:
	// 카메라 맵
	CCamera* mainCamera;
	CMap* map;

	CMatrix miniMapBar;
	CMatrix playerIcon;
	CMatrix checkPointIcon;

public:
	// 타일 배치 관련
	vector<TileEntryInfo> tileEntryInfo;
	int currentTileIndex;
	vector<CTile*> tileList;

public:
	// 총알 관련
	list<CBullet*> enemyBulletList;
	list<CBullet*> playerBulletList;

public:
	// 이펙트
	list<CEffect*> effectList;

public:
	list<CObject*> objectList;

public:
	// 적 소환 관련
	vector<EnemyEntryInfo> enemyEntryInfo;
	int currentEnemyIndex;
	list<CEnemy*> enemyList;
	float enemyEntryTimer;

public:
	bool isHole;
	float holeTimer;
	float holeTime;

public:
	CMatrix* conEffect;
	bool isConEffect;
	
public:
	// 플레이어
	CPlayer* player;
	int playerLife;

	// 플레이어 부활
	float rebirthTimer;
	float rebirthTime;
	int checkPointIndex;

	// 승리, 패배, 무적
	bool isWin;
	bool isLose;
	bool invincible;

	// 스테이지 클리어
	bool isStageClear;
	float clearTimer;
	float clearTime;

public:
	// 특수 공격
	CMatrix* clearAttack;
	CMatrix* clearAttack_White;
	int clearAttackCount;
	bool isClearAttack;

public:
	// UI
	CMatrix* ui;
	CMatrix* scoreUI[6];
	CMatrix* playerLifeUI[3];
	CMatrix* clearAttackUI[2];
	// 스테이지 넘어갈 때 창 띄우기
	CMatrix* stageUI;
	// 스테이지 클리어 창 띄우기
	CMatrix* stageClearUI;
	CMatrix* scoreUI_clear[6];

	// 아이템 적용중인거 보여주는 UI
	CMatrix* itemUI;
	float inputScale;
	CMatrix* getItemUI;
	
	// 컨티뉴 ctn 라고 썻음
	CMatrix* ctnUI;
	bool isCtn;
	bool reStartGame; // 엔터치면 스테이지에서 다시시작하게 도와줌

public:
	CGameScene(int stage);
	~CGameScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	void SetTile();
	void SetEnemy();

public:
	void TileUpdate(float deltaTime);
	void PlayerUpdate(float deltaTime);
	void EnemyUpdate(float deltaTime);
	void BulletUpdate(float deltaTime);
	void ObjectUpdate(float deltaTime);

public:
	void RectUpdate(float deltaTime);
	void EffectUpdate(float deltaTime);
	void ClearAttack();
	void UIUpdate(float deltaTime);
};