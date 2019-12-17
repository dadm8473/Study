#pragma once
class CEffect : public CMatrix
{
public:
	CCamera* camera;

	int type;

	bool isDestroyed;

public:
	CEffect(D3DXVECTOR2 pos, int inputType, CCamera* camera);
	virtual void Update(float deltatime);
	virtual void Render(LPD3DXSPRITE sprite);
};

