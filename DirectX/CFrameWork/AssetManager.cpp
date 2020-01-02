#include "DXUT.h"
#include "Header.h"

AssetManager* AssetManager::instance;
AssetManager* gAssetManager;

void AssetManager::LoadAssets()
{
	// LoadTexture("key", L"filename", L"png", maxScene);
	LoadTexture("Intro", L"image/Scene/Title/intro00", L"png", 3);
	LoadTexture("Title", L"image/Scene/Title/title00", L"png", 2);

	LoadTexture("Win", L"image/Scene/Ending/win00", L"png", 1);
	LoadTexture("Lose", L"image/Scene/Ending/lose00", L"png", 1);
}

void AssetManager::ReleaseAssets()
{
	// for (map<string, CTexture*>::iterator it = textures.begin(); it != textures.end(); ++it)
	for (auto it = textures.begin(); it != textures.end(); ++it)
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

CTexture* AssetManager::GetTexture(string key)
{
	if (textures.find(key) == textures.end())
		return NULL;
	return textures[key];
}
