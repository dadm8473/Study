#pragma once
class CMap
{
public:
	CCamera* camera;

	CMatrix mapLayer[2];

	float speed;

public:
	CMap(CCamera* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};

