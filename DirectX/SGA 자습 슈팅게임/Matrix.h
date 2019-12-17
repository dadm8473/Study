#pragma once

class CMatrix
{
public:
	CMatrix* camera;
	float zValue;

	D3DXMATRIX matrix;
	D3DXVECTOR2 position;
	D3DXVECTOR2 center;
	D3DXVECTOR2 scale;
	float rotate;

	int a, r, g, b;

	bool animation;

	float aniTime;
	float aniTimer;

	int currentScene;
	int maxScene;

	bool repeatAni;
	bool isAniEnd;

public:
	CMatrix();
	virtual void Update(float deltaTime);
	void Draw(LPD3DXSPRITE sprite, CTexture* texture, RECT* drawRect = NULL);

	virtual void SetAnimation(float rate, int maxScene, bool repeat);

	void Play();
	void Stop();

	CMatrix* GetCameraObject()
	{
		return this->camera;
	}
	void SetCameraObject(CMatrix* camera)
	{
		this->camera = camera;
	}
};

extern CMatrix* gCamera;