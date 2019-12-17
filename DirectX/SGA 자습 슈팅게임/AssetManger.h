#pragma once

class AssetManager
{
private:
	//클래스를 단 하나의 오브젝트로 만들기 = 싱글톤 패턴
	static AssetManager* instance;

	std::map<std::string, CTexture*> textures;

public:
	static AssetManager* Instance()
	{
		if (!instance)
			instance = new AssetManager();
		return instance;
	}

public:
	void LoadAssets();
	void ReleaseAssets();

	void LoadTexture(string key, LPCWSTR filename, LPCWSTR extname, int maxScene);

	CTexture* GetTexture(string key);
};

extern AssetManager* gAssetManager;