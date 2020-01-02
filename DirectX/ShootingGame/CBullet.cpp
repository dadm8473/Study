#include "DXUT.h"
#include "Header.h"

CBullet::CBullet(D3DXVECTOR2 pos, int inputType, float inputMoveAngle, float inputSpeed, CCamera* inputCamera)
	: CGameObject(pos, inputCamera), type(inputType), moveAngle(inputMoveAngle)
{
	speed = inputSpeed;

	center = D3DXVECTOR2(1, 8);
	scale = D3DXVECTOR2(2, 2);

	d3dxPI = D3DX_PI / 180;
}

void CBullet::Update(float deltaTime)
{
	position.x += sin(moveAngle * d3dxPI) * speed * deltaTime;
	position.y -= cos(moveAngle * d3dxPI) * speed * deltaTime;

	rotate = moveAngle;

	if (position.y < camera->position.y - 128 || position.y > camera->position.y + 1024 + 128 ||
		position.x < camera->position.x - 128 || position.x > camera->position.x + 768 + 128)
		isDestroy = true;

	SetRect(&rect, position.x - 2, position.y - 12, position.x + 2, position.y + 12);
	CGameObject::Update(deltaTime);
}

void CBullet::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Bullet"));

	CGameObject::Render(sprite);
}
