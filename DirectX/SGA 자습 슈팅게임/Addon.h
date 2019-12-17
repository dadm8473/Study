#pragma once

class CGameScene;
class CAddon : public CMatrix
{
public:
	CGameScene* parrentScene;
	CEnemy* target;

	void SetEnemyPos(CEnemy* enemy) { target = enemy; }

	float attackTimer;
	float attackTime;
	bool isAttack;
	bool isDestroyed;

	bool isMove;

	int angle;
	int angle_;
	int number;

	void Attack();
public:
	CAddon(D3DXVECTOR2 playerPos, int number);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};

