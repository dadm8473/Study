#include "DXUT.h"
#include "Header.h"

CObject::CObject(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera)
	: camera(inputCamera), type(inputType), isDestroyed(false), isActive(true), hp(1)
{
	position = pos;
	center = D3DXVECTOR2(64, 64);
	switch (type)
	{
	case 1:
		center = D3DXVECTOR2(128, 180);
		currentScene = stage - 1;
		hp = 5;
		switch (currentScene)
		{
		case 0:
			center = D3DXVECTOR2(128, 180);
			scale = D3DXVECTOR2(1, 0.8f);
			break;
		case 1:
			center = D3DXVECTOR2(128, 190);
			scale = D3DXVECTOR2(1, 0.8f);
			break;
		}
		break;
	case 2:
		break;
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
		SetAnimation(0.05f, 10, true);
		center = D3DXVECTOR2(64, 128);
		break;
	case 100:
		center = D3DXVECTOR2(128, 226);
		scale = D3DXVECTOR2(1, 1.3f);
		break;
	case 777:
		currentScene = stage - 1;
		switch (currentScene)
		{
		case 0:
			center = D3DXVECTOR2(128, 105);
			break;
		case 1:
			center = D3DXVECTOR2(128, 256);
			break;
		}
		break;
	}
}

void CObject::Update(float deltaTime)
{
	switch (type)
	{
	case 1:
		SetRect(&rect, position.x - 40, position.y - 50, position.x + 40, position.y + 20);
		break;
	case 2:
		SetRect(&rect, position.x - 128, position.y, position.x + 128, position.y + 999);
		break;
	case 100:
		SetRect(&rect, position.x - 88, position.y - 128, position.x + 128, position.y + 128);
	default:
		if (isActive)
			SetRect(&rect, position.x - 64, position.y - 64, position.x + 64, position.y + 64);
		else
			SetRect(&rect, 0, 0, 0, 0);
		break;
	}

	if (type == 777)
		SetRect(&rect, position.x - 128, position.y - 384, position.x + 128, position.y + 128);

	CMatrix::Update(deltaTime, camera->position);
}

void CObject::Render(LPD3DXSPRITE sprite)
{
	switch (type)
	{
	case 1:
		Draw(sprite, gAssetManager->GetTexture("Object"));
		break;
	case 2:
		//Draw(sprite, gAssetManager->GetTexture("Hole"));
		break;
	case 11:
		Draw(sprite, gAssetManager->GetTexture("Item1"));
		break;
	case 12:
		Draw(sprite, gAssetManager->GetTexture("Item2"));
		break;
	case 13:
		Draw(sprite, gAssetManager->GetTexture("Item3"));
		break;
	case 14:
		Draw(sprite, gAssetManager->GetTexture("Item4"));
		break;
	case 15:
		Draw(sprite, gAssetManager->GetTexture("Item5"));
		break;
	case 16:
		Draw(sprite, gAssetManager->GetTexture("Item6"));
		break;
	case 100:
		Draw(sprite, gAssetManager->GetTexture("Container"));
		break;
	case 777:
		Draw(sprite, gAssetManager->GetTexture("TileEnd"));
		break;
	}
}
