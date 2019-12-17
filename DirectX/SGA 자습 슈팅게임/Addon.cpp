#include "DXUT.h"
#include "Header.h"

CAddon::CAddon(D3DXVECTOR2 playerPos, int number)
	:CMatrix(), attackTimer(0), attackTime(0.1f), isAttack(false), angle(0), angle_(0), isDestroyed(false), isMove(true),
	target(NULL)
{
	position = playerPos;
	center = D3DXVECTOR2(32, 32);
	//scale = D3DXVECTOR2(2, 2);
	this->number = number;

	SetAnimation(0.01f, 40, true);
}

void CAddon::Update(float deltaTime)
{
	CMatrix::Update(deltaTime);
	
	attackTimer += deltaTime;
	if (isAttack)
	{
		if (attackTimer > attackTime)
		{
			attackTimer = 0;
			if (target)
				angle_ = GetAngle(
					target->position.x - position.x,
					target->position.y - position.y);

			else if (parrentScene->boss)
				angle_ = GetAngle(
					parrentScene->boss->position.x - position.x,
					parrentScene->boss->position.y - position.y);
			else
				angle_ = 0;

			parrentScene->playerBulletList.push_back(new CBullet(position, 1, 1024, angle_, 10));
		}

		isAttack = false;
	}

	if (parrentScene->player)
	{
		isMove = true;

		if (a != 255)
			a += 200 * deltaTime;
		else
			a = 255;

		
		switch (number)
		{
		case 1:
			angle = GetAngle(
				parrentScene->player->position.x - 128 - position.x,
				parrentScene->player->position.y + 128 - position.y);
			break;
		case 2:
			angle = GetAngle(
				parrentScene->player->position.x + 128 - position.x,
				parrentScene->player->position.y + 128 - position.y);
			break;
		case 3:
			angle = GetAngle(
				parrentScene->player->position.x - 256 - position.x,
				parrentScene->player->position.y + 128 - position.y);
			break;
		case 4:
			angle = GetAngle(
				parrentScene->player->position.x + 256 - position.x,
				parrentScene->player->position.y + 128 - position.y);
			break;
		default:
			return;
			break;
		}

		if (parrentScene->player->isMove)
		{
			position.x += sin(angle*(D3DX_PI / 180)) * getRandomNumber(200, 300) * deltaTime;
			position.y -= cos(angle*(D3DX_PI / 180)) * getRandomNumber(200, 300) * deltaTime;
		}
	}
	else
	{
		if (a <= 0)
			a = 0;
		else
			a -= 200 * deltaTime;
	}
}

void CAddon::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Addon"));
}

void CAddon::Attack()
{
	isAttack = true;
}