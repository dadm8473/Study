#pragma once
class CObject : public CMatrix
{
public:
	CCamera* camera;

	int type;
	int hp;

	bool isActive;

	bool isDestroyed;
	RECT rect;

public:
	CObject(D3DXVECTOR2 pos, int inputType, CCamera* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};

