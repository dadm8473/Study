#pragma once

class CPlayer : public CGameObject
{
public:
	CPlayer(D3DXVECTOR2 pos, CCamera* inputCamera);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void Attack();
};
