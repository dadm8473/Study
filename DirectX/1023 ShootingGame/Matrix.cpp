#include "DXUT.h"
#include "Header.h"

CMatrix gCamera;

CMatrix::CMatrix()
{
	camera = NULL;

	zValue = 1;

	position = D3DXVECTOR2(0, 0);
	scale = D3DXVECTOR2(1, 1);
	center = D3DXVECTOR2(0, 0);
	rotate = 0;

	a = r = g = b = 255;

	animation = false;

	aniTime = 0;
	aniTimer = 0;
	currentScene = 0;
	maxScene = 0;
	repeatAni = false;
	isAniEnd = false;
}

void CMatrix::Update(float deltaTime)
{
	D3DXVECTOR2 pos = position;
	pos -= center;

	D3DXMatrixIdentity(&matrix);

	if (camera)
	{
		pos.x -= (camera->position.x - camera->center.x) / zValue; // X
		pos.y -= (camera->position.y - camera->center.y) / zValue; // Y
	}

	D3DXMatrixTransformation2D(&matrix, &center, 0, &scale, &center, D3DXToRadian(rotate), &pos);

	if (animation && !isAniEnd)
	{
		aniTimer += deltaTime;
		if (aniTimer >= aniTime)
		{
			currentScene++;
			if (currentScene >= maxScene)
			{
				if (repeatAni)
					currentScene = 0;
				else
				{
					currentScene--;
					isAniEnd = true;
				}
			}
			aniTimer = 0;
		}
	}
}

void CMatrix::Draw(LPD3DXSPRITE sprite, CTexture* texture, RECT* drawRect)
{
	sprite->SetTransform(&matrix);
	sprite->Draw(texture->GetTexture(currentScene), drawRect,
		NULL, NULL, D3DCOLOR_ARGB(a, r, g, b));
}

void CMatrix::SetAnimation(float rate, int maxScene, bool repeat)
{
	animation = true;

	aniTime = rate;
	aniTimer = 0;
	currentScene = 0;
	this->maxScene = maxScene;
	repeatAni = repeat;
	isAniEnd = false;
}

void CMatrix::Play()
{
	aniTimer = 0;
	currentScene = 0;
	isAniEnd = false;
}

void CMatrix::Stop()
{
	animation = false;
}