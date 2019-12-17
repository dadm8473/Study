#pragma once
#pragma once

class CEndingScene : public CScene
{
public:
	CMatrix* victoryImage;
	CMatrix* loseImage;
	bool isWin;
	bool leftMouseClick;

public:
	CEndingScene(bool isWin);
	virtual ~CEndingScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprtie);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};