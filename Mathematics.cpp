/*=============================================================================

		数学系関数[ Mathematics.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/07/20
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/17
=============================================================================*/

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Mathematics.h"

/*-----------------------------------------------------------------------------
	マクロ定義
-----------------------------------------------------------------------------*/
#define PI ((float)3.141592654)	//	円周率
#define DEGREETORADIAN ( degree ) ((degree) * (PI / 180.0f))//	角度を求める
#define RADIANTODEGREE ( radian ) ((radian) * (180.0f / PI))//	度を求める

/*-----------------------------------------------------------------------------
関数名:		float CAngle2Vector::Angle2Vector(D3DXVECTOR3 VectorB)
引数:		D3DXVECTOR3 VectorB		ベクトルB
戻り値:		return angle;			角度
説明:		角度を求める
-----------------------------------------------------------------------------*/
float CAngle2Vector::Angle2Vector(D3DXVECTOR3 VectorB)
{
	//	長さを求める
	float len1 = D3DXVec3Length(&m_VectorA);
	float len2 = D3DXVec3Length(&VectorB);

	//	角度を求める
	float angle = (float)(acos(D3DXVec3Dot(&VectorB, &m_VectorA) / (len1*len2)));

	return angle;
}

/*-----------------------------------------------------------------------------
 関数名:	CAstroidCurve::CAstroidCurve(D3DXVECTOR3 op, float rotvalue, float radius)
 引数:		D3DXVECTOR3 op		原点
			float rotvalue		角度変化量
			float radius		半径
 戻り値:	
 説明:		コンストラクタ
-----------------------------------------------------------------------------*/
CAstroidCurve::CAstroidCurve(D3DXVECTOR3 op, float rotvalue, float radius)
{
	m_OriginPoint = op;		//	原点

	m_Rot = 0.0f;			//	角度
	m_RotValue = rotvalue;	//	角度変化量
	m_Radius = radius;		//	半径
}

/*-----------------------------------------------------------------------------
関数名:		D3DXVECTOR3 CAstroidCurve::AstroidCurve()
引数:
戻り値:		return pos;		座標
説明:		アステロイド曲線計算
-----------------------------------------------------------------------------*/
D3DXVECTOR3 CAstroidCurve::AstroidCurve()
{

	D3DXVECTOR3 pos;
	
	float Cos3 = cosf(D3DXToRadian(m_Rot))*cosf(D3DXToRadian(m_Rot))*cosf(D3DXToRadian(m_Rot));
	float Sin3 = sinf(D3DXToRadian(m_Rot))*sinf(D3DXToRadian(m_Rot))*sinf(D3DXToRadian(m_Rot));

	pos.x = Cos3 * m_Radius + m_OriginPoint.x;
	pos.y = Sin3 * m_Radius + m_OriginPoint.y;
	pos.z = m_OriginPoint.z;

	m_Rot += m_RotValue;

	return pos;
}

/*-----------------------------------------------------------------------------
関数名:		CInvoluteCurve::CInvoluteCurve(D3DXVECTOR3 op, float rotvalue, float radius)
引数:		D3DXVECTOR3 op		原点
			float rotvalue		角度変化量
			float radius		半径
戻り値:
説明:		コンストラクタ
-----------------------------------------------------------------------------*/
CInvoluteCurve::CInvoluteCurve(D3DXVECTOR3 op, float rotvalue, float radius)
{
	m_OriginPoint = op;		//	原点

	m_Rot = 0.0f;			//	角度
	m_RotValue = rotvalue;	//	角度変化量
	m_Radius = radius;		//	半径
}

/*-----------------------------------------------------------------------------
関数名:		D3DXVECTOR3 CInvoluteCurve::InvoluteCurve(void)
引数:
戻り値:		return pos;		座標
説明:		インボリュート曲線計算
-----------------------------------------------------------------------------*/
D3DXVECTOR3 CInvoluteCurve::InvoluteCurve(void)
{

	D3DXVECTOR3 pos;

	pos.x = (m_Radius * (sinf(D3DXToRadian(m_Rot)) - m_Rot * cosf(D3DXToRadian(m_Rot))) * -1) + m_OriginPoint.x;
	pos.y = (m_Radius * (cosf(D3DXToRadian(m_Rot)) + m_Rot * sinf(D3DXToRadian(m_Rot))) * -1) + m_OriginPoint.y;
	pos.z = m_OriginPoint.z;

	m_Rot += m_RotValue;

	return pos;
}