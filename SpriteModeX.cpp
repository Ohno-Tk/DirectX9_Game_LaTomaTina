/*=============================================================================

		Xモデル描画[ SpriteModeLX.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/25
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/27
=============================================================================*/

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Manager.h"
#include "ModelManager.h"
#include "Scene.h"
#include "SpriteModeX.h"

/*-----------------------------------------------------------------------------
 関数名:	CSpriteModeLX::CSpriteModeLX(int Priolity)
 引数:		int Priolity	優先度
 戻り値:	
 説明:		コンストラクタ
-----------------------------------------------------------------------------*/
CSpriteModeLX::CSpriteModeLX(int Priolity) :CScene(Priolity)
{
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	回転
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//	拡大率
	m_FileName = NULL;
}

/*-----------------------------------------------------------------------------
関数名:		CSpriteModeLX* CSpriteModeLX::Create(int Priolity)
引数:		int Priolity			優先度
戻り値:
説明:		生成
-----------------------------------------------------------------------------*/
CSpriteModeLX* CSpriteModeLX::Create(int Priolity)
{
	CSpriteModeLX* spriteModelX;

	spriteModelX = new CSpriteModeLX(Priolity);

	spriteModelX->Init();	//	初期化

	return spriteModelX;
}

/*-----------------------------------------------------------------------------
関数名:		void CSpriteModeLX::Draw(void)
引数:
戻り値:
説明:		描画
-----------------------------------------------------------------------------*/
void CSpriteModeLX::Draw(void)
{
	D3DMATERIAL9 matDef;

	//	デバイスの取得
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();

	//	モデル管理の取得
	CModelManager *ModelManager = CManager::GetModelManager();

	m_ModelParam = ModelManager->GetModelParam(m_FileName);

	//	ワールド座標変換
	SetWorld(Device);

	//	現在デバイスに設定されているマテリアル情報の取得
	Device->GetMaterial(&matDef);


	// 現在のマテリアルを取得
	Device->GetMaterial(&matDef);


	// マテリアルへのポインタを取得
	m_ModelParam.Mat = (D3DXMATERIAL*)m_ModelParam.BuffMat->GetBufferPointer();


	for (int nCntMat = 0; nCntMat < (int)m_ModelParam.NumMat; nCntMat++)
	{
		// デバイスにマテリアルの設定
		Device->SetMaterial(&m_ModelParam.Mat[nCntMat].MatD3D);

		// テクスチャの設定
		Device->SetTexture(0, m_ModelParam.Texture[nCntMat]);

		// 描画
		m_ModelParam.Mesh->DrawSubset(nCntMat);
	}

	// マテリアルを元に戻す
	Device->SetMaterial(&matDef);
}

/*-----------------------------------------------------------------------------
関数名:		void CSpriteModeLX::SetWorld(LPDIRECT3DDEVICE9 Device)
引数:		LPDIRECT3DDEVICE9 Device	デバイス
戻り値:
説明:		ワールド座標変換
-----------------------------------------------------------------------------*/
void CSpriteModeLX::SetWorld(LPDIRECT3DDEVICE9 Device)
{
	D3DXMATRIX mtxWorld, mtxScl, mtxRot, mtxPos;

	D3DXMatrixIdentity(&mtxWorld);	//	行列を単位行列にする

	//	拡大行列を作る
	D3DXMatrixScaling(&mtxScl,	//拡大行列が作られる
		m_Scale.x,	//	X軸拡大
		m_Scale.y,	//	Y軸拡大
		m_Scale.z);	//	Z軸拡大

	//	回転行列を作る
	D3DXMatrixRotationYawPitchRoll(&mtxRot,	//	回転行列が作られる
		D3DXToRadian(m_Rotation.y), //	Y軸回転
		D3DXToRadian(m_Rotation.x), //	X軸回転
		D3DXToRadian(m_Rotation.z)); //	Z軸回転

	//	平行移動行列を作る
	D3DXMatrixTranslation(&mtxPos,
		m_Position.x,	//	X軸移動
		m_Position.y,	//	Y軸移動
		m_Position.z);	//	Z軸移動


	//	掛けてあげる
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxPos);

	//	デバイスにワールド変換行列を設定
	Device->SetTransform(D3DTS_WORLD, &mtxWorld);
}