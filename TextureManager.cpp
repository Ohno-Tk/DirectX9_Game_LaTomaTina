/*=============================================================================

		�e�N�X�`���Ǘ�[ TextureManager.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/24
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/24
=============================================================================*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "TextureManager.h"

/*-----------------------------------------------------------------------------
	�}�N����`
-----------------------------------------------------------------------------*/
#define TEXTURE_PATH "data/TEXTURE/"

/*-----------------------------------------------------------------------------
	�ÓI�ϐ�
-----------------------------------------------------------------------------*/
const LPSTR CTextureManager::m_FilePass[] = {
	TEXTURE_PATH"Fade.jpg",	//	�t�F�[�h
	TEXTURE_PATH"TITLE/title_text.png",	//	�v�b�V���{�^��
	TEXTURE_PATH"TITLE/title.png",	//	�^�C�g�����S
	TEXTURE_PATH"GAME/Ground.jpg",	//	�n��
	TEXTURE_PATH"GAME/runningman000.png",
	TEXTURE_PATH"GAME/number000.png",	//	����
	TEXTURE_PATH"GAME/Kill_Logo.png",	//	kill���S
	TEXTURE_PATH"GAME/sky001.jpg",	//	�X�J�C�h�[��
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
�֐���:		void CTextureManager::Load(TEXTURE_ID Id, D3DXVECTOR2 Div)
����:		TEXTURE_ID Id		�e�N�X�`����ID
�߂�l:
����:		�e�N�X�`���̃��[�h
-----------------------------------------------------------------------------*/
void CTextureManager::Load(TEXTURE_ID Id, D3DXVECTOR2 Div)
{
	m_TextureInfo[Id].Div = Div;

	//	�����t�@�C�������݂��邩�̌���
	auto it = m_Texture_Map.find(Id);

	if (it == m_Texture_Map.end())
	{	//	���݂��Ȃ�������

		HRESULT hr;

		//	�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();

		//	�e�N�X�`���̓ǂݍ���
		hr = D3DXCreateTextureFromFile(Device, m_FilePass[Id], &m_TextureInfo[Id].Texture);

		if (FAILED(hr))
		{
			MessageBox(NULL, "�e�N�X�`�����ǂݍ��߂܂���ł���", "Texture.cpp", MB_OK | MB_ICONHAND);
			return;
		}

		//�e�N�X�`���ڍ׏��擾
		D3DXIMAGE_INFO ImageInfo;
		D3DXGetImageInfoFromFile(m_FilePass[Id], &ImageInfo);
		m_TextureInfo[Id].Size.x = ImageInfo.Width / Div.x;
		m_TextureInfo[Id].Size.y = ImageInfo.Height / Div.y;


		//	�L�[�ƒl��A��������
		m_Texture_Map[Id] = m_TextureInfo[Id];
	}
}

/*-----------------------------------------------------------------------------
�֐���:		void CTextureManager::UnloadAll(void)
����:
�߂�l:
����:		�S�e�N�X�`���̔j��
-----------------------------------------------------------------------------*/
void CTextureManager::UnloadAll(void)
{
	for (auto it = m_Texture_Map.begin(); it != m_Texture_Map.end(); ++it)
	{
		if (it->second.Texture == NULL) continue;

		it->second.Texture->Release();	//	���
		it->second.Texture = NULL;
	}

	m_Texture_Map.clear();	//	�S�v�f�̍폜
}
