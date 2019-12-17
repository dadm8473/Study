#pragma once

class CScene
{
public:
	CScene();
	virtual ~CScene();

	virtual void Update(float deltaTime);
	virtual void Render(LPD3DXSPRITE sprite);
	virtual void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
};