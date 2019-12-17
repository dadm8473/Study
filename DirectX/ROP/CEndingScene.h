#pragma once
class CEndingScene : public CScene
{
public:
	CMatrix* winImage;
	CMatrix* loseImage;
	bool isWin;

public:
	bool isRank;
	bool isEnter;

	int currentInputIndex;
	float blinkTimer;

	CMatrix* num[6];
	CMatrix* initial[3];
	CMatrix* noRankMessage;

public:
	CEndingScene(bool isWin);
	~CEndingScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

