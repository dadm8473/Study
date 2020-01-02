#pragma once
class CMatrix
{
public:
	CMatrix* camera;

	D3DXMATRIX matrix;
	D3DXVECTOR2 position;
	D3DXVECTOR2 center;
	D3DXVECTOR2 scale;
	float rotate;

	int a, r, g, b;

	bool animation;

	float aniTime, aniTimer;
	int currentScene, maxScene;

	bool repeatAni, isAniEnd;

public:
	CMatrix();
	virtual void Update(float deltaTime, D3DXVECTOR2 camera = D3DXVECTOR2(0,0));
	void Draw(LPD3DXSPRITE sprite, CTexture* texture, RECT* drawRect = NULL);

	virtual void SetAnimation(float rate, int maxScene, bool repeat);
};

