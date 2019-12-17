#pragma once

class CMap : public CMatrix
{
private:
protected:
public:
	CMatrix land[2];
	CMatrix cloud1[2];
	CMatrix cloud2[2];

	int stage;

	CMap(int stage);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};