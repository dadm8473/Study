#pragma once

class CGameScene;
class CGameObject : public CMatrix
{
public:
	CCamera* camera;
	CGameScene* parentScene;

	int hp;
	float speed;

	bool isAttack;
	float attackTime;
	float attackTimer;

	bool isDie;
	bool isDestroy;
	RECT rect;

public:
	CGameObject(D3DXVECTOR2 pos, CCamera* inputCamera);
	~CGameObject();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void Attack();
};

