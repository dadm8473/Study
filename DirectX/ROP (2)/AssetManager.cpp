#include "DXUT.h"
#include "Header.h"

AssetManager* AssetManager::instance;
AssetManager* gAssetManager;

void AssetManager::LoadAssets()
{
	// LoadTexture(string, L"filename", L"png", maxScene);
	LoadTexture("Player", L"images/2��/player/Player1/player00", L"png", 20);
	LoadTexture("Player1", L"images/2��/player/Player2/player01", L"png", 20);
	LoadTexture("Player2", L"images/2��/player/Player3/player02", L"png", 20);

	// �÷��̾� ����
	LoadTexture("PlayerLife", L"images/2��/life00", L"png", 1);
	// clear attack count
	LoadTexture("ClearCount", L"images/2��/Clear", L"png", 1);

	// EndingScene Rank
	LoadTexture("Rank_End", L"images/2��/Rank00", L"png", 1);
	LoadTexture("noRank", L"images/2��/NoRank00", L"png", 1);

	// ��� �Ѿ�
	LoadTexture("Bullet_Sky", L"images/2��/Bullet/bellet01", L"png", 1);
	// ���� �Ѿ�
	LoadTexture("Bullet_Player", L"images/2��/Bullet/bellet00", L"png", 20);
	// �� �Ѿ�
	LoadTexture("Bullet_Enemy", L"images/2��/Bullet/bellet02", L"png", 20);

	// ��
	LoadTexture("Enemy1", L"images/2��/Enemy/enemy00", L"png", 20);
	LoadTexture("Enemy2", L"images/2��/Enemy/enemy01", L"png", 20);
	LoadTexture("Enemy3", L"images/2��/Enemy/enemy02", L"png", 20);

	// Object
	LoadTexture("Object", L"images/2��/Enemy/stone00", L"png", 2);
	LoadTexture("Hole", L"images/2��/Tile/trap00", L"png", 1);

	// temp
	LoadTexture("Item", L"images/2��/Item/ItemUI/item00", L"png", 7);
	// item
	LoadTexture("Item1", L"images/2��/Item/item02", L"png", 10);
	LoadTexture("Item2", L"images/2��/Item/item01", L"png", 10);
	LoadTexture("Item3", L"images/2��/Item/item04", L"png", 10);
	LoadTexture("Item4", L"images/2��/Item/item00", L"png", 10);
	LoadTexture("Item5", L"images/2��/Item/item03", L"png", 10);
	LoadTexture("Item6", L"images/2��/��/item05", L"png", 10);

	LoadTexture("ItemUI", L"images/Item/UI/ui00", L"png", 10);

	// Mini map
	LoadTexture("PlayerIcon", L"images/Minimap/playercheck", L"png", 1);
	LoadTexture("CheckIcon", L"images/Minimap/check", L"png", 1);
	LoadTexture("MiniMap", L"images/UI/minimap00", L"png", 1);

	LoadTexture("StageClear", L"images/UI/Stage/Black00", L"png", 2);

	LoadTexture("Container", L"images/2��/Item/item05", L"png", 1);
	LoadTexture("Clear", L"images/Item/Clear00", L"png", 1);

	// Effect
	LoadTexture("Effect", L"images/Effect/effect", L"png", 3);
	LoadTexture("Effect_Bullet", L"images/2��/effect/effect00", L"png", 20);
	LoadTexture("Effect_Enemy", L"images/2��/effect/effect01", L"png", 20);
	LoadTexture("Effect_Player", L"images/2��/effect/Boom/boom01", L"png", 20);
	LoadTexture("Effect_Clear", L"images/2��/effect/effect02", L"png", 20);

	LoadTexture("White", L"images/2��/effect/whiteOut", L"png", 1);

	LoadTexture("UI", L"images/2��/ui/ui00", L"png", 1);

	LoadTexture("StageUI", L"images/UI/Stage/Stage00", L"png", 3);
	LoadTexture("conUI", L"images/UI/CTN/ctn00", L"png", 10);

	LoadTexture("Num", L"images/Num/num00", L"png", 10);
	LoadTexture("Apb", L"images/APB/apb00", L"png", 26);

	// Ÿ��
	LoadTexture("Tile", L"images/2��/Tile/tile00", L"png", 4);
	LoadTexture("Tile2", L"images/2��/Tile/tile03", L"png", 3);

	LoadTexture("conEffect", L"images/Coneffect/coneffect00", L"png", 20);

	// ���� �߸� Ÿ��
	LoadTexture("TileEnd", L"images/2��/Tile/tileEnd", L"png", 2);

	LoadTexture("Sky", L"images/2��/Map/map00", L"png", 1);
	LoadTexture("Mid1", L"images/2��/Map/map01", L"png", 2);
	LoadTexture("Mid2", L"images/2��/Map/map02", L"png", 2);

	LoadTexture("Intro", L"images/2��/Intro/intro00", L"png", 40);
	LoadTexture("TitleBG", L"images/2��/Main/main00", L"png", 20);

	LoadTexture("Title", L"images/2��/Main/main03", L"png", 6);
	LoadTexture("Id", L"images/2��/�Ұ�", L"png", 1);

	LoadTexture("HowTo1", L"images/2��/Howto/howto00", L"png", 5);
	LoadTexture("HowTo2", L"images/2��/Howto/howto01", L"png", 5);
	LoadTexture("HowTo3", L"images/2��/Howto/howto02", L"png", 5);

	LoadTexture("Rank", L"images/2��/ranking00", L"png", 1);
	LoadTexture("Kredit", L"images/2��/cradit00", L"png", 1);

	LoadTexture("Win", L"images/2��/win00", L"png", 1);
	LoadTexture("Lose", L"images/2��/lose", L"png", 1);

	soundManager = new CSoundManager();
	soundManager->Initialize(DXUTGetHWND(), DSSCL_PRIORITY);
	soundManager->SetPrimaryBufferFormat(2, 22050, 16);

	LoadAsset_Sound("Clear", L"Sound/Clear.wav", 1);
	LoadAsset_Sound("Effect", L"Sound/Effect.wav", 10);
	LoadAsset_Sound("Lose", L"Sound/Lose.wav", 1);
	LoadAsset_Sound("Main", L"Sound/Main.wav", 1);
	LoadAsset_Sound("Stage1", L"Sound/Stage1.wav", 1);
	LoadAsset_Sound("Stage2", L"Sound/Stage2.wav", 1);
	LoadAsset_Sound("Win", L"Sound/Win.wav", 1);
}

void AssetManager::LoadAsset_Sound(string key, LPWSTR filename, int maxBuffer)
{
	soundManager->Create(&sounds[key], filename, 0, GUID_NULL, maxBuffer);
}

void AssetManager::ReleaseAssets()
{
	for (map<string, CTexture*>::iterator it = textures.begin(); it != textures.end(); ++it)
		if (it->second)
			delete it->second;
	textures.clear();


	for (auto it = sounds.begin(); it != sounds.end(); ++it)
		if (it->second)
			delete it->second;
	delete soundManager;
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
