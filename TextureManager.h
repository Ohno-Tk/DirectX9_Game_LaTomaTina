/*=============================================================================

		テクスチャ管理[ TextureManager.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/24
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/24
=============================================================================*/

#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include <unordered_map>

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CTextureManager
{
public:
	enum TEXTURE_ID
	{
		TEX_FADE = 0,	//	フェード
		TEX_PUSH_BUTTOM,	//	プッシュボタン
		TEX_TITLE_LOGO,	//	タイトルロゴ
		TEX_GROUND,		//	地面
		TEX_PLAYERUI,
		TEX_NUMBER,		//	数字
		TEX_WAVE_LOGO,	//	ウェーブロゴ
		TEX_SKYDOME,	//	スカイドーム
		TEX_GAME_UI,
		TEX_LOGO,
		TEX_PUSH_BUTTOM2,
		TEX_TUTORIAL,
		TEX_PUSH_BUTTOM3,
		TEX_TARGET,
		TEX_START,
		TEX_GOAL,
		MAX_TEXTURES	//	最大
	};
	struct TEXTUREINFO
	{
		LPDIRECT3DTEXTURE9 Texture;	//	テクスチャのポインタ
		D3DXVECTOR2 Size;			//	大きさ
		D3DXVECTOR2 Div;			//	分割数
	};

	void Load(TEXTURE_ID Id, D3DXVECTOR2 Div = D3DXVECTOR2(1.f, 1.f));	//	テクスチャのロード
	void UnloadAll(void);	//	全テクスチャの破棄

	//	Getter
	TEXTUREINFO GetTextureInfo(TEXTURE_ID Id) { return m_TextureInfo[Id]; }	//	テクスチャ情報

private:
	static const LPSTR m_FilePass[MAX_TEXTURES];	//	ファイルパス

	TEXTUREINFO m_TextureInfo[MAX_TEXTURES];	//	テクスチャ情報

	std::unordered_map< TEXTURE_ID, TEXTUREINFO > m_Texture_Map;
};
#endif
