#pragma once
class CBullet : public CMatrix
{
public:
	CCamera* camera;

	int type;
	
	float moveAngle;
	float timer;
	float speed;

	bool isDestoryed;
	RECT rect;

public:
	CBullet(CCamera* camera, D3DXVECTOR2 pos, int type, float moveAngle, float speed, float timer = 0.5f);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};

