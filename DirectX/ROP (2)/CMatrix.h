#pragma once
class CMatrix
{
public:
	D3DXMATRIX matrix;
	D3DXVECTOR2 position;
	D3DXVECTOR2 center;
	D3DXVECTOR2 scale;
	float rotate;

	int a, r, g, b;

	bool animation;

	float aniTime, aniTimer;
	int currentScene, maxScene;
	bool isAniEnd, repeatAni;

public:
	CMatrix();
	virtual void Update(float deltaTime, D3DXVECTOR2 camera = D3DXVECTOR2(0, 0));
	void Draw(LPD3DXSPRITE sprite, CTexture* texture);
	virtual void SetAnimation(float rate, int maxScene, bool repeat);
};

