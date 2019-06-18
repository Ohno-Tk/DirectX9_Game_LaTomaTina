/*=============================================================================

カメラ[ Camera.cpp ]

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
#include "Camera.h"
#include "Input.h"
#include "Manager.h"

/*-----------------------------------------------------------------------------
マクロ定義
-----------------------------------------------------------------------------*/
#define CAMERA_NEAR ( 1.0f )	//	near
#define CAMERA_FAR ( 2000.0f )	//	far

#define CAMERA_MOVE_SPEED (2.0f)	//	移動量


#define CAMERA_RANGE_V_MAX		(10.0f)
#define CAMERA_RANGE_V_MIN		(-20.0f)
#define CAMERA_RANGE_H_MAX		(30.0f)
#define CAMERA_RANGE_H_MIN		(-30.0f)


/*-----------------------------------------------------------------------------
関数名:	CCamera::CCamera()
引数:
戻り値:
説明:		コンストラクタ
-----------------------------------------------------------------------------*/
CCamera::CCamera()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.5f, -100.0f);	//	カメラ座標
	m_LookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	注視点
	m_VecUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//	上の視点

	m_VecAtCa = m_LookAt - m_Pos;
	m_fLength = D3DXVec3Length(&m_VecAtCa);		//	長さ

	m_fRotH = 0.0f;
	m_fRotV = 0.0f;
	//XY平面上での二点間の角度を求める
	m_fRotH = atan2f(m_VecAtCa.z, m_VecAtCa.x);	//横回転
												//XZ平面上とY座標の角度を求める
	m_fRotV = atan2f(m_VecAtCa.y, sqrtf((m_VecAtCa.x * m_VecAtCa.x) + (m_VecAtCa.z * m_VecAtCa.z)));		//縦回転

	m_fFov = D3DX_PI / 3.0f;					//画角60

												//	行列を単位行列にする
	D3DXMatrixIdentity(&m_MtxView);	//	ビュー行列マトリクス
	D3DXMatrixIdentity(&m_mtxProj);	//	プロジェクション行列マトリクス

	m_bUp = true;
}

/*-----------------------------------------------------------------------------
関数名:		void CCamera::Update(void)
引数:
戻り値:
説明:		更新
-----------------------------------------------------------------------------*/
void CCamera::Update(void)
{
	//#ifdef ENABLE_PEOC_DEBUG_CAMERA
	//	CameraOperation();
	//#endif

	InputProcess();


	if (m_bUp)
	{
		m_Pos = D3DXVECTOR3(0.0f, 7.0f, -100.0f);
	}
	else {
		m_Pos = D3DXVECTOR3(0.0f, 5.0f, -100.0f);
	}

	SetProjection();	//	プロジェクションのセット
}

/*-----------------------------------------------------------------------------
関数名:		void CCamera::SetProjection(void)
引数:
戻り値:
説明:		プロジェクションのセット
-----------------------------------------------------------------------------*/
void CCamera::SetProjection(void)
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();

	//	ワールド座標変換
	//	ワールドマトリクスの作成
	D3DXMATRIX mtxWorld;

	D3DXMatrixIdentity(&mtxWorld);	//	行列を単位行列にする

									//	デバイスにワールド変換行列を設定
	Device->SetTransform(D3DTS_WORLD, &mtxWorld);

	//	ビュー座標変換
	D3DXMatrixLookAtLH(&m_MtxView, &m_Pos, &m_LookAt, &m_VecUp);

	//	デバイスにビュー変換行列を設定
	Device->SetTransform(D3DTS_VIEW, &m_MtxView);

	//	プロジェクション変換


	//	パースペクティブ行列
	D3DXMatrixPerspectiveFovLH(&m_mtxProj,
		m_fFov,	//	画角
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,	//	アスペクト比
		CAMERA_NEAR,	//	near	値を絶対0以下にしない
		CAMERA_FAR);	//	far

						//	デバイスにプロジェクション変換行列を設定
	Device->SetTransform(D3DTS_PROJECTION, &m_mtxProj);

}


/*-----------------------------------------------------------------------------
関数名:		void CCamera::SetPosition(const D3DXVECTOR3 Pos)
引数:		const D3DXVECTOR3 Pos	座標
戻り値:
説明:		カメラ座標のセット
-----------------------------------------------------------------------------*/
void CCamera::SetPosition(const D3DXVECTOR3 Pos) {
	m_Pos = Pos;
}

/*-----------------------------------------------------------------------------
関数名:		void CCamera::SetPositionAt(const D3DXVECTOR3 PosAt)
引数:		const D3DXVECTOR3 PosAt		注視点
戻り値:
説明:		注視点のセット
-----------------------------------------------------------------------------*/
void CCamera::SetPositionAt(const D3DXVECTOR3 PosAt) {
	m_LookAt = PosAt;
}


/*-----------------------------------------------------------------------------
関数名:		const D3DXMATRIX CCamera::GetInversedView(void)const
引数:
戻り値:		return mtxViewInverse;	逆行列ビュー
説明:		逆行列ビューの取得
-----------------------------------------------------------------------------*/
const D3DXMATRIX CCamera::GetInversedView(void)const
{
	D3DXMATRIX mtxViewInverse;

	//	転置行列
	D3DXMatrixTranspose(&mtxViewInverse, &m_MtxView);

	//	平行移動成分をカット
	mtxViewInverse._14 = 0.0f;
	mtxViewInverse._24 = 0.0f;
	mtxViewInverse._34 = 0.0f;

	return mtxViewInverse;
}


void CCamera::InputProcess(void) {
	CInputMouse* pMouse = CManager::GetMouse();

	LONG ax = pMouse->GetAxisX();
	LONG ay = pMouse->GetAxisY();
	//LONG az = pMouse->GetAxisZ();

	m_fRotH -= ax / 180.0f;
	m_fRotV -= ay / 180.0f;

	if (m_fRotV < D3DXToRadian(CAMERA_RANGE_V_MIN)) {
		m_fRotV = D3DXToRadian(CAMERA_RANGE_V_MIN);
	}
	if (m_fRotV > D3DXToRadian(CAMERA_RANGE_V_MAX)) {
		m_fRotV = D3DXToRadian(CAMERA_RANGE_V_MAX);
	}
	if (m_fRotH < D3DX_PI / 2 + D3DXToRadian(CAMERA_RANGE_H_MIN)) {
		m_fRotH = D3DX_PI / 2 + D3DXToRadian(CAMERA_RANGE_H_MIN);
	}
	if (m_fRotH > D3DX_PI / 2 + D3DXToRadian(CAMERA_RANGE_H_MAX)) {
		m_fRotH = D3DX_PI / 2 + D3DXToRadian(CAMERA_RANGE_H_MAX);
	}

	//注視点からカメラへのベクトルを更新する
	m_VecAtCa.x = (float)(cos(m_fRotH) * cos(m_fRotV) * m_fLength);
	m_VecAtCa.y = (float)(sin(m_fRotV) * m_fLength);
	m_VecAtCa.z = (float)(sin(m_fRotH) * cos(m_fRotV) * m_fLength);

	//注視点
	m_LookAt = m_Pos + m_VecAtCa;
}

