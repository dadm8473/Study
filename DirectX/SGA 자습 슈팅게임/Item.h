#pragma once
class CGameScene;
class CItem : public CMatrix
{
public:
	CGameScene* parentScene;
	
	int type;
	/*
	type 1 - 점수를 주는 아이템
	type 2 - 플레이어 attack power을 증가시키는 아이템
	type 3 - 특수 공격을 채워주는 아이템
	*/
	
	bool isDestroyed;

	int speed;
	int angle;

	RECT rect;

public:
	CItem(D3DXVECTOR2 pos, int type);
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
};

