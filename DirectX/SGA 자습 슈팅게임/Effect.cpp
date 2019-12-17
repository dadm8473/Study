#include "DXUT.h"
#include "Header.h"

CEffect::CEffect(D3DXVECTOR2 pos, int type, float aniSpeed, D3DXVECTOR2 scale_)
	: CMatrix(), type(type), mustDestroy(false)
{
	position = pos;

	CTexture* texture = gAssetManager->GetTexture("effect");
	SetAnimation(aniSpeed, 21, false);

	center.x = texture->imageInfo.Width / 2.f;
	center.y = texture->imageInfo.Height / 2.f;
	scale = scale_;
}

void CEffect::Update(float deltaTime)
{
	CMatrix::Update(deltaTime);

	if (isAniEnd)
	{
		mustDestroy = true;
	}
}

void CEffect::Render(LPD3DXSPRITE sprite)
{
	CTexture* texture = gAssetManager->GetTexture("effect");
	Draw(sprite, texture);
}