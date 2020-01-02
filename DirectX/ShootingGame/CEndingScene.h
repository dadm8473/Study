#pragma once
class CEndingScene : public CScene
{
public:
	CMatrix* winImage;
	CMatrix* loseImage;

	bool isWin;

public:
	CEndingScene(bool isWin);
	~CEndingScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

