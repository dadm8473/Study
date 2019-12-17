#pragma once
class CTexture
{
public:
	LPDIRECT3DTEXTURE9* _texture;
	D3DXIMAGE_INFO imageInfo;

	int maxScene;
	int width, heigth;

	LPDIRECT3DTEXTURE9 GetTexture(int idx)
	{
		if (idx < 0 || idx > maxScene)
			return NULL;

		return _texture[idx];
	}

public:
	CTexture(LPCWSTR filename, LPCWSTR extname, int maxScene);
	~CTexture();
};

