#include "DXUT.h"
#include "Header.h"

CPlayer::CPlayer(D3DXVECTOR2 pos, CCamera* inputCamera)
	: CGameObject(pos, inputCamera)
{
	center = D3DXVECTOR2(32, 32);

	hp = 3;
	speed = 350;

	attackTime = 0.05f;
	attackTimer = attackTime;
	
	// Animation
}

void CPlayer::Update(float deltaTime)
{
	// Player Move
	if(GetKeyState(VK_LEFT) & 0x8000)
		position.x -= speed * deltaTime;
	if (GetKeyState(VK_RIGHT) & 0x8000)
		position.x += speed * deltaTime;
	if (GetKeyState(VK_UP) & 0x8000)
		position.y -= speed * deltaTime;
	if (GetKeyState(VK_DOWN) & 0x8000)
		position.y += speed * deltaTime;

	// Player Attack
	if ((GetKeyState('X') & 0x8000) && isAttack)
		Attack();

	SetRect(&rect, position.x - 32, position.y - 32, position.x + 32, position.y + 32);
	CGameObject::Update(deltaTime);
}

void CPlayer::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Player"));

	CGameObject::Render(sprite);
}

void CPlayer::Attack()
{
	parentScene->playerBulletList.push_back(new CBullet(position, 1, 0, 500, camera));
	CGameObject::Attack();
}
