#pragma once

class CEffect : public CMatrix
{
public:
	bool mustDestroy;
	int type;

	CEffect(D3DXVECTOR2 pos, int type, float aniSpeed, D3DXVECTOR2 scale_ = D3DXVECTOR2(1,1));

	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);

};