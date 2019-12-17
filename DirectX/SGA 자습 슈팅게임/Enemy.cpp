#include "DXUT.h"
#include "Header.h"

CEnemy::CEnemy(D3DXVECTOR2 pos, int type, int _rotate)
	:CMatrix(), type(type), isDestroyed(false), parrentScene(NULL), centerPick(NULL), hp(100), isDie(false), angle(180), timer(0), moveDir_X(1), moveDir_Y(1),
	attackTime(0.1f), attackTimer(0), exitTime(1), exitTimer(0), exit(false), speed(0), count(0), isAttack(false),
	beHit(false), hitRedTime(0.05f), hitRedTimer(0)
{
	position = pos;

	switch (type)
	{
	case 0:
	case 1:
		hp = 2;
		center = D3DXVECTOR2(64, 64);
		attackTime = 0.8f;
		attackTimer = 0.5f;
		rotate = 180;
		SetAnimation(0.06f, 28, false);
		break;
	case 10:
		hp = 20;
		center = D3DXVECTOR2(64, 64);
		speed = 256;
		attackTime = 1;
		rotate = 180;
		SetAnimation(0.016f, 61, true);
		break;
	case 11:
		center = D3DXVECTOR2(16, 16);
		attackTime = 1;
		break;
	case 20:
		hp = 40;
		center = D3DXVECTOR2(64, 64);
		attackTime = 1.5f;
		break;
	case 21:
		center = D3DXVECTOR2(64, 64);
		break;
	case 22:
		center = D3DXVECTOR2(192, 64);
		rotate = _rotate;
		break;
	case 30:
		hp = 30;
		center = D3DXVECTOR2(64, 64);
		attackTime = 1;
		break;
	case 90:
		hp = 5;
		center = D3DXVECTOR2(64, 64);
		break;
	case 100:
		center = D3DXVECTOR2(16, 0);
		SetAnimation(0.2f, 2, true);
		attackTime = 3;
		break;
	}
}

void CEnemy::Update(float deltaTime)
{
	switch (type)
	{
	// Type 1 - �밢�� ������ (������)
	case 0:
		// �������ϸ鼭 �����Ѿ�
		SetRect(&rect, position.x - 40, position.y - 40, position.x + 40, position.y + 40);

		position.y += 150 * deltaTime;
		position.x += 300 * deltaTime;

		attackTimer += deltaTime;
		if (attackTimer >= attackTime)
		{
			if (count >= 2)
			{

			}
			else
			{
				if (parrentScene->player)
				{
					angle = GetAngle(
						parrentScene->player->position.x - position.x,
						parrentScene->player->position.y - position.y);
				}
				parrentScene->enemyBulletList.push_back(new CBullet(position, 10, 500, angle, 10));
				parrentScene->enemyBulletList.push_back(new CBullet(position, 10, 500, angle - 15, 10));
				parrentScene->enemyBulletList.push_back(new CBullet(position, 10, 500, angle + 15, 10));

				attackTimer = 0;
				count++;
			}
		}
		break;
	// Type 2 - �밢�� ������ (����)
	case 1:
		//
		SetRect(&rect, position.x - 40, position.y - 40, position.x + 40, position.y + 40);

		position.y += 150 * deltaTime;
		position.x -= 300 * deltaTime;

		attackTimer += deltaTime;
		if (attackTimer >= attackTime)
		{
			if (count >= 2)
			{

			}
			else
			{
				if (parrentScene->player)
				{
					angle = GetAngle(
						parrentScene->player->position.x - position.x,
						parrentScene->player->position.y - position.y);
				}
				parrentScene->enemyBulletList.push_back(new CBullet(position, 10, 500, angle, 10));
				parrentScene->enemyBulletList.push_back(new CBullet(position, 10, 500, angle - 15, 10));
				parrentScene->enemyBulletList.push_back(new CBullet(position, 10, 500, angle + 15, 10));

				attackTimer = 0;
				count++;
			}
		}
		break;
	// Type 10 - ��¡��
	case 10:
		SetRect(&rect, position.x - 40, position.y - 40, position.x + 40, position.y + 40);
		if (!exit)
		{
			// ���ͼ� type 11 ���� 3���� ��
			if (count >= 3)
				exit = true;
			else
				attackTimer += deltaTime;

			if (attackTimer >= attackTime)
			{
				parrentScene->enemyList.push_back(new CEnemy(D3DXVECTOR2(position.x, position.y + 65), 11));
				count++;

				attackTimer = 0;
			}

			if (position.y > 150)
				speed = 0;

			position.y += speed * deltaTime;
		}
		else
		{
			exitTimer += deltaTime;
			if(exitTimer >= exitTime)
				position.y -= 256 * deltaTime;
		}
		break;
	// Type 11 - ��¡��
	case 11:
		// ��¡ ���� �Ѿ� �뿪
		attackTimer += deltaTime;
		scale = D3DXVECTOR2(1 + 3 * timer, 1 + 3 * timer);
		if (attackTimer >= attackTime)
		{
			SetRect(&rect, position.x - 40, position.y - 40, position.x + 40, position.y + 40);
			if (!isAttack)
			{
				if (parrentScene->player)
				{
					angle = GetAngle(
						parrentScene->player->position.x - position.x,
						parrentScene->player->position.y - position.y);
				}
				rotate = angle;

				isAttack = true;
			}

			position.x += sin(angle*(D3DX_PI / 180)) * 800 * deltaTime;
			position.y -= cos(angle*(D3DX_PI / 180)) * 800 * deltaTime;
		}
		else
			timer += deltaTime;
		break;
	// Type 20 - n way
	case 20:
		SetRect(&rect, position.x - 40, position.y - 40, position.x + 40, position.y + 40);

		// �缱���� �̵��ϸ鼭 �÷��̾�� n-way ����
		position.x += moveDir_X * 200 * deltaTime;
		position.y += 64 * deltaTime;
		if (position.x < 65)
			moveDir_X = -moveDir_X;
		if (position.x >= 668)
			moveDir_X = -moveDir_X;

		

		attackTimer += deltaTime;
		if (attackTimer >= attackTime)
		{
			if (parrentScene->player)
			{
				angle = GetAngle(
					parrentScene->player->position.x - position.x,
					parrentScene->player->position.y - position.y);
			}
			for(int i = 0; i <5; i++)
				parrentScene->enemyBulletList.push_back(new CBullet(position, 10, 500, angle - 30 +  ( i * 15 ), 10));

			attackTimer = 0;
		}
		break;

		// ������
	case 30:
		SetRect(&rect, position.x - 40, position.y - 40, position.x + 40, position.y + 40);

		if (position.y <= 200)
		{
			position.y += 150 * deltaTime;
		}
		else
		{
			// ���� �ð��� ������ �÷��̾� ������ ����
			attackTimer += deltaTime;
			if (attackTimer >= attackTime)
			{
				if (!isAttack)
				{
					if (parrentScene->player)
					{
						angle = GetAngle(
							parrentScene->player->position.x - position.x,
							parrentScene->player->position.y - position.y);
					}

					rotate = angle;

					isAttack = true;
				}

				position.x += sin(angle*(D3DX_PI / 180)) * 1024 * deltaTime;
				position.y -= cos(angle*(D3DX_PI / 180)) * 1024 * deltaTime;
			}
			else
			{
				if (parrentScene->player)
				{
					angle = GetAngle(
						parrentScene->player->position.x - position.x,
						parrentScene->player->position.y - position.y);
				}

				rotate = angle;
			}
		}
		break;
	case 90:
		SetRect(&rect, position.x - 40, position.y - 40, position.x + 40, position.y + 40);

		position.x += moveDir_X * 200 * deltaTime;
		if (position.x < 65)
			moveDir_X = -moveDir_X;
		if (position.x >= 668)
			moveDir_X = -moveDir_X;

		position.y += moveDir_Y * 150 * deltaTime;
		if (position.y > 960)
			moveDir_Y = -moveDir_Y;

		break;
	case 100:
		if (parrentScene->player)
		{
			angle = GetAngle(
				parrentScene->player->position.x - position.x,
				parrentScene->player->position.y - position.y);
		}

		position.x += sin(angle * (D3DX_PI / 180)) * 450 * deltaTime;

		attackTimer += deltaTime;
		if (attackTimer >= attackTime)
		{
			parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(position.x, position.y), 100, 1024, 180, 10));

			attackTimer = 0;
			isDestroyed = true;
		}

		break;
	}

	if (position.x < -256 || position.x > 800 || position.y < -256 || position.y > 1080)
		isDestroyed = true;

	if (beHit)
	{
		g = 0;
		b = 0;

		hitRedTimer += deltaTime;

		if (hitRedTimer >= hitRedTime)
		{
			beHit = false;
			hitRedTimer = 0;
		}
	}
	else
	{
		g = 255;
		b = 255;
	}

	CMatrix::Update(deltaTime);
}

void CEnemy::Render(LPD3DXSPRITE sprite)
{
	switch (type)
	{
	case 0:
		Draw(sprite, gAssetManager->GetTexture("������1"));
		break;
	case 1:
		Draw(sprite, gAssetManager->GetTexture("������2"));
		break;
	case 10:
		Draw(sprite, gAssetManager->GetTexture("��¡"));
		break;
	case 11:
		Draw(sprite, gAssetManager->GetTexture("chargingBullet"));
		break;
	case 20:
		Draw(sprite, gAssetManager->GetTexture("enemy"));
		break;
	case 21:
		Draw(sprite, gAssetManager->GetTexture("enemy"));
		break;
	case 22:
		Draw(sprite, gAssetManager->GetTexture("enemy"));
		break;
	case 30:
		Draw(sprite, gAssetManager->GetTexture("enemy"));
		break;
	case 90:
		Draw(sprite, gAssetManager->GetTexture("chest"));
		break;
	case 100:
		Draw(sprite, gAssetManager->GetTexture("line"));
		break;
	}
}