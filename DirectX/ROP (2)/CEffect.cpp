#include "DXUT.h"
#include "Header.h"

CEffect::CEffect(D3DXVECTOR2 pos, int inputType, CCamera * camera)
	: camera(camera), isDestroyed(false), type(inputType)
{
	position = pos;
	center = D3DXVECTOR2(64, 64);

	switch (type)
	{
	case 1: // Bullet
		SetAnimation(0.04f, 20, false);
		gAssetManager->GetSoundAsset("Effect")->Play();
		scale = D3DXVECTOR2(0.5f, 0.5f);
		break;
	case 2: // enemy
		SetAnimation(0.04f, 20, false);
		scale = D3DXVECTOR2(2, 2);
		break;
	case 3: // player
		center = D3DXVECTOR2(128, 128);
		SetAnimation(0.04f, 20, false);
		gAssetManager->GetSoundAsset("Effect")->Play();
		break;
	case 4: // Clear
		center = D3DXVECTOR2(256, 384);
		SetAnimation(0.04f, 20, false);
		break;
	default:
		SetAnimation(0.1f, 3, false);
		break;
	}
}

void CEffect::Update(float deltatime)
{
	if (isAniEnd)
		isDestroyed = true;

	CMatrix::Update(deltatime, camera->position);
}

void CEffect::Render(LPD3DXSPRITE sprite)
{
	switch (type)
	{
	case 1: // Bullet
		Draw(sprite, gAssetManager->GetTexture("Effect_Bullet"));
		break;
	case 2: // enemy
		Draw(sprite, gAssetManager->GetTexture("Effect_Enemy"));
		break;
	case 3: // player
		Draw(sprite, gAssetManager->GetTexture("Effect_Player"));
		break;
	case 4: // Clear
		Draw(sprite, gAssetManager->GetTexture("Effect_Clear"));
		break;
	default:
		Draw(sprite, gAssetManager->GetTexture("Effect"));
		break;
	}
}
