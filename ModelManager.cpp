/*=============================================================================

		モデル管理[ ModelManager.cpp ]

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
	scanf のwarning防止
-----------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include <string.h>
#include <assert.h>
#include "DirectX.h"
#include "ModelManager.h"

/*-----------------------------------------------------------------------------
	マクロ定義
-----------------------------------------------------------------------------*/
#define TEXTURE_PATH "data/TEXTURE/"

/*-----------------------------------------------------------------------------
関数名:	
引数:		
戻り値:
説明:		
-----------------------------------------------------------------------------*/
void CModelManager::Init(void)
{
	Load(MODEL_PATH"tomato.x");
	Load(MODEL_PATH"house.x");
	Load(MODEL_PATH"house2.x");
	Load(MODEL_PATH"taihou.x");

	Load(MODEL_PATH"Player/00_head.x");
	Load(MODEL_PATH"Player/01_body.x");
	Load(MODEL_PATH"Player/02_Hip.x");
	Load(MODEL_PATH"Player/03_JointAll_R.x");
	Load(MODEL_PATH"Player/04_Arm01_R.x");
	Load(MODEL_PATH"Player/05_Arm02_R.x");
	Load(MODEL_PATH"Player/06_Wrist_R.x");
	Load(MODEL_PATH"Player/07_Hand_R.x");
	Load(MODEL_PATH"Player/08_Hand_L.x");
	Load(MODEL_PATH"Player/09_LegJointAll.x");
	Load(MODEL_PATH"Player/10_Leg01.x");
	Load(MODEL_PATH"Player/11_Leg02.x");
	Load(MODEL_PATH"Player/12_foot.x");
	Load(MODEL_PATH"Player/13_Arm01_L.x");
	Load(MODEL_PATH"Player/14_Arm02_L.x");
	Load(MODEL_PATH"Player/15_JointAll_L.x");
	Load(MODEL_PATH"Player/16_Wrist_L.x");
}

/*-----------------------------------------------------------------------------
 関数名:	
 引数:		
 戻り値:	
 説明:		モデルのロード
-----------------------------------------------------------------------------*/
void CModelManager::Load(char* Name)
{
	//	同じファイルが存在するかのチェック
	auto it = m_Model_Map.find(Name);

	if (it == m_Model_Map.end())
	{	//	存在しなかったら

		HRESULT hr;

		//	デバイスの取得
		LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();

		// Xファイルの読み込み
		hr = D3DXLoadMeshFromX(Name,		//	ファイル名
			D3DXMESH_SYSTEMMEM,
			Device,					//	デバイス
			NULL,					//	隣接バッファ
			&m_Model.BuffMat,		//	マテリアル情報を格納
			NULL,
			&m_Model.NumMat,		//	マテリアル数
			&m_Model.Mesh);			//	メッシュ

		if (FAILED(hr))
		{

			MessageBox(NULL, "モデルが読み込めませんでした", "Model.cpp", MB_OK | MB_ICONHAND);
			return;
		}


		//	テクスチャの読み込み
		m_Model.Mat = (D3DXMATERIAL*)m_Model.BuffMat->GetBufferPointer();
		m_Model.Texture = new LPDIRECT3DTEXTURE9[m_Model.NumMat];
		for (int i = 0; i < (int)m_Model.NumMat; i++)
		{

			m_Model.Texture[i] = NULL;

			if (m_Model.Mat[i].pTextureFilename)
			{

				char filePath[MAX_PATH];
				strcpy(filePath, TEXTURE_PATH);
				strcat(filePath, m_Model.Mat[i].pTextureFilename);

				hr = D3DXCreateTextureFromFile(Device, filePath, &m_Model.Texture[i]);

				if (FAILED(hr))
				{

					MessageBox(NULL, "テクスチャが読み込めませんでした", "Model.cpp", MB_OK | MB_ICONHAND);
					return;
				}
			}
		}


		//	キーと値を連結させる
		m_Model_Map[Name] = m_Model;
	}
}

/*-----------------------------------------------------------------------------
関数名:		void CModelManager::UnloadAll(void)
引数:
戻り値:
説明:		全モデルの破棄
-----------------------------------------------------------------------------*/
void CModelManager::UnloadAll(void)
{
	for (auto it = m_Model_Map.begin(); it != m_Model_Map.end(); ++it)
	{

		//	テクスチャの解放
		for (unsigned int i = 0; i < it->second.NumMat; i++)
		{

			if (it->second.Texture[i] == NULL) continue;

			it->second.Texture[i]->Release();	//	解放

		}

		delete[] it->second.Texture;	//	解放

		if (it->second.Mesh != NULL)    it->second.Mesh->Release();	//	解放

		if (it->second.BuffMat != NULL) it->second.BuffMat->Release();	//	解放

	}

	m_Model_Map.clear();	//	全要素の削除
}

/*-----------------------------------------------------------------------------
関数名:		
引数:		
戻り値:
説明:		モデルIDの取得
-----------------------------------------------------------------------------*/
const CModelManager::MODEL_PARAM CModelManager::GetModelParam(char* Name)const
{
	//	初期化
	MODEL_PARAM Model;
	Model.BuffMat = NULL;
	Model.Mat = 0;
	Model.Mesh = NULL;
	Model.NumMat = 0;

	//	ファイルが存在するかのチェック
	auto it = m_Model_Map.find(Name);


	if (it != m_Model_Map.end())
	{	//	存在していたら

		return it->second;

	}

	assert(!"[ ModelManager.cpp ]   モデルが取得できませんでした");

	return Model;
}