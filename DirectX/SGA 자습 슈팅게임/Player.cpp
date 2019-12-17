#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos)
	:CMatrix(), attackTimer(0), attackTime(0), isAttack(false), isDie(false), 
	isInvincible(false), invincible(false), invincibleTime(0), invincibleTimer(0), angle(0), isMove(false),
	addon(NULL), specialTime(0.01f), specialTimer(0), isSpecial(false), count(0)
{
	position = pos;
	center = D3DXVECTOR2(64, 64);
	//SetCameraObject(gCamera);

	attackTime = 0.1f;
	isInvincible = true;
	invincibleTime = 1.5f;

	SetAnimation(0.03f, 21, true);
}

void CPlayer::Update(float deltaTime)
{
	CMatrix::Update(deltaTime);

	// Rect
	SetRect(&rect, position.x - 10, position.y - 10, position.x + 10, position.y + 10);


	// Player Attack
	attackTimer += deltaTime;
	if (isAttack)
	{
		if (attackTimer > attackTime)
		{
			attackTimer = 0;
			switch (attackPower)
			{
			case 0:
				parrentScene->playerBulletList.push_back(new CBullet(D3DXVECTOR2(position.x + 20, position.y), 1, 1024, 0, 10));
				parrentScene->playerBulletList.push_back(new CBullet(D3DXVECTOR2(position.x - 20, position.y), 1, 1024, 0, 10));
				break;
			case 1:
				for (int i = 0; i < 5; i++)
				{
					parrentScene->playerBulletList.push_back(new CBullet(position, 1, 1024, -10 + (i * 5), 10));
				}
				break;
			case 2:
				for (int i = 0; i < 7; i++)
				{
					parrentScene->playerBulletList.push_back(new CBullet(position, 1, 1024, -15 + (i * 5), 10));
				}
				break;
			case 3:
				for (int i = 0; i < 9; i++)
				{
					parrentScene->playerBulletList.push_back(new CBullet(position, 1, 1024, -20 + (i * 5), 10));
				}
				break;
			case 4:
				// 유도 추가하기
				for (int i = 0; i < 11; i++)
				{
					parrentScene->playerBulletList.push_back(new CBullet(position, 1, 1024, -25 + (i * 5), 10));
				}
				break;
			}
		}
		isAttack = false;
	}

	// 특수공격
	if (isSpecial)
	{
		// 큰 이펙트
		if (count == 0)
		{
			parrentScene->effectList.push_back(new CEffect(
				D3DXVECTOR2(384, 512),
				1, 0.02f, D3DXVECTOR2(5, 5)));
		}

		// 적을 다 clear
		parrentScene->enemyList.clear();
		parrentScene->enemyBulletList.clear();
		parrentScene->bossASList.clear();

		// 이펙트
		specialTimer += deltaTime;
		if (specialTime < specialTimer)
		{
			if (count >= 15)
			{
				specialTimer = 0;
				parrentScene->effectList.push_back(new CEffect(
					D3DXVECTOR2(getRandomNumber(0, 768), getRandomNumber(0, 1024)),
					1, 0.02f));
			}
			count++;
		}

		// 끝내기
		if (count >= 100)
		{
			isSpecial = false;
			count = 0;
			special--;
		}
	}

	// invincible
	if (isInvincible || invincible)
	{
		a = 100;

		//SetRect(&rect, position.x - 0, position.y - 0, position.x + 0, position.y + 0);

		invincibleTimer += deltaTime;
		if (invincibleTimer >= invincibleTime && !invincible)
		{
			invincibleTimer = 0;
			SetRect(&rect, position.x - 10, position.y - 10, position.x + 10, position.y + 10);
			isInvincible = false;
		}
	}
	else
		a = 255;

}

void CPlayer::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("player"));
}

void CPlayer::Attack()
{
	isAttack = true;
	if (addon)
		addon->Attack();
}

void CPlayer::SpecialAttack()
{
	if (special > 0)
	{
		isSpecial = true;
	}
}