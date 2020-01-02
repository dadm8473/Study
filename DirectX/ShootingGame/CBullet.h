#pragma once
class CBullet : public CGameObject
{
public:
	int type;
	float moveAngle;
	float d3dxPI;

public:
	CBullet(D3DXVECTOR2 pos, int inputType, float inputMoveAngle, float inputSpeed, CCamera* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};
