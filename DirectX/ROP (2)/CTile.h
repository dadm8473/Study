#pragma once
class CTile : public CMatrix
{
public:
	CCamera* camera;
	int type;

public:
	CTile(D3DXVECTOR2 pos, int inputType, CCamera* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	float GetGround_Y_Pos(float xPos);
};

