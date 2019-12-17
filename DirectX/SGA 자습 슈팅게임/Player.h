#pragma once

class CGameScene;
class CPlayer : public CMatrix
{
public:
	CGameScene* parrentScene;
	CAddon* addon;

	float attackTimer;
	float attackTime;
	bool isAttack;

	float specialTimer;
	float specialTime;
	bool isSpecial;
	int count;

	int angle;

	bool isMove;
	bool isDie;
	RECT rect;

	bool isInvincible;
	bool invincible;
	float invincibleTimer;
	float invincibleTime;

	void Attack();
	void SpecialAttack();

public:
	CPlayer(D3DXVECTOR2 pos);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};