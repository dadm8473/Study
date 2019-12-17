#pragma once

class CGameScene;
class CEnemy : public CMatrix
{
public:
	CGameScene* parrentScene;
	CEnemy * centerPick;

	int type;
	/*
	Type 1 - �밢�� ������ (������)
	Type 2 - �밢�� ������ (����)
	Type 10 - ��¡
	Type 11 - ��¡ ��
	Type 20 - ���� n-way
	Type 30 - ����
	Type 40 -
	Type 90 - ��������
	Type 100 - ����
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