#include "DXUT.h"
#include "Header.h"

CTexture::CTexture(LPCWSTR filename, LPCWSTR extname, int maxScene)
{
	_textures = new LPDIRECT3DTEXTURE9[maxScene];
	this->maxScene = maxScene;

	for (int i = 0; i < maxScene; ++i)
	{
		wchar_t temp[256];
		wsprintf(temp, L"%s%02d.%s", filename, i, extname);

		D3DXGetImageInfoFromFile(temp, &imageInfo);

		if (FAILED(D3DXCreateTextureFromFileEx(
			DXUTGetD3D9Device(),
			temp,
			imageInfo.Width,
			imageInfo.Height,
			1,
			0,
			D3DFMT_A8R8G8B8,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			0,
			NULL,
			NULL,
			&_textures[i]
		)))
		{
			MessageBox(DXUTGetHWND(),
				temp,
				L"정해광이 잘못했습니다.",
				MB_OK);
		}

		if (i == 0)
		{
			width = imageInfo.Width;
			height = imageInfo.Height;
		}
	}
}

CTexture::~CTexture()
{
	for (int i = 0; i < maxScene; ++i)
	{
		if (_textures[i])
			_textures[i]->Release();
	}
	delete[] _textures;
}