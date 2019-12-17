#pragma once
class CGameScene;
class CItem : public CMatrix
{
public:
	CGameScene* parentScene;
	
	int type;
	/*
	type 1 - ������ �ִ� ������
	type 2 - �÷��̾� attack power�� ������Ű�� ������
	type 3 - Ư�� ������ ä���ִ� ������
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

