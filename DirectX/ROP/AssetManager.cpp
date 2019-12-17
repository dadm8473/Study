#include "DXUT.h"
#include "Header.h"

AssetManager* AssetManager::instance;
AssetManager* gAssetManager;

void AssetManager::LoadAssets()
{
	// LoadTexture(string, L"filename", L"png", maxScene);

	LoadTexture("Player", L"images/2차/player/Player1/player00", L"png", 20);
	LoadTexture("Player1", L"images/2차/player/Player2/player01", L"png", 20);
	LoadTexture("Player2", L"images/2차/player/Player3/player02", L"png", 20);

	//LoadTexture("PlayerBullet", L"images/2차/Bullet/bullet00", L"png", 20);

	// 플레이어 총알
	//LoadTexture("PlayerBullet", L"images/2차/Bullet/bullet00", L"png", 20);
	LoadTexture("Bullet", L"images/2차/Bullet/bellet01", L"png", 1);
	// bullet 0100 ??
	// 적 총알
	//("EnemyBullet", L"images/2차/Bullet/bullet02", L"png", 20);

	LoadTexture("Object", L"images/2차/Enemy/stone00", L"png", 1);
	LoadTexture("Hole", L"images/2차/Tile/trap00", L"png", 1);
	LoadTexture("Item1", L"images/2차/Item/item00", L"png", 10);
	LoadTexture("Item2", L"images/2차/Item/item01", L"png", 10);
	LoadTexture("Item3", L"images/2차/Item/item02", L"png", 10);
	LoadTexture("Item4", L"images/2차/Item/item03", L"png", 10);
	LoadTexture("Item5", L"images/2차/Item/item04", L"png", 10);
	//LoadTexture("Item6", L"images/2차/Item/item05", L"png", 10);

	LoadTexture("ItemUI", L"images/Item/UI/ui00", L"png", 10);

	LoadTexture("StageClear", L"images/UI/Stage/Black00", L"png", 2);

	LoadTexture("Container", L"images/2차/Item/item05", L"png", 1);
	LoadTexture("Clear", L"images/Item/Clear00", L"png", 1);

	LoadTexture("Effect", L"images/Effect/effect", L"png", 3);
	// 총알 없어질 때
	LoadTexture("Effect_Bullet", L"images/2차/effect/effect00", L"png", 20);
	// 적 죽을 때
	LoadTexture("Effect_Enemy", L"images/2차/effect/effect01", L"png", 20);
	// 클리어 어택
	LoadTexture("Effect_Clear", L"images/2차/effect/effect02", L"png", 20);
	// 플레이어 죽을 때
	LoadTexture("Effect_Player", L"images/2차/effect/Boom/boom01", L"png", 20);

	LoadTexture("StageUI", L"images/UI/Stage/Stage00", L"png", 2);
	LoadTexture("conUI", L"images/UI/CTN/ctn00", L"png", 10);

	LoadTexture("Num", L"images/Num/num00", L"png", 10);
	LoadTexture("Apb", L"images/APB/apb00", L"png", 26);

	LoadTexture("Tile", L"images/Tile/tile00", L"png", 3);

	LoadTexture("Sky", L"images/Map/Sky", L"png", 1);
	LoadTexture("Mid", L"images/Map/Mid", L"png", 1);

	LoadTexture("Intro", L"images/Main/Title/intro00", L"png", 3);

	LoadTexture("Title", L"images/Main/Title/title00", L"png", 6);
	LoadTexture("Id", L"images/Main/Title/id00", L"png", 1);
	LoadTexture("HowTo", L"images/Main/Title/HowTo00", L"png", 3);
	LoadTexture("Rank", L"images/Main/Title/Rank00", L"png", 1);
	LoadTexture("Kredit", L"images/Main/Title/Kredit00", L"png", 1);

	LoadTexture("Win", L"images/Main/Ending/Win", L"png", 1);
	LoadTexture("noRank", L"images/Main/Ending/noRank00", L"png", 1);
	LoadTexture("Lose", L"images/Main/Ending/Lose", L"png", 1);
}

void AssetManager::ReleaseAssets()
{
	for (map<string, CTexture*>::iterator it = textures.begin(); it != textures.end(); ++it)
		if (it->second)
			delete it->second;

	textures.clear();
}

void AssetManager::LoadTexture(string key, LPCWSTR filename, LPCWSTR extname, int maxScene)
{
	if (textures.find(key) != textures.end())
		return;

	textures[key] = new CTexture(filename, extname, maxScene);
}

CTexture * AssetManager::GetTexture(string key)
{
	if (textures.find(key) == textures.end())
		return NULL;
	return textures[key];
}
