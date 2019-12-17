#pragma once
class CGameScene;
class CEnemy : public CMatrix
{
public:
	CCamera* camera;
	CGameScene* parentScene;

	int hp;
	int type;

	float attackTimer;
	float attackTime;

	bool isDestroyed;
	bool isDie;

	RECT rect;

public:
	CEnemy(D3DXVECTOR2 pos, int inputType, CCamera* inputCamera);
	virtual void Updata(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
