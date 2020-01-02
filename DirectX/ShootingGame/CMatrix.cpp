#include "DXUT.h"
#include "Header.h"

CMatrix::CMatrix()
	: position(0, 0), scale(1, 1), center(0, 0), rotate(0),
	currentScene(0), maxScene(0), animation(false), aniTime(0), aniTimer(0),
	isAniEnd(false), repeatAni(false), camera(NULL)
{
	a = r = g = b = 255;

	D3DXMatrixIdentity(&matrix);
}

void CMatrix::Update(float deltaTime, D3DXVECTOR2 camera)
{
	D3DXVECTOR2 pos = position - center - camera;

	D3DXMatrixTransformation2D(&matrix, &center, 0, &scale, &center, D3DXToRadian(rotate), &pos);

	if (animation && !isAniEnd)
	{
		aniTimer += deltaTime;
		if (aniTimer >= aniTime)
		{
			if (++currentScene >= maxScene)
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
