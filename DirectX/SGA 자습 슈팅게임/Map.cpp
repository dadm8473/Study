#include "DXUT.h"
#include "Header.h"

CMap::CMap(int stage) : stage(stage)
{
	for (int i = 0; i < 2; i++)
	{
		land[i] = CMatrix();
		land[i].position.y = 1536 * i;

		cloud1[i] = CMatrix();
		cloud1[i].position.y = 1536 * i;

		cloud2[i] = CMatrix();
		cloud2[i].position.y = 1536 * i;
	}
}

void CMap::Update(float deltaTime)
{
	for (int i = 0; i < 2; i++)
	{
		land[i].position.y += 128 * deltaTime;

		if (land[i].position.y >= 1536)
			land[i].position.y -= 1536 * 2;

		cloud1[i].position.y += 383 * deltaTime;

		cloud2[i].position.y += 256 * deltaTime;

		if (cloud1[i].position.y >= 1536)
			cloud1[i].position.y -= 1536 * 2;

		if (cloud2[i].position.y >= 1536)
			cloud2[i].position.y -= 1536 * 2;

		land[i].Update(deltaTime);
		cloud1[i].Update(deltaTime);
		cloud2[i].Update(deltaTime);
	}
}

void CMap::Render(LPD3DXSPRITE sprite)
{
	for (int i = 0; i < 2; i++)
		land[i].Draw(sprite, gAssetManager->GetTexture("land"));
	for (int i = 0; i < 2; i++)
		cloud1[i].Draw(sprite, gAssetManager->GetTexture("cloud_1"));
	for (int i = 0; i < 2; i++)
		cloud2[i].Draw(sprite, gAssetManager->GetTexture("cloud_2"));
}