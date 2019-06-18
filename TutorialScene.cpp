/*=============================================================================

		チュートリアルシーン[ TutorialScene.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/09/01
------------------------------------------------------------------------------- 
	■　更新日
		2017/09/01
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
#include "Scene.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "SpriteBillboard.h"
#include "SpriteModeX.h"
#include "Mode.h"
#include "Fade.h"
#include "GameScene.h"
#include "TutorialScene.h"
#include "FadeLogo.h"
#include "MeshDome.h"
#include "Ground.h"
#include "House.h"
#include "player.h"
#include "Target.h"

/*-----------------------------------------------------------------------------
 関数名:	
 引数:		
 戻り値:	
 説明:		
-----------------------------------------------------------------------------*/
void CTutorialScene::Init(void)
{

	//	テクスチャの取得
	CTextureManager* TextureManager = CManager::GetTextureManager();

	//	テクスチャのロード
	TextureManager->Load(CTextureManager::TEX_GROUND);
	TextureManager->Load(CTextureManager::TEX_TUTORIAL);
	TextureManager->Load(CTextureManager::TEX_SKYDOME);
	TextureManager->Load(CTextureManager::TEX_PUSH_BUTTOM3);
	TextureManager->Load(CTextureManager::TEX_TARGET);

	ObjectCreate();	//	オブジェクトの生成
}

/*-----------------------------------------------------------------------------
関数名:		void CGameScene::Uninit(void)
引数:
戻り値:
説明:		終了
-----------------------------------------------------------------------------*/
void CTutorialScene::Uninit(void)
{
	//	テクスチャ管理の取得
	CTextureManager* TextureManager = CManager::GetTextureManager();


	TextureManager->UnloadAll();	//	全テクスチャの破棄

	CScene::ReleaseAll();	//	全オブジェクトの解放
}

/*-----------------------------------------------------------------------------
関数名:		void CGameScene::Update(void)
引数:
戻り値:
説明:		更新
-----------------------------------------------------------------------------*/
void CTutorialScene::Update(void)
{

	ConditionalTransition();	//	遷移条件

	CScene::UpdateAll();		//	全オブジェクトの更新
}

/*-----------------------------------------------------------------------------
関数名:		void CGameScene::Draw(void)
引数:
戻り値:
説明:		描画
-----------------------------------------------------------------------------*/
void CTutorialScene::Draw(void)
{
	CScene::DrawAll();	//	全オブジェクトの描画
}

/*-----------------------------------------------------------------------------
関数名:		void CGameScene::ConditionalTransition(void)
引数:
戻り値:
説明:		遷移条件
-----------------------------------------------------------------------------*/
void CTutorialScene::ConditionalTransition(void)
{
	CInputMouse* pMouse = CManager::GetMouse();

	if (pMouse->GetKeyTrigger(1))
	{
		CFade::SetFade(CFade::FADE_OUT, new CGameScene);

		CSound* sound = CManager::GetSound();

		sound->Stop(CSound::SOUND_LABEL_BGM_TITLE);

		sound->Play(CSound::SOUND_LABEL_SE_MODE);
	}
}

/*-----------------------------------------------------------------------------
関数名:		void CGameScene::ObjectCreate(void)
引数:
戻り値:
説明:		オブジェクトの生成
-----------------------------------------------------------------------------*/
void CTutorialScene::ObjectCreate(void)
{
	CMeshDome::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), 100, 100, 800.0f, CMeshDome::IDXBACK_DRAW_INV_CLOCKWISE, CTextureManager::TEX_SKYDOME);

	m_Ground = CGround::Create(0);
	m_Ground->SetTextureID(CTextureManager::TEX_GROUND);
	m_Ground->SetPosition(D3DXVECTOR3(0.0f, -10.0f, 0.0f));
	m_Ground->SetNormal(D3DXVECTOR3(50.0f, 50.0f, 50.0f));
	m_Ground->SetSize(D3DXVECTOR3(600.0f, 0.0f, 600.0f));
	m_Ground->SetScroll(0.0f);

	m_bg = CSprite2D::Create(5);
	m_bg->SetTextureID(CTextureManager::TEX_TUTORIAL);
	m_bg->SetSize(D3DXVECTOR2(SCREEN_WIDTH, SCREEN_HEIGHT));

	m_Push_Buttom = CFadeRogo::Create(5);
	m_Push_Buttom->SetTextureID(CTextureManager::TEX_PUSH_BUTTOM3);
	m_Push_Buttom->SetPosition(D3DXVECTOR3(450.0f, 480.0f, 0.0f));
	m_Push_Buttom->SetSize(D3DXVECTOR2(300.0f, 130.0f));
	m_Push_Buttom->SetUpLimit(1.0f);
	m_Push_Buttom->SetLowerLimit(0.0f);

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

	m_Target = CTarget::Create();
	m_Target->SetTextureID(CTextureManager::TEX_TARGET);
	m_Target->SetPosition(D3DXVECTOR3(0.0f, 0.0f, -50.0f));
	m_Target->SetSize(D3DXVECTOR2(5.0f, 10.0f));

	CPlayer::Create();

}