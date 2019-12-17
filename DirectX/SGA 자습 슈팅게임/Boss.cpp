#include"DXUT.h"
#include "Header.h"
#include <cstdlib>
#include <ctime>
using namespace std;

CBoss::CBoss(int _type)
	: hp(0), maxHp(0), speed(0), type(_type), isDie(false), isEnter(false), patternTime(0), patternTimer(0), isPatternOn(false), patternNum(3), sum(0), sum_1(0),
	attackTime(0), attackTimer(0), maxBullet(0), bulletCount(0), bulletSpeed(0), moveDir(1), pAngle(0), x(0), y(0)
{
	this->position = D3DXVECTOR2(384, -30);

	center = D3DXVECTOR2(64, 64);

	switch (type)
	{
	case 1:
		// 1 Stage Side Boss
		hp = 2000;
		break;
	case 2:
		// 1 Stage Boss
		hp = 2500;
		break;
	case 3:
		// 2 Stage Side Boss
		hp = 3500;
		break;
	case 4:
		// 2 Stage Boss
		hp = 5000;
		break;
	}

	maxHp = hp;
	patternTime = 1.5f;
}

void CBoss::Update(float deltaTime)
{
	if (!isDie)
	{
		// 임시 테스트 충돌
		SetRect(&rect, position.x - 40, position.y - 40, position.x + 40, position.y + 40);

		if (isEnter)
		{
			position.x += moveDir * speed * deltaTime;
			if (position.x >= 540 || position.x <= 228)
				moveDir = -moveDir;

			if (!isPatternOn)
			{
				patternTimer += deltaTime;
				if (patternTimer >= patternTime)
				{
					isPatternOn = true;
					patternTimer = 0;
					switchPattern();
				}
			}
			else
			{
				attackTimer += deltaTime;
				if (attackTimer >= attackTime)
				{
					attackTimer = 0;
					switch (type)
					{
					case 1:
						StageOneSideBoss();
						break;
					case 2:
						StageOneBoss();
						break;
					case 3:
						StageTwoSideBoss(deltaTime);
						break;
					case 4:
						StageTwoBoss(deltaTime);
						break;
					}
				}
			}
		}
		else
		{
			position.y += 256 * deltaTime;

			if (position.y >= 128)
			{
				position.y = 128;
				isEnter = true;
			}
		}
	}
	CMatrix::Update(deltaTime);
}

void CBoss::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("enemy"));
}

void CBoss::switchPattern()
{
	isPatternOn = true;
	patternTimer = 0;
	bulletCount = 0;
	bulletSpeed = 0;
	sum = 0;
	sum_1 = 0;
	speed = 128;
	x = 0;
	y = 0;

	switch (type)
	{
	case 1:
		switch (patternNum)
		{
		case 1:
			attackTime = 0.4f;
			maxBullet = 18;
			break;
		case 2:
			attackTime = 0.2f;
			maxBullet = 18;
			sum = 0;
			break;
		case 3:
			attackTime = 0.05f;
			maxBullet = 100;
			break;
		}
		break;
	case 2:
		switch (patternNum)
		{
		case 1:
			attackTime = 0.04f;
			maxBullet = 85;
			speed = 0;
			break;
		case 2:
			attackTime = 0.5f;
			maxBullet = 10;
			speed = 0;
			break;
		case 3:
			attackTime = 0.01f;
			maxBullet = 300;
			speed = 0;
			sum_1 = 1;
			break;
		}
		break;
	case 3:
		switch (patternNum)
		{
		case 1:
			attackTime = 0.1f;
			maxBullet = 50;
			break;
		case 2:
			attackTime = 0.01f;
			maxBullet = 250;
			sum_1 = 1;
			break;
		case 3:
			attackTime = 0.03f;
			maxBullet = 50;
			speed = 0;
			break;
		}
		break;
	case 4:
		speed = 0;
		switch (patternNum)
		{
		case 1:
			attackTime = 0.005f;
			maxBullet = 700;
			break;
		case 2:
			attackTime = 0.1f;
			maxBullet = 207;
			sum = 200;
			break;
		case 3:
			attackTime = 0.9f;
			maxBullet = 13;
			break;
		}
		break;
	}
}

void CBoss::StageOneSideBoss()
{
	switch (patternNum)
	{
	case 1:	// N-way Application Pattern
		switch (sum)
		{
		case 0:
			for (int i = 0; i < 3; i++)
			{
				parrentScene->enemyBulletList.push_back(new CBullet(position + D3DXVECTOR2(-128, 0), -1, 550, 150 + (i * 30), 10));
				parrentScene->enemyBulletList.push_back(new CBullet(position + D3DXVECTOR2(128, 0), -1, 550, 150 + (i * 30), 10));
			}
			sum = 1;
			break;
		case 1:
			parrentScene->enemyBulletList.push_back(new CBullet(position + D3DXVECTOR2(-128, 0), -1, 550, 180, 10));
			parrentScene->enemyBulletList.push_back(new CBullet(position + D3DXVECTOR2(128, 0), -1, 550, 180, 10));
			sum = 2;
			break;
		case 2:
			for(int i = 1; i < 10; i++)
				parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 550, 135 + (i * 9), 10));
			sum = 0;
			break;
		}

		bulletCount++;

		if (bulletCount > maxBullet)
		{
			isPatternOn = false;
			patternNum = 2;
		}
		else
			patternNum = 1;
		break;
	case 2:	// n-way Fast Pattern
		speed = 256;

		switch (sum)
		{
		case 0:
			for (int i = 0; i <= 9; i++)
			{
				parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 600, 90 + (i * 20), 10));
			}
			sum = 1;
			break;
		case 1:
			for (int i = 0; i <= 8; i++)
			{
				parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 450, 100 + (i * 20), 10));
			}
			sum = 0;
			break;
		}

		bulletCount++;

		if (bulletCount > maxBullet)
		{
			isPatternOn = false;
			patternNum = 3;
		}
		else
			patternNum = 2;
		break;
	case 3: // Tornado Pattern

		parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 600, 0 + (sum * 15), 10));
		parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 450, 90 + (sum * 15), 10));
		parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 600, 180 + (sum * 15), 10));
		parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 450, 270 + (sum * 15), 10));

		sum++;
		bulletCount++;

		if (bulletCount > maxBullet)
		{
			isPatternOn = false;
			patternNum = 1;
		}
		else
			patternNum = 3;
		break;
	}
}

void CBoss::StageOneBoss()
{
	switch (patternNum)
	{
	case 1:
		for(int i = 0; i < 3; i++)
			parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 500, 180 + (sum * 7) + (i * 120), 10));

		for(int i = 0; i < 3; i++)
			parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 500, 360 - (sum * 7) - (i * 120), 10));

		

		bulletCount++;
		sum++;

		if (bulletCount > maxBullet)
		{
			isPatternOn = false;
			patternNum = 2;
		}
		else
			patternNum = 1;

		break;
	case 2:
		switch (sum_1)
		{
		case 0:
			for (int i = 0; i < 15; i++)
				parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 155 + (i * 30), 250 - (i * 5), 10));
			sum_1 = 1; 
			break;
		case 1:
			for (int i = 0; i < 15; i++)
				parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 155 + (i * 30), 110 + (i * 5), 10));
			sum_1 = 0;
			break;
		}

		bulletCount++;
		sum++;

		if (bulletCount > maxBullet)
		{
			isPatternOn = false;
			patternNum = 3;
		}
		else
			patternNum = 2;

		break;
	case 3:
		parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 500, 180 + sum_1*(sum * 13), 10));
		parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 300, 0 + sum_1*(sum * 13), 10));

		sum++;

		if (bulletCount % 30 == 0)
			sum_1 = -sum_1;

		bulletCount++;

		if (bulletCount > maxBullet)
		{
			isPatternOn = false;
			patternNum = 1;
		}
		else
			patternNum = 3;
		break;
	}
}

void CBoss::StageTwoSideBoss(float deltaTime)
{
	switch (patternNum)
	{
	case 1:
		for (int i = 0; i < 5; i++)
			parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 400, 180 + (sum * 7) + (i * 72), 10));

		for (int i = 0; i < 5; i++)
			parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 400, 360 - (sum * 7) - (i * 72), 10));

		bulletCount++;
		sum++;

		if (bulletCount > maxBullet)
		{
			isPatternOn = false;
			patternNum = 2;
		}
		else
			patternNum = 1;

		break;
	case 2:
		switch (sum_1)
		{
		case -1:
			parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(position.x + 200, position.y), -1, 500, 90 + (sum * 17), 10));
			parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(position.x - 200, position.y), -1, 500, 90 - (sum * 17), 10));
			sum++;																							   
			break;																							   
		case 1:																								   
			parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(position.x + 200, position.y), -1, 500, 90 - (sum * 17), 10));
			parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(position.x - 200, position.y), -1, 500, 90 + (sum * 17), 10));
			sum++;
			break;
		}

		if (bulletCount % 40 == 0)
			sum_1 = -sum_1;

		bulletCount++;

		if (bulletCount > maxBullet)
		{
			isPatternOn = false;
			patternNum = 3;
		}
		else
			patternNum = 2;
		break;
	case 3:
		for (int i = 0; i < 4; i++)
		{
			parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(position.x + 200, position.y), -1, 400, (i * 90) + (sum * 15), 10));
		}

		for (int i = 0; i < 4; i++)
		{
			parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(position.x - 200, position.y), -1, 400, (i * 90) - (sum * 15), 10));
		}

		sum++;
		bulletCount++;

		if (bulletCount > maxBullet)
		{
			isPatternOn = false;
			patternNum = 1;
		}
		else
			patternNum = 3;

		break;
	}
}

void CBoss::StageTwoBoss(float deltaTime)
{
	switch (patternNum)
	{
	case 1:
	{
		/*x = position.x + (cos(pAngle) * 100);
		y = position.y + (sin(pAngle) * 200);

		parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(x, y), -1, 500, sum * 5, 10, 0.35f));
		parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(x, y), -1, 500, 2 + sum * 5, 10, 0.35f));*/
		/*int x_cos = cosf(3.141592/4) * (position.x + sinf(pAngle) * 50);
		int y_cos = cosf(3.141592/4) * (position.y + cosf(pAngle) * 50);
		int x_sin = sinf(3.141592/4) * (position.x + sinf(pAngle) * 50);
		int y_sin = sinf(3.141592/4) * (position.y + cosf(pAngle) * 50);

		x = x_cos - y_sin;
		y = x_sin + y_cos;*/

		// 주석 모양대로 타원을 출력해서 날림
		if (bulletCount < 500)
		{
			if (bulletCount % 2 == 0)
			{
				int x_cos = position.x + (cos(pAngle) * 50);
				int y_sin = position.y + (sin(pAngle) * 200);

				x = x_cos - y_sin;
				y = x_cos + y_sin;
				// /
				parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(x + 125, y - 380), -2, 350, sum * 7, 10, 3));

				x_cos = position.x + (cos(pAngle) * 200);
				y_sin = position.y + (sin(pAngle) * 50);

				x = x_cos - y_sin;
				y = x_cos + y_sin;
				// ＼
				parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(x + 125, y - 380), -2, 350, sum * 7, 10, 3));
			}
			else
			{
				int x_cos = position.x + (cos(pAngle) * 50);
				int y_sin = position.y + (sin(pAngle) * 300);
				// |
				parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(x_cos, y_sin), -2, 350, sum * 7, 10, 3));

				x_cos = position.x + (cos(pAngle) * 300);
				y_sin = position.y + (sin(pAngle) * 50);

				// ㅡ
				parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(x_cos, y_sin), -2, 350, sum * 7, 10, 3));
			}
			pAngle += 5;

			sum++;
		}

		bulletCount++;

		if (bulletCount > maxBullet)
		{
			isPatternOn = false;
			patternNum = 2;
		}
		else
			patternNum = 1;
	}
	break;
	case 2:
		if (bulletCount < 200)
		{
			if (bulletCount % 50 == 0)
			{
				CBossAttackSuppot * bossAS = new CBossAttackSuppot(D3DXVECTOR2(sum, 0), 4);
				CBossAttackSuppot * bossAS_ = new CBossAttackSuppot(D3DXVECTOR2(sum, -255), 4);
				parrentScene->bossASList.push_back(bossAS);
				parrentScene->bossASList.push_back(bossAS_);
				if (sum == 200)
					sum = 568;
				else if (sum == 568)
					sum = 200;
			}
		}

		bulletCount++;

		if (bulletCount > maxBullet)
		{
			isPatternOn = false;
			patternNum = 3;
		}
		else
			patternNum = 2;
		break;
	case 3:
		/*for (int i = 0; i <= 18; i++)
		{
			parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 450, (i * 20), 10));
			parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 350, 10 + (i * 20), 10));
		}*/

		if (bulletCount <= 10)
			if (bulletCount % 2 == 0)
			{
				CBossAttackSuppot* bossAS = new CBossAttackSuppot(D3DXVECTOR2(getRandomNumber(0, 768), 0), 2);
				parrentScene->bossASList.push_back(bossAS);
			}

		bulletCount++;

		bulletCount++;
		if (bulletCount > maxBullet)
		{
			isPatternOn = false;
			patternNum = 1;
		}
		else
			patternNum = 3;
		break;
	}
}

int CBoss::randomSum(int min, int max)
{
	srand(time(NULL));

	int ran = rand() % max + min;

	return ran;
}

// 벌레 공주 패턴
/*for (int i = 0; i < 36; i++)
parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 200, 180 + (sum * 1) + (i * 10), 10));

for (int i = 0; i < 36; i++)
parrentScene->enemyBulletList.push_back(new CBullet(position, -1, 200, 360 - (sum * 1) - (i * 10), 10));*/

// 원 그리고 날리기
/*x = position.x + (cos(pAngle) * 50);
y = position.y + (sin(pAngle) * 50);

int angle = GetAngle(
parrentScene->player->position.x - position.x,
parrentScene->player->position.y - position.y);

parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(x, y), -1, 400, angle, 10));

pAngle += 0.5f;

bulletCount++;*/

// 나중에 연구해보셈 원통형임
//for (int i = 0; i < 10; i++)
//{
//	x = position.x + (cos(pAngle) * 100);
//	y = position.y + (sin(pAngle) * 100);
//
//	int angle = GetAngle(
//		parrentScene->player->position.x - position.x,
//		parrentScene->player->position.y - position.y);
//
//	parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(x, y), -1, 400, angle, 10));
//
//	pAngle += 7;
//}

// 위에꺼로 만들었음
//for (int i = 1; i < 5; i++)
//{
//	x = position.x + (cos(pAngle) * 150);
//	y = position.y + (sin(pAngle) * 150);
//
//	parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(x, y), -1, 400, sum * 4, 10, 0.3f));
//
//	pAngle += 3;
//}
//
//sum++;

/*for (int i = 0; i < 2; i++)
{
parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(100, 100), -1, 300, (i * 180) + (sum * 15), 10));
}

for (int i = 0; i < 2; i++)
{
parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(668, 100), -1, 300, (i * 180) - (sum * 15), 10));
}

for (int i = 0; i < 2; i++)
{
parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(100, 924), -1, 300, (i * 180) - (sum * 15), 10));
}

for (int i = 0; i < 2; i++)
{
parrentScene->enemyBulletList.push_back(new CBullet(D3DXVECTOR2(668, 924), -1, 300, -(i * 180) + (sum * 15), 10));
}*/