#include "DXUT.h"
#include "Header.h"

CBullet::CBullet(D3DXVECTOR2 pos, int type, float speed, float moveAngle, int damage, float bulletTime)
	:CMatrix(), type(type), speed(speed), moveAngle(moveAngle), damage(damage), isDestroyed(false), bulletTimer(0), bulletTime(0),
	timer(0), time(0.3f), angle(180), parentScene(NULL)
{
	position = pos;

	this->bulletTime = bulletTime;

	switch (type)
	{
	// Player Bullet
	case 1:
		center = D3DXVECTOR2(12, 12);
		break;
	// 편대비행 Enemy Bullet
	case 10:
		center = D3DXVECTOR2(12, 12);
		break;
	// 차징 Enemy Bullet
	case 20:
		break;
	case 100:
		center = D3DXVECTOR2(64, 64);
		scale = D3DXVECTOR2(1, 3);
		break;
	// 보스 총알
	case -1:
		center = D3DXVECTOR2(12, 24);
		scale = D3DXVECTOR2(1.5f, 1.5f);
		break;
	// 보스 총알
	case -2:
		center = D3DXVECTOR2(12, 24);
		scale = D3DXVECTOR2(1.5f, 1.5f);
		break;
	}
}

void CBullet::Update(float deltaTime)
{
	bulletTimer += deltaTime;
	if (bulletTime <= bulletTimer)
	{
		timer += deltaTime;
		if (timer >= time)
		{
			if (type == 1)
			{
				if (parentScene->boss)
				{
					angle = GetAngle(
						parentScene->boss->position.x - position.x,
						parentScene->boss->position.y - position.y);

					moveAngle = angle;
				}
			}
		}

		position.x += sin(moveAngle*(D3DX_PI / 180))*speed*deltaTime;
		position.y -= cos(moveAngle*(D3DX_PI / 180))*speed*deltaTime;

		rotate = moveAngle;

		if(type == -2)
			r = 100;
	}

	switch (type)
	{
		// Player Bullet
	case 1:
		// 일반 총알
		SetRect(&rect, position.x - 12, position.y - 24, position.x + 12, position.y + 12);
		break;
		// 편대비행 Enemy Bullet
	case 10:
		// 일반 총알
		SetRect(&rect, position.x - 12, position.y - 12, position.x + 12, position.y + 12);
		break;
	case 100:
		position.x += sin(moveAngle*(D3DX_PI / 180))*speed*deltaTime;
		position.y -= cos(moveAngle*(D3DX_PI / 180))*speed*deltaTime;
		SetRect(&rect, position.x - 32, position.y - 32, position.x + 32, position.y + 32);
		break;
	case -1:
		SetRect(&rect, position.x - 12, position.y - 12, position.x + 12, position.y + 12);
		break;
	case -2:
		SetRect(&rect, position.x - 12, position.y - 12, position.x + 12, position.y + 12);
		break;
	}

	if (position.x < -128 || position.x > 800 || position.y < -128 || position.y > 1100)
		isDestroyed = true;

	CMatrix::Update(deltaTime);
}

void CBullet::Render(LPD3DXSPRITE sprite)
{
	switch (type)
	{
	case 1:
	case 10:
		Draw(sprite, gAssetManager->GetTexture("playerBullet"));
		break;
	case 100:
		Draw(sprite, gAssetManager->GetTexture("meteor"));
		break;
	case -1:
		Draw(sprite, gAssetManager->GetTexture("bossBullet"));
		break;
	case -2:
		Draw(sprite, gAssetManager->GetTexture("bossBullet"));
		break;
	}
}