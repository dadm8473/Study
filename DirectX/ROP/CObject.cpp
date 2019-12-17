#include "DXUT.h"
#include "Header.h"

CObject::CObject(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera)
	: camera(inputCamera), type(inputType), isDestroyed(false), isActive(true)
{
	position = pos;
	center = D3DXVECTOR2(64, 64);
	switch (type)
	{
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
		currentScene = type - 10;
		center = D3DXVECTOR2(64, 64);
		break;
	case 100:
		center = D3DXVECTOR2(64, 64);
		break;
	case 777:
		center = D3DXVECTOR2(128, 320);
		break;
	}
}

void CObject::Update(float deltaTime)
{
	switch (type)
	{
	case 1:
		SetRect(&rect, position.x - 40, position.y - 10, position.x + 40, position.y + 20);
		break;
	case 2:
		SetRect(&rect, position.x - 40, position.y - 10, position.x + 40, position.y + 20);
		break;
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
		Draw(sprite, gAssetManager->GetTexture("Hole"));
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
		Draw(sprite, gAssetManager->GetTexture("Item1"));
		break;
	case 100:
		Draw(sprite, gAssetManager->GetTexture("Container"));
		break;
	case 777:
		Draw(sprite, gAssetManager->GetTexture("Clear"));
		break;
	}
}
