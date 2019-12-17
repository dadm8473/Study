#include "DXUT.h"
#include "Header.h"

CEffect::CEffect(D3DXVECTOR2 pos, CCamera * camera)
	: camera(camera), isDestroyed(false)
{
	position = pos;
	center = D3DXVECTOR2(64, 64);
	SetAnimation(0.1f, 3, false);
}

void CEffect::Update(float deltatime)
{
	if (isAniEnd)
		isDestroyed = true;

	CMatrix::Update(deltatime, camera->position);
}

void CEffect::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Effect"));
}
