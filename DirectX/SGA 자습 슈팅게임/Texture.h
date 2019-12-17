#pragma once

class CTexture
{
public:
	LPDIRECT3DTEXTURE9* _textures;
	D3DXIMAGE_INFO imageInfo;

	int maxScene;
	int width, height;

	LPDIRECT3DTEXTURE9 GetTexture(int idx) {
		if (idx < 0 || idx >= maxScene)
			return NULL;
		return _textures[idx];
	}

public:
	CTexture(LPCWSTR filename, LPCWSTR extname, int maxScene);
	~CTexture();
};