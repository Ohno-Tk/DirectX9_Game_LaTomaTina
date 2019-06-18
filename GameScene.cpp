/*=============================================================================

		ゲームシーン[ GameScene.cpp ]

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
#include "Input.h"
#include "Sound.h"
#include "Manager.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "Mode.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "Fade.h"
#include "Scene.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "SpriteModeX.h"
#include "Motion.h"
#include "Ground.h"
#include "PlayerUi.h"
#include "Number2D.h"
#include "KillCont.h"
#include "MeshDome.h"
#include "House.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "player.h"

/*-----------------------------------------------------------------------------
	マクロ定義
-----------------------------------------------------------------------------*/
CKillCount* CGameScene::m_Kill = NULL;
CPlayer* CGameScene::m_Player = NULL;
bool CGameScene::m_Clear = false;
bool CGameScene::m_GameOver = false;

CGameScene::CGameScene()
{
	m_Ground = NULL;
	m_PlayerUI = NULL;
	m_Kill_Logo = NULL;
	m_EnemyManager = NULL;

	for (int i = 0; i < MAX_HOUSE; i++)
	{
		m_House[i] =NULL;
	}

	m_Clear = false;
	m_GameOver = false;
	m_ModeChange = false;
}

/*-----------------------------------------------------------------------------
関数名:		void CGameScene::Init(void)
引数:
戻り値:
説明:		初期化
-----------------------------------------------------------------------------*/
void CGameScene::Init(void)
{
	CSound* sound = CManager::GetSound();

	sound->Play(CSound::SOUND_LABEL_BGM_TITLE);

	//	テクスチャの取得
	CTextureManager* TextureManager = CManager::GetTextureManager();

	//	テクスチャのロード
	TextureManager->Load(CTextureManager::TEX_GROUND);
	TextureManager->Load(CTextureManager::TEX_PLAYERUI,D3DXVECTOR2(8.0f,1.0f));
	TextureManager->Load(CTextureManager::TEX_NUMBER);
	TextureManager->Load(CTextureManager::TEX_WAVE_LOGO);
	TextureManager->Load(CTextureManager::TEX_SKYDOME);
	TextureManager->Load(CTextureManager::TEX_GAME_UI);
	TextureManager->Load(CTextureManager::TEX_START);
	TextureManager->Load(CTextureManager::TEX_GOAL);


	ObjectCreate();	//	オブジェクトの生成
}

/*-----------------------------------------------------------------------------
関数名:		void CGameScene::Uninit(void)
引数:
戻り値:
説明:		終了
-----------------------------------------------------------------------------*/
void CGameScene::Uninit(void)
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
void CGameScene::Update(void)
{

	m_EnemyManager->Update();

	ConditionalTransition();	//	遷移条件

	CScene::UpdateAll();		//	全オブジェクトの更新
}

/*-----------------------------------------------------------------------------
関数名:		void CGameScene::Draw(void)
引数:
戻り値:
説明:		描画
-----------------------------------------------------------------------------*/
void CGameScene::Draw(void)
{
	CScene::DrawAll();	//	全オブジェクトの描画
}

/*-----------------------------------------------------------------------------
関数名:		void CGameScene::ConditionalTransition(void)
引数:
戻り値:
説明:		遷移条件
-----------------------------------------------------------------------------*/
void CGameScene::ConditionalTransition(void)
{
	//	キーボードの取得
	CInputKeyboard* KeyBoard = CManager::GetKeyboard();

	//	サウンドの取得
	CSound *sound = CManager::GetSound();

	if (KeyBoard->GetKeyTrigger(DIK_SPACE))
	{
		CFade::SetFade(CFade::FADE_OUT, new CResultScene);

		CManager::SetTomatoCount(m_Kill->GetCount());
	}

	if (!m_ModeChange)
	{
		if (m_Clear || m_GameOver)
		{
			CFade::SetFade(CFade::FADE_OUT, new CResultScene);

			CManager::SetTomatoCount(m_Kill->GetCount());

			sound->Stop(CSound::SOUND_LABEL_BGM_TITLE);

			m_ModeChange = true;
		}
	}
}

/*-----------------------------------------------------------------------------
関数名:		void CGameScene::ObjectCreate(void)
引数:
戻り値:
説明:		オブジェクトの生成
-----------------------------------------------------------------------------*/
void CGameScene::ObjectCreate(void)
{
	CMeshDome::Create(D3DXVECTOR3(0.0f, -15.0f, 0.0f), 100, 100, 800.0f, CMeshDome::IDXBACK_DRAW_INV_CLOCKWISE, CTextureManager::TEX_SKYDOME);

	m_Ground = CGround::Create(0);
	m_Ground->SetTextureID(CTextureManager::TEX_GROUND);
	m_Ground->SetPosition(D3DXVECTOR3(0.0f, -10.0f, 0.0f));
	m_Ground->SetSize(D3DXVECTOR3(600.0f, 0.0f, 600.0f));
	m_Ground->SetNormal(D3DXVECTOR3(50.0f, 50.0f, 50.0f));
	m_Ground->SetScroll(0.005f);

	m_PlayerUI = CPlayerUI::Create(4);
	m_PlayerUI->SetTextureID(CTextureManager::TEX_PLAYERUI);
	m_PlayerUI->SetPosition(D3DXVECTOR3(580.0f, 200.0f, 0.0f));
	m_PlayerUI->SetSize(D3DXVECTOR2(35.0f, 35.0f));

	m_Game_UI = CSprite2D::Create(4);
	m_Game_UI->SetTextureID(CTextureManager::TEX_GAME_UI);
	m_Game_UI->SetPosition(D3DXVECTOR3(590.0f,200.0f,0.0f));
	m_Game_UI->SetSize(D3DXVECTOR2(150.0f, 300.0f));

	m_Start_Logo = CSprite2D::Create(4);
	m_Start_Logo->SetTextureID(CTextureManager::TEX_START);
	m_Start_Logo->SetPosition(D3DXVECTOR3(690.0f, 190.0f, 0.0f));
	m_Start_Logo->SetSize(D3DXVECTOR2(100.0f, 50.0f));

	m_Goal_Logo = CSprite2D::Create(4);
	m_Goal_Logo->SetTextureID(CTextureManager::TEX_GOAL);
	m_Goal_Logo->SetPosition(D3DXVECTOR3(690.0f, 460.0f, 0.0f));
	m_Goal_Logo->SetSize(D3DXVECTOR2(100.0f, 50.0f));

	int i = 0;

	for (i = 0; i < MAX_HOUSE; i++)
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

		m_House[i]->SetPosition(D3DXVECTOR3(4.0f, 5.0f, -97.5f - (2.5f * i)));
		m_House[i]->SetRotation(D3DXVECTOR3(0.0f, 90.0f, 0.0f));
		m_House[i]->SetSpeed(0.05f);
	}

	for (int j = 0; j < MAX_HOUSE; j++)
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

		m_House[j]->SetPosition(D3DXVECTOR3(-4.0f, 5.0f, -97.5f - (2.5f * j)));
		m_House[j]->SetRotation(D3DXVECTOR3(0.0f, -90.0f, 0.0f));
		m_House[j]->SetSpeed(0.05f);
	}

	m_EnemyManager = new CEnemyManager;

	m_Kill_Logo = CSprite2D::Create(4);
	m_Kill_Logo->SetTextureID(CTextureManager::TEX_WAVE_LOGO);
	m_Kill_Logo->SetPosition(D3DXVECTOR3(10.0f, 10.0f,0.0f));
	m_Kill_Logo->SetSize(D3DXVECTOR2(250.0f, 100.0f));

	m_Kill = CKillCount::Create(D3DXVECTOR2(130.0f, 130.0f), D3DXVECTOR2(50.0f, 50.0f));

	m_Player = CPlayer::Create();
}