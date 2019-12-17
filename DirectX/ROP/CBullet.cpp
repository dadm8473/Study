#include "DXUT.h"
#include "Header.h"

CBullet::CBullet(CCamera * camera, D3DXVECTOR2 pos, int type, float moveAngle, float speed, float timer)
	: camera(camera), type(type), moveAngle(moveAngle), timer(timer), speed(speed), isDestoryed(false)
{
	position = pos;
	center = D3DXVECTOR2(32, 64);
}

void CBullet::Update(float deltaTime)
{
	position.x += sin(moveAngle * (D3DX_PI / 180)) * speed * deltaTime;
	position.y -= cos(moveAngle * (D3DX_PI / 180)) * speed * deltaTime;
	rotate = moveAngle;

	timer -= deltaTime;
	if (timer <= 0)
		isDestoryed = true;

	SetRect(&rect, position.x - 64, position.y - 64, position.x + 64, position.y + 64);
	CMatrix::Update(deltaTime, camera->position);
}

void CBullet::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Bullet"));
}
