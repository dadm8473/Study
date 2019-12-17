#pragma once

class CGameScene;
class CBullet : public CMatrix
{
public:
	CGameScene* parentScene;
	int type;
	int damage;

	float bulletTimer;
	float bulletTime;
	float timer;
	float time;
	float angle;

	float speed;
	float _speed;
	float temp;
	float moveAngle;

	bool isDestroyed;

	RECT rect;

public:
	CBullet(D3DXVECTOR2 pos, int type, float speed, float moveAngle, int damage, float bulletTime = 0);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};