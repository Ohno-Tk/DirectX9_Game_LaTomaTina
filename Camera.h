/*=============================================================================

カメラ[ Camera.h ]

-------------------------------------------------------------------------------
■　製作者
大野拓也

■　作成日
2017/08/25
-------------------------------------------------------------------------------
■　更新日
2017/08/25
=============================================================================*/

#ifndef _CAMERA_H_
#define _CAMERA_H_

/*-----------------------------------------------------------------------------
マクロ
-----------------------------------------------------------------------------*/
#define ENABLE_PEOC_DEBUG_CAMERA
#undef ENABLE_PEOC_DEBUG_CAMERA

/*-----------------------------------------------------------------------------
クラス
-----------------------------------------------------------------------------*/
class CCamera
{
public:
	CCamera();	//	コンストラクタ

	void Update(void);		//	更新

							//void NormalizeCamera(void);	//	カメラの正規化を計算

							//	Setter
	void SetPosition(const D3DXVECTOR3 Pos);		//	座標
	void SetPositionAt(const D3DXVECTOR3 PosAt);	//	注視点

													//	Getter

	D3DXVECTOR3 GetCameraPos(void) { return m_Pos; }	//	カメラ座標
	D3DXVECTOR3 GetCameraPosAt(void) { return m_LookAt; }	//	注視点
	D3DXVECTOR3 GetCameraVecUp(void) { return m_VecUp; }	//	上の視点
	D3DXVECTOR3 GetForwardVector(void) { return m_VecAtCa; }	//	前方向ベクトル

	D3DXVECTOR2 GetCameraRotVH(void) { return D3DXVECTOR2(m_fRotV, m_fRotH); }

	//	行列
	const D3DXMATRIX GetMtxView(void)const { return m_MtxView; };	//	ビュー行列
	const D3DXMATRIX &GetMtxProjection(void)const { return m_mtxProj; }	//	プロジェクション行列

																		//	逆行列
	const D3DXMATRIX GetInversedView(void)const;	//	ビュー行列

	void SwitchFrag(void) { m_bUp = !m_bUp; }
	bool GetFrag(void) { return m_bUp; }

private:
	void InputProcess(void);

	void SetProjection(void);	//	プロジェクションのセット

private:
	D3DXVECTOR3 m_LookAt;			//注視点座標
	D3DXVECTOR3 m_Pos;				//視点位置
	D3DXVECTOR3 m_VecUp;			//カメラ上方向
	D3DXVECTOR3 m_VecAtCa;			//注視点からカメラへのベクトル
									//D3DXVECTOR3 m_NorVecAtCa;		//↑の正規化
	float m_fLength;				//注視点からカメラへの距離
	float m_fRotV;					//XZ平面軸の角度
	float m_fRotH;					//カメラと注視点のXZ平面上の角度(Y軸回転)
	float m_fFov;					//視野角、画角(ズームイン、ズームアウト)


	D3DXMATRIX m_MtxView;		//	ビュー行列マトリクス
	D3DXMATRIX m_mtxProj;		//	プロジェクション行列マトリクス

	bool m_bUp;
};
#endif
