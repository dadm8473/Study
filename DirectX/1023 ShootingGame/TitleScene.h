#pragma once
#pragma once

class CTitleScene : public CScene
{
public:
	CMatrix* titleImage;
	CMatrix* howToImage;
	CMatrix* rankImage;

	int mouseX;
	int mouseY;
	bool leftMouseClicked;

	bool isHowTo;
	bool isRank;
	bool isLight;

	RECT mouseRect;
	RECT startRect;
	RECT howToRect;
	RECT rankRect;
	RECT exitRect;
	RECT leaveRect;

public:
	CTitleScene();
	virtual ~CTitleScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprtie);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};