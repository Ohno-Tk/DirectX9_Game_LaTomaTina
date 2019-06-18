/*=============================================================================

		リザルトシーン[ ResultScene.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/25
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/25
=============================================================================*/

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Input.h"
#include "Sound.h"
#include "Manager.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "Mode.h"
#include "Fade.h"
#include "ResultScene.h"
#include "TitleScene.h"
#include "Scene.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "SpriteModeX.h"
#include "FadeLogo.h"
#include "Ground.h"
#include "MeshDome.h"
#include "Number2D.h"
#include "KillCont.h"
#include "House.h"

/*-----------------------------------------------------------------------------
関数名:		void CResultScene::Init(void)
引数:
戻り値:
説明:		初期化
-----------------------------------------------------------------------------*/
void CResultScene::Init(void)
{
	CSound* sound = CManager::GetSound();

	sound->Play(CSound::SOUND_LABEL_SE_GAMECLEAR);

	//	テクスチャの取得
	CTextureManager* TextureManager = CManager::GetTextureManager();

	//	テクスチャのロード
	TextureManager->Load(CTextureManager::TEX_GROUND);
	TextureManager->Load(CTextureManager::TEX_TITLE_LOGO);
	TextureManager->Load(CTextureManager::TEX_PUSH_BUTTOM2);
	TextureManager->Load(CTextureManager::TEX_SKYDOME);
	TextureManager->Load(CTextureManager::TEX_NUMBER);
	TextureManager->Load(CTextureManager::TEX_WAVE_LOGO);
	TextureManager->Load(CTextureManager::TEX_LOGO,D3DXVECTOR2(1.0f,4.0f));

	ObjectCreate();	//	オブジェクトの生成
}

/*-----------------------------------------------------------------------------
関数名:		void CResultScene::Uninit(void)
引数:
戻り値:
説明:		終了
-----------------------------------------------------------------------------*/
void CResultScene::Uninit(void)
{
	//	テクスチャの取得
	CTextureManager* TextureManager = CManager::GetTextureManager();


	TextureManager->UnloadAll();	//	全テクスチャの破棄

	CScene::ReleaseAll();	//	全オブジェクトの解放
}

/*-----------------------------------------------------------------------------
関数名:		void CResultScene::Update(void)
引数:
戻り値:
説明:		更新
-----------------------------------------------------------------------------*/
void CResultScene::Update(void)
{
	ConditionalTransition();	//	遷移条件

	CScene::UpdateAll();	//	全オブジェクトの更新
}

/*-----------------------------------------------------------------------------
関数名:		void CResultScene::Draw(void)
引数:
戻り値:
説明:		描画
-----------------------------------------------------------------------------*/
void CResultScene::Draw(void)
{
	CScene::DrawAll();	//	全オブジェクトの描画
}

/*-----------------------------------------------------------------------------
関数名:		void CResultScene::ConditionalTransition(void)
引数:
戻り値:
説明:		遷移条件
-----------------------------------------------------------------------------*/
void CResultScene::ConditionalTransition(void)
{
	CInputMouse* pMouse = CManager::GetMouse();

	if (pMouse->GetKeyTrigger(0) || pMouse->GetKeyTrigger(1))
	{
		CFade::SetFade(CFade::FADE_OUT, new CTitleScene);

		CSound* sound = CManager::GetSound();

		sound->Stop(CSound::SOUND_LABEL_BGM_TITLE);

		sound->Play(CSound::SOUND_LABEL_SE_MODE);
	}
}

/*-----------------------------------------------------------------------------
関数名:		void CResultScene::ObjectCreate(void)
引数:
戻り値:
説明:		オブジェクトの生成
-----------------------------------------------------------------------------*/
void CResultScene::ObjectCreate(void)
{
	CMeshDome::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), 100, 100, 800.0f, CMeshDome::IDXBACK_DRAW_INV_CLOCKWISE, CTextureManager::TEX_SKYDOME);

	m_Push_Buttom = CFadeRogo::Create(4);
	m_Push_Buttom->SetTextureID(CTextureManager::TEX_PUSH_BUTTOM2);
	m_Push_Buttom->SetPosition(D3DXVECTOR3(400.0f, 500.0f, 0.0f));
	m_Push_Buttom->SetSize(D3DXVECTOR2(300.0f, 130.0f));
	m_Push_Buttom->SetUpLimit(1.0f);
	m_Push_Buttom->SetLowerLimit(0.0f);

	m_Ground = CGround::Create(0);
	m_Ground->SetTextureID(CTextureManager::TEX_GROUND);
	m_Ground->SetPosition(D3DXVECTOR3(0.0f, -10.0f, 0.0f));
	m_Ground->SetNormal(D3DXVECTOR3(50.0f, 50.0f, 50.0f));
	m_Ground->SetSize(D3DXVECTOR3(600.0f, 0.0f, 600.0f));
	m_Ground->SetScroll(0.0f);

	m_Kill_Logo = CSprite2D::Create(4);
	m_Kill_Logo->SetTextureID(CTextureManager::TEX_WAVE_LOGO);
	m_Kill_Logo->SetPosition(D3DXVECTOR3(100.0f, 200.0f, 0.0f));
	m_Kill_Logo->SetSize(D3DXVECTOR2(250.0f, 100.0f));

	m_Kill = CKillCount::Create(D3DXVECTOR2(600.0f, 200.0f), D3DXVECTOR2(100.0f, 100.0f));
	m_Kill->SetCount(CManager::GetTomatoCount());

	m_Result_Logo = CSprite2D::Create(3);
	m_Result_Logo->SetTextureID(CTextureManager::TEX_LOGO);
	m_Result_Logo->SetSize(D3DXVECTOR2(300.0, 50.0f));
	m_Result_Logo->SetTexturePattern(2);

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

		m_House[i]->SetPosition(D3DXVECTOR3(6.0f, 5.0f, -97.5f + (2.5f * i)));
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

		m_House[j]->SetPosition(D3DXVECTOR3(-6.0f, 5.0f, -97.5f + (2.5f * j)));
		m_House[j]->SetRotation(D3DXVECTOR3(0.0f, -90.0f, 0.0f));
		m_House[j]->SetSpeed(0.0f);
	}
}