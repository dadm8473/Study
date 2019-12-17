#pragma once

class CGameScene;
class CEnemy : public CMatrix
{
public:
	CGameScene* parrentScene;
	CEnemy * centerPick;

	int type;
	/*
	Type 1 - 대각선 편대비행 (오른쪽)
	Type 2 - 대각선 편대비행 (왼쪽)
	Type 10 - 차징
	Type 11 - 차징 샷
	Type 20 - 유도 n-way
	Type 30 - 돌진
	Type 40 -
	Type 90 - 보물상자
	Type 100 - 유성
	*/
	 
	bool isDestroyed;

	float attackTime;
	float attackTimer;
	bool isAttack;
	float angle;

	float exitTime;
	float exitTimer;
	bool exit;

	int count;
	float timer;
	int moveDir_X;
	int moveDir_Y;
	
	int hp;
	bool isDie;
	float speed;

	RECT rect;

	bool beHit;
	float hitRedTime;
	float hitRedTimer;

public:
	CEnemy(D3DXVECTOR2 pos, int type, int _rotate = 0);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};