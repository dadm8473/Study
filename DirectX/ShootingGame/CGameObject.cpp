#include "DXUT.h"
#include "Header.h"

CGameObject::CGameObject(D3DXVECTOR2 pos, CCamera* inputCamera)
	: camera(inputCamera), isDie(false), isDestroy(false), hp(1), speed(0),
	isAttack(false), attackTime(0), attackTimer(0), parentScene(NULL)
{
	position = pos;
}

CGameObject::~CGameObject()
{
}

void CGameObject::Update(float deltaTime)
{
	// Attack
	if (!isAttack && attackTime != 0)
	{
		attackTimer += deltaTime;
		if (attackTimer > attackTime)
		{
			isAttack = true;
			attackTimer = 0;
		}
	}

	// Die
	if (hp < 0)
		isDie = true;

	CMatrix::Update(deltaTime, camera->position);
}

void CGameObject::Render(LPD3DXSPRITE sprite)
{
}

void CGameObject::Attack()
{
	if (!isAttack)
		return;

	isAttack = false;
}
