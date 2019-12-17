#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos, CCamera * inputCamera)
	: camera(inputCamera), velocity_Y(0), ground_Y_Pos(0), jumpCount(0), isDie(false), 
	isAttack(false), isOverAttack(false), attackTime(0.4f), attackTimer(0),
	speed(600), rich(0.3f), isMultiAttack(false), isHomingAttack(false), target(NULL),
	upgrade(0), doubleJump(false), velocity_X(0)
{
	position = pos;
	center = D3DXVECTOR2(64, 64);

	ground_Y_Pos = pos.y;
}

void CPlayer::Update(float deltaTime)
{
	velocity_Y += 32 * deltaTime;
	position.y += velocity_Y;
	position.x += velocity_X * deltaTime;

	if (parentScene)
	{
		int tileIndex = position.x / tileWidth;
		if (tileIndex >= 0 && tileIndex < parentScene->tileList.size())
		{
			float outY = parentScene->tileList[tileIndex]->GetGround_Y_Pos(position.x);
			if (outY != 0)
				ground_Y_Pos = outY;
		}
	}

	if (isAttack)
	{
		attackTimer += deltaTime;
		if (attackTimer > attackTime)
		{
			parentScene->playerBulletList.push_back(new CBullet(camera, position, 0, 90, 1000, rich));

			if (isHomingAttack && target)
			{
				float angle = GetAngle(target->position.x - position.x, target->position.y - position.y);

				if(angle > - 20)
					parentScene->playerBulletList.push_back(new CBullet(camera, position, 0, angle, 1000, 5));

				target = NULL;
			}

			attackTimer = 0;
			isAttack = false;
		}
	}

	if (isOverAttack)
	{
		attackTimer += deltaTime;
		if (attackTimer > attackTime)
		{
			parentScene->playerBulletList.push_back(new CBullet(camera, position, 0, 70, 1000, rich));

			if (isMultiAttack)
			{
				parentScene->playerBulletList.push_back(new CBullet(camera, position, 0, 80, 1000, rich));
				parentScene->playerBulletList.push_back(new CBullet(camera, position, 0, 60, 1000, rich));
			}

			attackTimer = 0;
			isOverAttack = false;
		}
	}

	if (position.y > ground_Y_Pos)
	{
		position.y = ground_Y_Pos;
		velocity_Y = 0;
		velocity_X = 0;

		if (!doubleJump)
			jumpCount = 1;
		else
			jumpCount = 2;
	}

	SetRect(&rect, position.x - 64, position.y - 64, position.x + 64, position.y + 64);
	CMatrix::Update(deltaTime, camera->position);
}

void CPlayer::Render(LPD3DXSPRITE sprite)
{
	switch (upgrade)
	{
	case 0:
		Draw(sprite, gAssetManager->GetTexture("Player"));
		break;
	case 1:
		Draw(sprite, gAssetManager->GetTexture("Player1"));
		break;
	case 2:
		Draw(sprite, gAssetManager->GetTexture("Player2"));
		break;
	}
}

void CPlayer::Move(int dir, float deltaTime)
{
	position.x += dir * speed * deltaTime;
}

void CPlayer::Jump()
{
	if (--jumpCount >= 0)
	{
		velocity_Y = -12;
		velocity_X = 50;
	}
}

void CPlayer::Attack()
{
	isAttack = true;

	isOverAttack = false;
}

void CPlayer::OverAttack()
{
	isOverAttack = true;

	isAttack = false;
}

void CPlayer::DoubleJump()
{
	if(upgrade != 2)
		doubleJump = true;
}

void CPlayer::SpeedUP()
{
	speed += 35;
	if (speed > 600)
		speed = 600;
}

void CPlayer::LongAttack()
{
	rich = 2;
}

void CPlayer::MultiAttack()
{
	isMultiAttack = true;
}

void CPlayer::HomingAttack()
{
	isHomingAttack = true;
}

void CPlayer::Reset()
{
	doubleJump = false;
	rich = 0.3f + (upgrade * 0.1f);
	isMultiAttack = false;
	isHomingAttack = false;
}