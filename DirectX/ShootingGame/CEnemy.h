#pragma once

class CGameScene;
class CEnemy : public CGameObject
{
public:
	CGameScene* parentScene;

	int type;

public:
	CEnemy(D3DXVECTOR2 pos, int inputType, CCamera* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};

