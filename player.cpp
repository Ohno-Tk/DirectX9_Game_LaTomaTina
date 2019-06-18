#include "DirectX.h"
#include "ModelManager.h"
#include "Scene.h"
#include "SpriteModeX.h"
#include "player.h"
#include "Input.h"
#include "Manager.h"
#include "Camera.h"
#include "bullet.h"
#include "Mode.h"
#include "GameScene.h"

#define MODEL_ID MODEL_PATH"tomato.x"

int CPlayer::m_HP = 3;

CPlayer* CPlayer::Create(void) {
	CPlayer* pPlayer = new CPlayer(3);

	pPlayer->m_FileName = MODEL_ID;
	pPlayer->Init();

	return pPlayer;
}

void CPlayer::Init() {
	m_Position = D3DXVECTOR3(0.0f, 8.0f, -98.0f);	//カメラ-POS_CAMERA_TO_PLAYER
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	回転
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//	拡大率

	m_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_HP = 3;
}

void CPlayer::Uninit() {
	CScene::Release();
}

void CPlayer::Update() {
	CInputMouse* pMouse = CManager::GetMouse();
	CCamera* pCamera = CManager::GetCamera();

	//if (pMouse->GetKeyTrigger(1)) {
	//	pCamera->SwitchFrag();
	//}
	//if (pCamera->GetFrag()) {
	//	m_Position = D3DXVECTOR3(0.0f, 8.0f, -98.0f);
	//}
	//else {
	//	m_Position = D3DXVECTOR3(0.0f, 5.0f, -98.0f);
	//}

//	if (pMouse->GetKeyPress(CInputMouse::MOUSE_LEFT) && pCamera->GetFrag())
	if (pMouse->GetKeyTrigger(CInputMouse::MOUSE_LEFT) && pCamera->GetFrag())
	{
		D3DXVECTOR3 cameraVec = pCamera->GetForwardVector();
		D3DXVec3Normalize(&cameraVec, &cameraVec);

		CBullet::Create(m_offset, cameraVec);
	}

}
void CPlayer::Draw() {
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
void CPlayer::SetWorld(LPDIRECT3DDEVICE9 Device)
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


	CCamera* pCamera = CManager::GetCamera();
	D3DXVECTOR2 cameraVH = pCamera->GetCameraRotVH();
	D3DXVECTOR3 offset;
	D3DXVECTOR3 cameraRot, cameraPos;

	cameraPos = pCamera->GetCameraPos();
	offset = cameraPos - m_Position;

	D3DXMATRIX mtxOffset, mtxCameraRot, mtxCameraTrans;

	D3DXMatrixTranslation(&mtxOffset, offset.x, offset.y, offset.z);

	cameraRot.y = -cameraVH.y - D3DXToRadian(90);
	cameraRot.x = cameraVH.x * sinf(cameraVH.y);
	cameraRot.z = cameraVH.x * cosf(cameraVH.y);

	D3DXMatrixRotationYawPitchRoll(&mtxCameraRot, cameraRot.y, cameraRot.x, cameraRot.z);


	D3DXMatrixTranslation(&mtxCameraTrans, cameraPos.x, cameraPos.y, cameraPos.z);


	m_offset = cameraPos - m_Position;
	D3DXVec3TransformCoord(&m_offset, &m_offset, &mtxOffset);
	D3DXVec3TransformCoord(&m_offset, &m_offset, &mtxCameraRot);
	D3DXVec3TransformCoord(&m_offset, &m_offset, &mtxCameraTrans);


	//	掛けてあげる
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxOffset);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxCameraRot);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxCameraTrans);
	//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxOffset);


	//	デバイスにワールド変換行列を設定
	Device->SetTransform(D3DTS_WORLD, &mtxWorld);
}


void CPlayer::SubHp(void)
{
	m_HP--;

	if (m_HP <= 0)
	{
		m_HP = 0;
		CGameScene::GameOver();
	}
}