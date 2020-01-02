#include "DXUT.h"
#include "Header.h"

CCamera::CCamera()
	: position(0, 0), center(384, 700), limitPos_Min(-50, 0), limitPos_Max(50, 0), target(NULL), speed(1)
{
}

CCamera::~CCamera()
{

}

void CCamera::Update(float deltatime)
{
	if (target)
		D3DXVec2Lerp(&position, &position, &(target->position - center), speed);
	else
		return;

	if (position.x <= limitPos_Min.x)
		position.x = limitPos_Min.x;
	if (position.x >= limitPos_Max.x)
		position.x = limitPos_Max.x;

	if (position.y <= limitPos_Min.y)
		position.y = limitPos_Min.y;
	if (position.y >= limitPos_Max.y)
		position.y = limitPos_Max.y;
}
