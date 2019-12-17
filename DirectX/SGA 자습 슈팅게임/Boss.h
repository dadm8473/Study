#pragma once

class CBoss : public CMatrix
{
public:
	CGameScene* parrentScene;

	int hp;
	int maxHp;
	int speed;
	int type;
	RECT rect;
	bool isDie;

	bool isEnter;

	float patternTime;
	float patternTimer;
	bool isPatternOn;
	int patternNum;
	int sum;
	int sum_1;

	float attackTimer;
	float attackTime;
	int maxBullet;
	int bulletCount;
	int bulletSpeed;

	int moveDir;
	float pAngle;
	int x, y;

public:
	CBoss(int _type = 1);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	void switchPattern();
	void StageOneSideBoss();
	void StageOneBoss();
	void StageTwoSideBoss(float deltaTime);
	void StageTwoBoss(float deltaTime);
	int randomSum(int min, int max);
};