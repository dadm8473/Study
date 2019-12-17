#pragma once

class CGameScene;
class CPlayer : public CMatrix
{
public:
	CCamera* camera;
	CGameScene* parentScene;
	CMatrix* target;

	float velocity_Y;
	float velocity_X;
	float ground_Y_Pos;

	int jumpCount;

	int upgrade;

public:
	bool isAttack;
	bool isOverAttack;
	float attackTimer;
	float attackTime;

	float speed;
	float rich;
	bool isMultiAttack;
	bool isHomingAttack;
	bool doubleJump;

public:
	bool isDie;
	RECT rect;

public:
	CPlayer(D3DXVECTOR2 pos, CCamera* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	void SetTarget(CMatrix* inputTarget) { target = inputTarget; }

public:
	void Move(int dir, float deltaTime);
	void Jump();
	void Attack();
	void OverAttack();

public:
	void DoubleJump();
	void SpeedUP();
	void LongAttack();
	void MultiAttack();
	void HomingAttack();
	void Reset();
};

