#include "DXUT.h"
#include "Header.h"

CEnemy::CEnemy(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera)
	: camera(inputCamera), type(inputType), isDestroyed(false), isDie(false), hp(3),
	attackTime(1.5f), attackTimer(1)
{
	position = pos;

	center = D3DXVECTOR2(128, 64);
	scale = D3DXVECTOR2(-1, 1);

	switch (type)
	{
	case 1:
		SetAnimation(0.03f, 20, true);
		break;
	case 2:
		SetAnimation(0.03f, 20, true);
		break;
	case 3:
		SetAnimation(0.03f, 20, true);
		break;
	case 4:
		SetAnimation(0.03f, 20, true);
		break;
	default:
		break;
	}
}

void CEnemy::Updata(float deltaTime)
{
	position.x -= 400 * deltaTime;

	switch (type % 2)
	{
	case 0:
		attackTimer += deltaTime;
		if (attackTime < attackTimer)
		{
			attackTimer = 0;
			attackTime = 1.5f + rand() % 1;
			parentScene->enemyBulletList.push_back(new CBullet(camera, position, 2, 180, 400 + rand() % 200, 0.7f));
		}
		break;
	case 1:
		attackTimer += deltaTime;
		if (attackTime < attackTimer)
		{
			attackTimer = 0;
			attackTime = 1.5f + rand() % 1;
			parentScene->enemyBulletList.push_back(new CBullet(camera, position, 2, -170, 400 + rand() % 200, 0.75f));
		}
		break;
	}

	if (position.x < camera->position.x - 256 || position.x > camera->position.x + 1024 + 256)
		isDestroyed = true;

	SetRect(&rect, position.x - 64, position.y - 64, position.x + 64, position.y + 64);
	CMatrix::Update(deltaTime, camera->position);
}

void CEnemy::Render(LPD3DXSPRITE sprite)
{
	switch (type)
	{
	case 1:
		Draw(sprite, gAssetManager->GetTexture("Enemy1"));
		break;
	case 2:
		Draw(sprite, gAssetManager->GetTexture("Enemy1"));
		break;
	case 3:
		Draw(sprite, gAssetManager->GetTexture("Enemy2"));
		break;
	case 4:
		Draw(sprite, gAssetManager->GetTexture("Enemy3"));
		break;
	default:
		Draw(sprite, gAssetManager->GetTexture("Player"));
		break;
	}
}
