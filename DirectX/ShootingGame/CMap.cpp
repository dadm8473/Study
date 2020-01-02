#include "DXUT.h"
#include "Header.h"

CMap::CMap(CCamera* inputCamera)
	: camera(inputCamera), speed(5)
{
	for (int i = 0; i < 2; ++i)
	{
		mapLayer[i] = CMatrix();
		mapLayer[i].position.x = camera->limitPos_Min.x;
		mapLayer[i].position.y = 1024 * i;
	}
}

void CMap::Update(float deltaTime)
{
	if (!camera)
		return;

	for (int i = 0; i < 2; ++i)
	{
		// Map Move
		mapLayer[i].position.y += speed + deltaTime;

		// Map Move Set
		if (mapLayer[i].position.y >= camera->position.y + 1024)
			mapLayer[i].position.y -= 1024 * 2;

		// Map Update
		mapLayer[i].Update(deltaTime, camera->position);
	}
}

void CMap::Render(LPD3DXSPRITE sprite)
{
	for (int i = 0; i < 2; ++i)
		mapLayer[i].Draw(sprite, gAssetManager->GetTexture("Map"));
}
