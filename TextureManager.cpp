/*=============================================================================

		テクスチャ管理[ TextureManager.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/24
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/24
=============================================================================*/

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "TextureManager.h"

/*-----------------------------------------------------------------------------
	マクロ定義
-----------------------------------------------------------------------------*/
#define TEXTURE_PATH "data/TEXTURE/"

/*-----------------------------------------------------------------------------
	静的変数
-----------------------------------------------------------------------------*/
const LPSTR CTextureManager::m_FilePass[] = {
	TEXTURE_PATH"Fade.jpg",	//	フェード
	TEXTURE_PATH"TITLE/title_text.png",	//	プッシュボタン
	TEXTURE_PATH"TITLE/title.png",	//	タイトルロゴ
	TEXTURE_PATH"GAME/Ground.jpg",	//	地面
	TEXTURE_PATH"GAME/runningman000.png",
	TEXTURE_PATH"GAME/number000.png",	//	数字
	TEXTURE_PATH"GAME/Kill_Logo.png",	//	killロゴ
	TEXTURE_PATH"GAME/sky001.jpg",	//	スカイドーム
	TEXTURE_PATH"GAME/UI.png",
	TEXTURE_PATH"text.png",
	TEXTURE_PATH"RESULT/rogo.png",
	TEXTURE_PATH"Tutorial.png",
	TEXTURE_PATH"pushbuttom3.png",
	TEXTURE_PATH"Target.png",
	TEXTURE_PATH"GAME/Start.png",
	TEXTURE_PATH"GAME/Goal.png",
};

/*-----------------------------------------------------------------------------
関数名:		void CTextureManager::Load(TEXTURE_ID Id, D3DXVECTOR2 Div)
引数:		TEXTURE_ID Id		テクスチャのID
戻り値:
説明:		テクスチャのロード
-----------------------------------------------------------------------------*/
void CTextureManager::Load(TEXTURE_ID Id, D3DXVECTOR2 Div)
{
	m_TextureInfo[Id].Div = Div;

	//	同じファイルが存在するかの検索
	auto it = m_Texture_Map.find(Id);

	if (it == m_Texture_Map.end())
	{	//	存在しなかったら

		HRESULT hr;

		//	デバイスの取得
		LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();

		//	テクスチャの読み込み
		hr = D3DXCreateTextureFromFile(Device, m_FilePass[Id], &m_TextureInfo[Id].Texture);

		if (FAILED(hr))
		{
			MessageBox(NULL, "テクスチャが読み込めませんでした", "Texture.cpp", MB_OK | MB_ICONHAND);
			return;
		}

		//テクスチャ詳細情報取得
		D3DXIMAGE_INFO ImageInfo;
		D3DXGetImageInfoFromFile(m_FilePass[Id], &ImageInfo);
		m_TextureInfo[Id].Size.x = ImageInfo.Width / Div.x;
		m_TextureInfo[Id].Size.y = ImageInfo.Height / Div.y;


		//	キーと値を連結させる
		m_Texture_Map[Id] = m_TextureInfo[Id];
	}
}

/*-----------------------------------------------------------------------------
関数名:		void CTextureManager::UnloadAll(void)
引数:
戻り値:
説明:		全テクスチャの破棄
-----------------------------------------------------------------------------*/
void CTextureManager::UnloadAll(void)
{
	for (auto it = m_Texture_Map.begin(); it != m_Texture_Map.end(); ++it)
	{
		if (it->second.Texture == NULL) continue;

		it->second.Texture->Release();	//	解放
		it->second.Texture = NULL;
	}

	m_Texture_Map.clear();	//	全要素の削除
}
