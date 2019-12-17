#include "DXUT.h"
#include "Header.h"

AssetManager* AssetManager::instance;
AssetManager* gAssetManager;

void AssetManager::LoadAssets()
{
	LoadTexture("player", L"images/�÷�3/player000", L"png", 41);
	LoadTexture("Addon", L"images/�ֵ��/addon00", L"png", 40);

	LoadTexture("playerBullet", L"images/Bullet/PlayerBullet/PlayerBullet00", L"png", 1);

	LoadTexture("enemy", L"images/Enemy/enemy00", L"png", 1);
	LoadTexture("������1", L"images/����/enemy02", L"png", 41);
	LoadTexture("������2", L"images/������/enemy00", L"png", 41);
	LoadTexture("��¡", L"images/��¡/enemy03", L"png", 61);
	LoadTexture("enemyBullet", L"images/Bullet/EnemyBullet/EnemyBullet00", L"png", 1);

	LoadTexture("chest", L"images/Item/Chest00", L"png", 1);
	LoadTexture("scoreItem", L"images/Item/scoreItem00", L"png", 1);
	LoadTexture("powerItem", L"images/Item/powerItem00", L"png", 1);
	LoadTexture("specialItem", L"images/Item/specialItem00", L"png", 1);

	LoadTexture("bossBullet", L"images/Bullet/BossBullet/BossBullet00", L"png", 1);
	LoadTexture("bossBullet_Laser", L"images/Bullet/BossBullet/BossBullet10", L"png", 1);
	LoadTexture("bossSA_1", L"images/Bullet/BossSA/BossSA00", L"png", 1);
	LoadTexture("chain", L"images/Bullet/BossSA/chain00", L"png", 1);
	LoadTexture("boom", L"images/Bullet/BossSA/boom00", L"png", 1);

	LoadTexture("effect", L"images/��������Ʈ/die00", L"png", 21);

	LoadTexture("line", L"images/Enemy/Line00", L"png", 2);
	LoadTexture("meteor", L"images/Enemy/meteor00", L"png", 1);
	LoadTexture("chargingBullet", L"images/Bullet/EnemyBullet/charging00", L"png", 1);

	LoadTexture("effect_1", L"images/Effect/effect00", L"png", 40);

	LoadTexture("bossHpBar", L"images/boss/BossHpBar00", L"png", 1);
	LoadTexture("bossHpValue", L"images/boss/BossHpValue00", L"png", 1);

	LoadTexture("number", L"Images/Num/Num", L"png", 10);

	LoadTexture("land", L"images/map/map00", L"png", 1);
	LoadTexture("cloud_1", L"images/map/cloud00", L"png", 1);
	LoadTexture("cloud_2", L"images/map/cloud01", L"png", 1);

	LoadTexture("howTo", L"images/Main/TitleScene/HowTo00", L"png", 1);
	LoadTexture("ranking", L"images/Main/TitleScene/Ranking00", L"png", 1);
	LoadTexture("title", L"images/Main/TitleScene/Title00", L"png", 4);

	LoadTexture("victory", L"images/Main/EndingScene/Victory00", L"png", 1);
	LoadTexture("lose", L"images/Main/EndingScene/Lose00", L"png", 1);
}

void AssetManager::ReleaseAssets()
{
	for (map<string, CTexture*>::iterator it = textures.begin(); it != textures.end(); ++it)
	{
		if (it->second)
			delete it->second;
	}
	textures.clear();
}

void AssetManager::LoadTexture(string key, LPCWSTR filename, LPCWSTR extname, int maxScene)
{
	if (textures.find(key) != textures.end())
	{
		//���� Ű�� �̹� ����
		MessageBox(DXUTGetHWND(), L"�ؽ�ó Ű �ߺ�!", L"", MB_OK);
		return;
	}

	textures[key] = new CTexture(filename, extname, maxScene);
}

CTexture* AssetManager::GetTexture(string key)
{
	if (textures.find(key) == textures.end())
	{
		return NULL;
	}

	return textures[key];

}