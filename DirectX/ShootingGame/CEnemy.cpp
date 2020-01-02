#include "DXUT.h"
#include "Header.h"

CEnemy::CEnemy(D3DXVECTOR2 pos, int inputType, CCamera* inputCamera)
	: CGameObject(pos, inputCamera), type(inputType), parentScene(NULL)
{
	center = D3DXVECTOR2(64, 64);

	speed = 300;
	b = 0;
}

void CEnemy::Update(float deltaTime)
{
	position.y += speed * deltaTime;

	if (position.y < camera->position.y - 128 || position.y > camera->position.y + 1024 + 128)
		isDestroy = true;

	SetRect(&rect, position.x - 32, position.y - 32, position.x + 32, position.y + 32);
	CGameObject::Update(deltaTime);
}

void CEnemy::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Player"));
	CGameObject::Render(sprite);
}
