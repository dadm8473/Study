#include "DXUT.h"
#include "Header.h"

CMap::CMap(int stage) : stage(stage), CMatrix()
{
	for (int i = 0; i < 2; i++)
	{
		land[i] = CMatrix();
		land[i].position.x -= 64;
		land[i].position.y = 1792 * i;
		land[i].SetCameraObject(&gCamera);

		cloud1[i] = CMatrix();
		cloud1[i].position.x -= 64;
		cloud1[i].position.y = 1792 * i;
		cloud1[i].SetCameraObject(&gCamera);

		cloud2[i] = CMatrix();
		cloud2[i].position.x -= 64;
		cloud2[i].position.y = 1792 * i;
		cloud2[i].SetCameraObject(&gCamera);
		cloud2[i].a = 100;
	}
}

void CMap::Update(float deltaTime)
{
	for (int i = 0; i < 2; i++)
	{
		land[i].position.y += 128 * deltaTime;

		if (land[i].position.y >= 1792)
			land[i].position.y -= 1792 * 2;

		cloud1[i].position.y += 383 * deltaTime;

		cloud2[i].position.y += 256 * deltaTime;

		if (cloud1[i].position.y >= 1792)
			cloud1[i].position.y -= 1792 * 2;

		if (cloud2[i].position.y >= 1792)
			cloud2[i].position.y -= 1792 * 2;

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