#include "DXUT.h"
#include "Header.h"

CItem::CItem(D3DXVECTOR2 pos, int type)
	: isDestroyed(false), speed(256), angle(180)
{
	position = pos;
	this->type = type;
	center = D3DXVECTOR2(64, 64);
	scale = D3DXVECTOR2(0.5f, 0.5f);
}

void CItem::Update(float deltaTime)
{
	CMatrix::Update(deltaTime);

	SetRect(&rect, position.x - 64, position.y - 64, position.x + 64, position.y + 64);

	if (parentScene->player)
	{
		angle = GetAngle(
			parentScene->player->position.x - position.x,
			parentScene->player->position.y - position.y);
		speed = 512;
	}
	else
	{
		angle = getRandomNumber(0, 360);
		if (speed > 0)
			speed -= 200 * deltaTime;
		else
			speed = 0;
	}

	position.x += sin(angle*(D3DX_PI / 180)) * speed * deltaTime;
	position.y -= cos(angle*(D3DX_PI / 180)) * speed * deltaTime;

	switch (type)
	{
	case 1:
		// 점수 주는 아이템
		if (isDestroyed)
		{
			score += getRandomNumber(100, 500);
		}
		break;
	case 2:
		// 플레이어 파워 증가시키는 아이템
		if (isDestroyed)
		{
			if (attackPower < 4)
				attackPower++;
			else
			{
				if (power > 3)
					return;
				power++;
				if (parentScene->player)
					parentScene->addonList.push_back(new CAddon(parentScene->player->position, power));
			}
		}
		break;
	case 3:
		// 특수 공격 채워주는 아이템
		special++;
		if (special > 3)
			special = 3;
		break;
	}

	if (position.x < -128 || position.x > 800 || position.y < -128 || position.y > 1100)
		isDestroyed = true;
}

void CItem::Render(LPD3DXSPRITE sprite)
{
	switch (type)
	{
	case 1:
		// 점수 주는 아이템
		Draw(sprite, gAssetManager->GetTexture("scoreItem"));
		break;
	case 2:
		// 플레이어 파워 증가시키는 아이템
		Draw(sprite, gAssetManager->GetTexture("powerItem"));
		break;
	case 3:
		// 특수 공격 채워주는 아이템
		Draw(sprite, gAssetManager->GetTexture("specialItem"));
		break;
	default:
		Draw(sprite, gAssetManager->GetTexture("player"));
		break;
	}
}
