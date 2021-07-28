/*=============================================================================

		�^�C�g���V�[��[ TitleScene.cpp ]

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
#include "Input.h"
#include "Sound.h"
#include "Manager.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "Mode.h"
#include "TitleScene.h"
#include "TutorialScene.h"
#include "Fade.h"
#include "Scene.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "SpriteModeX.h"
#include "FadeLogo.h"
#include "Ground.h"
#include "MeshDome.h"
#include "House.h"

/*-----------------------------------------------------------------------------
 �֐���:	void CTitleScene::Init(void)
 ����:		
 �߂�l:	
 ����:		������
-----------------------------------------------------------------------------*/
void CTitleScene::Init(void)
{

	CSound* sound = CManager::GetSound();

	sound->Play(CSound::SOUND_LABEL_BGM_TITLE);

	//	�e�N�X�`���Ǘ��̎擾
	CTextureManager* TextureManager = CManager::GetTextureManager();

	//	�e�N�X�`���̃��[�h
	TextureManager->Load(CTextureManager::TEX_GROUND);
	TextureManager->Load(CTextureManager::TEX_TITLE_LOGO);
	TextureManager->Load(CTextureManager::TEX_PUSH_BUTTOM);
	TextureManager->Load(CTextureManager::TEX_SKYDOME);

	ObjectCreate();	//	�I�u�W�F�N�g�̐���
}

/*-----------------------------------------------------------------------------
�֐���:		void CTitleScene::Uninit(void)
����:
�߂�l:
����:		�I��
-----------------------------------------------------------------------------*/
void CTitleScene::Uninit(void)
{
	//	�e�N�X�`���Ǘ��̎擾
	CTextureManager* TextureManager = CManager::GetTextureManager();

	TextureManager->UnloadAll();	//	�S�e�N�X�`���̔j��

	CScene::ReleaseAll();	//	�S�I�u�W�F�N�g�̉��
}

/*-----------------------------------------------------------------------------
�֐���:		void CTitleScene::Update(void)
����:
�߂�l:
����:		�X�V
-----------------------------------------------------------------------------*/
void CTitleScene::Update(void)
{

	ConditionalTransition();	//	�J�ڏ���

	CScene::UpdateAll();		//	�S�I�u�W�F�N�g�̍X�V
}

/*-----------------------------------------------------------------------------
�֐���:		void CTitleScene::Draw(void)
����:
�߂�l:
����:		�`��
-----------------------------------------------------------------------------*/
void CTitleScene::Draw(void)
{
	CScene::DrawAll();	//	�S�I�u�W�F�N�g�̕`��
}

/*-----------------------------------------------------------------------------
�֐���:		void CTitleScene::ConditionalTransition(void)
����:
�߂�l:
����:		�J�ڏ���
-----------------------------------------------------------------------------*/
void CTitleScene::ConditionalTransition(void)
{
	//	�L�[�{�[�h�̎擾
	CInputKeyboard* KeyBoard = CManager::GetKeyboard();

	if (KeyBoard->GetKeyTrigger(DIK_SPACE))
	{
		CFade::SetFade(CFade::FADE_OUT, new CTutorialScene);
	}

	CInputMouse* pMouse = CManager::GetMouse();

	if (pMouse->GetKeyTrigger(0)|| pMouse->GetKeyTrigger(1))
	{
		CFade::SetFade(CFade::FADE_OUT, new CTutorialScene);

		CSound* sound = CManager::GetSound();

		sound->Stop(CSound::SOUND_LABEL_BGM_TITLE);

		sound->Play(CSound::SOUND_LABEL_SE_MODE);
	}
}

/*-----------------------------------------------------------------------------
�֐���:		void CTitleScene::ObjectCreate(void)
����:
�߂�l:
����:		�I�u�W�F�N�g�̐���
-----------------------------------------------------------------------------*/
void CTitleScene::ObjectCreate(void)
{
	CMeshDome::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), 100, 100, 800.0f, CMeshDome::IDXBACK_DRAW_INV_CLOCKWISE, CTextureManager::TEX_SKYDOME);

	m_Title_Logo = CSprite2D::Create(4);
	m_Title_Logo->SetTextureID(CTextureManager::TEX_TITLE_LOGO);
	m_Title_Logo->SetPosition(D3DXVECTOR3(50.0f, 0.0f, 0.0f));
	m_Title_Logo->SetSize(D3DXVECTOR2(1392.0f * 0.5f, 888.0f * 0.5f));

	m_Push_Buttom = CFadeRogo::Create(4);
	m_Push_Buttom->SetTextureID(CTextureManager::TEX_PUSH_BUTTOM);
	m_Push_Buttom->SetPosition(D3DXVECTOR3(150.0f, 450.0f, 0.0f));
	m_Push_Buttom->SetSize(D3DXVECTOR2(1108.0f * 0.5f, 110.0f * 0.5f));
	m_Push_Buttom->SetUpLimit(1.0f);
	m_Push_Buttom->SetLowerLimit(0.0f);

	m_Ground = CGround::Create(0);
	m_Ground->SetTextureID(CTextureManager::TEX_GROUND);
	m_Ground->SetPosition(D3DXVECTOR3(0.0f, -10.0f, 0.0f));
	m_Ground->SetNormal(D3DXVECTOR3(50.0f, 50.0f, 50.0f));
	m_Ground->SetSize(D3DXVECTOR3(600.0f, 0.0f, 600.0f));
	m_Ground->SetScroll(0.0f);

	int i = 0;

	for (i = 0; i < 16; i++)
	{
		m_House[i] = CHouse::Create();

		int ID = rand() % 2;

		switch (ID)
		{
		case 0:
			m_House[i]->SetModel(MODEL_PATH"house.x");
			break;
		case 1:
			m_House[i]->SetModel(MODEL_PATH"house2.x");
			break;
		}

		m_House[i]->SetPosition(D3DXVECTOR3(4.0f, 5.0f, -97.5f + (2.5f * i)));
		m_House[i]->SetRotation(D3DXVECTOR3(0.0f, 90.0f, 0.0f));
		m_House[i]->SetSpeed(0.0f);
	}

	for (int j = 0; j < 16; j++)
	{
		m_House[j] = CHouse::Create();

		int ID = rand() % 2;

		switch (ID)
		{
		case 0:
			m_House[j]->SetModel(MODEL_PATH"house.x");
			break;
		case 1:
			m_House[j]->SetModel(MODEL_PATH"house2.x");
			break;
		}

		m_House[j]->SetPosition(D3DXVECTOR3(-4.0f, 5.0f, -97.5f + (2.5f * j)));
		m_House[j]->SetRotation(D3DXVECTOR3(0.0f, -90.0f, 0.0f));
		m_House[j]->SetSpeed(0.0f);
	}
}