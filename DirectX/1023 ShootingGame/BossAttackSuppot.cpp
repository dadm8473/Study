#include "DXUT.h"
#include "Header.h"
#include <cstdlib>
#include <ctime>
using namespace std;

CBossAttackSuppot::CBossAttackSuppot(D3DXVECTOR2 pos, int type, int _rotate)
	: CMatrix(), type(type), isDestroyed(false), attackTime(0), attackTimer(0), isAttack(false), angle(180),
	time_(0), timer(0), sum(0)
{
	position = pos;
	SetCameraObject(&gCamera);

	switch (type)
	{
		// ¸¶¹ýÁø
	case 1: 
		center = D3DXVECTOR2(32, 32);
		attackTime = 2;
		scale = D3DXVECTOR2(0.1f, 0.1f);
		break;
		// ¼è»ç½½
	case 2:
		attackTime = 0.05f;
		a = 255;
		time_ = 2;
		center = D3DXVECTOR2(32, 32);
		break;
	case 3:
		// ¼è»ç½½ ÆøÅº
		attackTime = 1.5f;
		time_ = 0.3f;
		center = D3DXVECTOR2(12, 24);
		scale = D3DXVECTOR2(3, 3);
		break;
	case 4:
		// È¸¿À¸® ¸÷
		attackTime = 0.1f;
		center = D3DXVECTOR2(32, 32);
		break;
	case 5:
		break;
	case 6:
		break;
	}
}

void CBossAttackSuppot::Update(float deltaTime)
{
	switch (type)
	{
		// ¸¶¹ýÁø
	case 1:
		rotate += 30 * deltaTime;

		scale += D3DXVECTOR2(2 * deltaTime, 2 * deltaTime);

		if (parrentScene->player)
		{
			angle = GetAngle(
				parrentScene->player->position.x - position.x,
				parrentScene->player->position.y - position.y);
		}
		position.x += sin(angle*(D3DX_PI / 180)) * 100 * deltaTime;
		position.y -= cos(angle*(D3DX_PI / 180)) * 100 * deltaTime;

		attackTimer += deltaTime;
		if (attackTimer >= attackTime)
		{
			attackTimer = 0;
			// effect
			isDestroyed = true;
		}
		break;
	case 2:
		// ¼è»ç½½ ÇÃ·¹ÀÌ¾î ÂÊÀ¸·Î ³¯¶ó°¡¸é¼­ ÆøÅºÀ» »ý¼º
		if (!isAttack)
		{
			if (parrentScene->player)
				angle = GetAngle(
					parrentScene->player->position.x - position.x,
					parrentScene->player->position.y - position.y);

			rotate = angle;
			isAttack = true;
		}

		if (position.y <= 1054 && position.x >= -20 && position.x <= 788)
		{
			position.x += sin(angle*(D3DX_PI / 180)) * 2024 * deltaTime;
			position.y -= cos(angle*(D3DX_PI / 180)) * 2024 * deltaTime;

			attackTimer += deltaTime;
			if (attackTimer >= attackTime)
			{
				CBossAttackSuppot* bossAS = new CBossAttackSuppot(position, 3);
				parrentScene->bossASList.push_back(bossAS);
				attackTimer = 0;
			}
		}

		timer += deltaTime;
		if (timer >= time_)
		{
			this->a -= 100 * deltaTime;
			if (a <= 10)
			{
				timer = 0;
				isDestroyed = true;
			}
		}

		break;
	case 3:
		// ¼è»ç½½ ÆøÅº
		attackTimer += deltaTime;
		if (attackTimer >= attackTime)
		{
			attackTimer = 0;
			isAttack = true;
			parrentScene->effectList.push_back(new CEffect(position, 1, 0.02f));

		}
		if (isAttack)
		{
			SetRect(&rect, position.x - 100, position.y - 100, position.x + 100, position.y + 100);
			timer += deltaTime;
			if (timer >= time_)
			{
				isDestroyed = true;
			}
		}

		break;
	case 4:
		// ¼Ò¿ëµ¹ÀÌ ¸÷
		position.y += 400 * deltaTime;

		attackTimer += deltaTime;
		if (attackTimer >= attackTime)
		{
			for (int i = 0; i < 2; i++)
			{
				parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 300, (i * 180) + (sum * 25), 10));
			}

			sum++;
			attackTimer = 0;
		}
		break;
	case 5:
		break;
	case 6:
		break;
	}

	/*if (position.x < -256 || position.x > 800 || position.y < -256 || position.y > 1080)
		isDestroyed = true;*/

	CMatrix::Update(deltaTime);
}

void CBossAttackSuppot::Render(LPD3DXSPRITE sprite)
{
	switch (type)
	{
	case 1:
		Draw(sprite, gAssetManager->GetTexture("bossSA_1"));
		break;
	case 2:
		Draw(sprite, gAssetManager->GetTexture("chain"));
		break;
	case 3:
		Draw(sprite, gAssetManager->GetTexture("bossBullet"));
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	}
}

int CBossAttackSuppot::randomSum(int min, int max)
{
	srand(time(NULL));

	int ran = rand() % max + min;

	return ran;
}