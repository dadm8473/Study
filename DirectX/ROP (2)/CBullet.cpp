#include "DXUT.h"
#include "Header.h"

CBullet::CBullet(CCamera * camera, D3DXVECTOR2 pos, int type, float moveAngle, float speed, float timer)
	: camera(camera), type(type), moveAngle(moveAngle), timer(timer), speed(speed), isDestoryed(false)
{
	position = pos;
	center = D3DXVECTOR2(32, 64);
	scale = D3DXVECTOR2(0.7f, 0.7f);
	
	switch (type)
	{
		// 대공
	case 0:
		break;
		// 일반
	case 1:
		SetAnimation(0.02f, 20, true);
		break;
		// 적
	case 2:
		SetAnimation(0.02f, 20, true);
		break;
	}
}

void CBullet::Update(float deltaTime)
{
	position.x += sin(moveAngle * (D3DX_PI / 180)) * speed * deltaTime;
	position.y -= cos(moveAngle * (D3DX_PI / 180)) * speed * deltaTime;
	rotate = moveAngle;

	timer -= deltaTime;
	if (timer <= 0)
		isDestoryed = true;

	SetRect(&rect, position.x - 32, position.y - 32, position.x + 32, position.y + 32);
	CMatrix::Update(deltaTime, camera->position);
}

void CBullet::Render(LPD3DXSPRITE sprite)
{
	switch (type)
	{
	case 0:
		Draw(sprite, gAssetManager->GetTexture("Bullet_Sky"));
		break;
	case 1:
		Draw(sprite, gAssetManager->GetTexture("Bullet_Player"));
		break;
	case 2:
		Draw(sprite, gAssetManager->GetTexture("Bullet_Enemy"));
		break;
	}
}
