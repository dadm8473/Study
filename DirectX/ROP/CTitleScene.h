#pragma once
class CTitleScene : public CScene
{
public:
	CMatrix* intro;

	CMatrix* titleImage;
	CMatrix* idImage;
	CMatrix* howToImage;
	CMatrix* rankImage;
	CMatrix* kreditImage;

	bool isIntro;

	bool isId;
	bool isHowTo;
	bool isRank;
	bool isKredit;

public:
	CMatrix* num[3][6];
	CMatrix* initial[3][3];

public:
	CTitleScene();
	~CTitleScene();
	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};

