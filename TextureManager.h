/*=============================================================================

		�e�N�X�`���Ǘ�[ TextureManager.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/24
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/24
=============================================================================*/

#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include <unordered_map>

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CTextureManager
{
public:
	enum TEXTURE_ID
	{
		TEX_FADE = 0,	//	�t�F�[�h
		TEX_PUSH_BUTTOM,	//	�v�b�V���{�^��
		TEX_TITLE_LOGO,	//	�^�C�g�����S
		TEX_GROUND,		//	�n��
		TEX_PLAYERUI,
		TEX_NUMBER,		//	����
		TEX_WAVE_LOGO,	//	�E�F�[�u���S
		TEX_SKYDOME,	//	�X�J�C�h�[��
		TEX_GAME_UI,
		TEX_LOGO,
		TEX_PUSH_BUTTOM2,
		TEX_TUTORIAL,
		TEX_PUSH_BUTTOM3,
		TEX_TARGET,
		TEX_START,
		TEX_GOAL,
		MAX_TEXTURES	//	�ő�
	};
	struct TEXTUREINFO
	{
		LPDIRECT3DTEXTURE9 Texture;	//	�e�N�X�`���̃|�C���^
		D3DXVECTOR2 Size;			//	�傫��
		D3DXVECTOR2 Div;			//	������
	};

	void Load(TEXTURE_ID Id, D3DXVECTOR2 Div = D3DXVECTOR2(1.f, 1.f));	//	�e�N�X�`���̃��[�h
	void UnloadAll(void);	//	�S�e�N�X�`���̔j��

	//	Getter
	TEXTUREINFO GetTextureInfo(TEXTURE_ID Id) { return m_TextureInfo[Id]; }	//	�e�N�X�`�����

private:
	static const LPSTR m_FilePass[MAX_TEXTURES];	//	�t�@�C���p�X

	TEXTUREINFO m_TextureInfo[MAX_TEXTURES];	//	�e�N�X�`�����

	std::unordered_map< TEXTURE_ID, TEXTUREINFO > m_Texture_Map;
};
#endif
