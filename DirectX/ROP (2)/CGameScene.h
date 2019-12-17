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
	// ī�޶� ��
	CCamera* mainCamera;
	CMap* map;

	CMatrix miniMapBar;
	CMatrix playerIcon;
	CMatrix checkPointIcon;

public:
	// Ÿ�� ��ġ ����
	vector<TileEntryInfo> tileEntryInfo;
	int currentTileIndex;
	vector<CTile*> tileList;

public:
	// �Ѿ� ����
	list<CBullet*> enemyBulletList;
	list<CBullet*> playerBulletList;

public:
	// ����Ʈ
	list<CEffect*> effectList;

public:
	list<CObject*> objectList;

public:
	// �� ��ȯ ����
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
	// �÷��̾�
	CPlayer* player;
	int playerLife;

	// �÷��̾� ��Ȱ
	float rebirthTimer;
	float rebirthTime;
	int checkPointIndex;

	// �¸�, �й�, ����
	bool isWin;
	bool isLose;
	bool invincible;

	// �������� Ŭ����
	bool isStageClear;
	float clearTimer;
	float clearTime;

public:
	// Ư�� ����
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
	// �������� �Ѿ �� â ����
	CMatrix* stageUI;
	// �������� Ŭ���� â ����
	CMatrix* stageClearUI;
	CMatrix* scoreUI_clear[6];

	// ������ �������ΰ� �����ִ� UI
	CMatrix* itemUI;
	float inputScale;
	CMatrix* getItemUI;
	
	// ��Ƽ�� ctn ��� ����
	CMatrix* ctnUI;
	bool isCtn;
	bool reStartGame; // ����ġ�� ������������ �ٽý����ϰ� ������

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