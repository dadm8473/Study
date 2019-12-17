#include "DXUT.h"
#include "Header.h"

CTile::CTile(D3DXVECTOR2 pos, int inputType, CCamera * inputCamera)
	: type(inputType), camera(inputCamera)
{
	position = pos;
	currentScene = type;
}

void CTile::Update(float deltaTime)
{
	CMatrix::Update(deltaTime, camera->position);
}

void CTile::Render(LPD3DXSPRITE sprite)
{
	Draw(sprite, gAssetManager->GetTexture("Tile"));
}

float CTile::GetGround_Y_Pos(float xPos)
{
	float yPos = 0;

	if (position.x <= xPos && position.x + tileWidth > xPos)
	{
		float length = xPos - position.x;

		float value = 0;
		float delta_Y = 0;

		switch (type)
		{
		case 1:
			value = -100;
			delta_Y = 100;
			break;
		case 2:
			value = 100;
			break;
		}

		yPos = position.y + delta_Y + value * (length / tileWidth);
	}

	return yPos;
}
