#pragma once

class CGameScene;
class CBossAttackSuppot : public CMatrix
{
public:
	CGameScene* parrentScene;

	int type;

	bool isDestroyed;

	float attackTime;
	float attackTimer;
	bool isAttack;
	float angle;

	float time_;
	float timer;

	int sum;

	RECT rect;

public:
	CBossAttackSuppot(D3DXVECTOR2 pos, int type, int _rotate = 0);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	int randomSum(int min, int max);
};