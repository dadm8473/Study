#pragma once
class CTitleScene : public CScene
{
public:
	CMatrix* intro;
	CMatrix* titleBG;
	CMatrix* titleBG_2;

	CMatrix* titleImage;
	CMatrix* idImage;

	CMatrix* howToImage_1;
	CMatrix* howToImage_2;
	CMatrix* howToImage_3;

	CMatrix* rankImage;
	CMatrix* kreditImage;

	bool isIntro;

	bool isId;
	bool isHowTo;
	bool isRank;
	bool isKredit;

	int currentHowto;

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

