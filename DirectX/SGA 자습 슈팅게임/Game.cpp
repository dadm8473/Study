#include "DXUT.h"
#include "Header.h"
#include <random>
using namespace std;

int playerLife = 5;
int score = 0;
int power = 0;
int attackPower = 0;
int special = 3;
int stage = 1;

LPD3DXSPRITE gSprite = NULL;
CScene* gScene = NULL;

bool changeScene = true;
int changeSceneNum = 0;

CMatrix* loadingMatrix;
bool isLoading = true;
float loadTime = 0.33f, loadTimer = 0;
bool isStartLoading;
bool isFadingOut;
float fadeIntimer = 0;
float fadeIntime = 1;

float mainTime = 1;

void ChangeScene(int sceneNum)
{
	changeSceneNum = sceneNum;

	isStartLoading = true;
	isFadingOut = true;
	//changeScene = true;
}

void _ChangeScene(int sceneNum)
{
	if (gScene)
	{
		delete gScene;
		gScene = NULL;
	}

	switch (sceneNum)
	{
	case 0:
		gScene = new CTitleScene();
		break;
	case 1:
		gScene = new CGameScene(1);
		break;
	case 12:
		gScene = new CGameScene(2);
		break;
	case 2:
		gScene = new CEndingScene(true);
		break;
	case 3:
		gScene = new CEndingScene(false);
		break;
	}
}

void Init()
{
	loadingMatrix = new CMatrix();

	gCamera = new CMatrix();
	gCamera->center = D3DXVECTOR2(384, 512);

	gAssetManager = new AssetManager();
	gAssetManager->LoadTexture("loading", L"images/Main/loading00", L"png", 4);

	D3DXCreateSprite(DXUTGetD3D9Device(), &gSprite);

	ChangeScene(0);
}

void Term()
{
	gAssetManager->ReleaseAssets();
	delete gAssetManager;

	gSprite->Release();

	if (gScene)
	{
		delete gScene;
		gScene = NULL;
	}

	delete gCamera;
}

void Lost()
{
	gSprite->OnLostDevice();
}

void Reset()
{
	gSprite->OnResetDevice();
}

void Update(float deltaTime)
{
	if (gScene)
		gScene->Update(deltaTime);

	if (isStartLoading)
	{
		if (isFadingOut)
		{
			loadingMatrix->a += (int)(255 * deltaTime);
			if (loadingMatrix->a >= 255)
			{
				loadingMatrix->a = 255;

				fadeIntimer += deltaTime;
				if (fadeIntimer > fadeIntime)
				{
					fadeIntimer = 0;
					isFadingOut = false;
					_ChangeScene(changeSceneNum);
				}
			}
		}
		else
		{
			loadingMatrix->a -= (int)(255 * deltaTime);
			if (loadingMatrix->a <= 0)
			{
				loadingMatrix->a = 0;
				isStartLoading = false;
			}
		}
	}
}

void Render()
{
	gSprite->Begin(D3DXSPRITE_ALPHABLEND);

	if (gScene)
		gScene->Render(gSprite);

	loadingMatrix->Draw(gSprite, gAssetManager->GetTexture("loading"));

	gSprite->End();
}

void MsgProc(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (gScene)
		gScene->MsgProc(uMsg, wParam, lParam);
}

void LoadingUpdate(float deltaTime)
{
	loadingMatrix->Update(deltaTime);

	loadTimer += deltaTime;
	if (loadTimer >= loadTime)
	{
		gAssetManager->LoadAssets();
		isLoading = false;
	}
}

void LoadingRender()
{
	gSprite->Begin(D3DXSPRITE_ALPHABLEND);
	loadingMatrix->Draw(gSprite, gAssetManager->GetTexture("loading"));
	gSprite->End();
}


float GetAngle(float x, float y)
{
	// 좌표 받아오기
	return D3DXToDegree(atan2(y, x)) + 90;
}

int getRandomNumber(int min, int max)
{
	// 정수형 랜덤 변수 리턴
	//시드 설정
	random_device rn;
	mt19937_64 rnd(rn());

	uniform_int_distribution<int> range(min, max);

	return range(rnd);
}