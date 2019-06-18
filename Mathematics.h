/*=============================================================================

		数学系関数[ Mathematics.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/07/20
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/17
=============================================================================*/

#ifndef _MATHEMATICS_H_
#define _MATHEMATICS_H_

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CAngle2Vector
{	//	2つのベクトルのなす角度を求める
public:
	//	コンストラクタ
	CAngle2Vector(D3DXVECTOR3 VectorA) :m_VectorA(VectorA) {}

	//	角度を求める
	float Angle2Vector(D3DXVECTOR3 VectorB);
private:
	D3DXVECTOR3 m_VectorA;	//	ベクトルA
};

class CAstroidCurve
{	//	アステロイド曲線
public:
	//	コンストラクタ
	CAstroidCurve(D3DXVECTOR3 op, float rotvalue, float radius);

	//	アステロイド曲線計算
	D3DXVECTOR3 AstroidCurve();

private:
	D3DXVECTOR3 m_OriginPoint;	//	原点

	float m_Rot;				//	角度
	float m_RotValue;			//	角度変化量
	float m_Radius;				//	半径
};

class CInvoluteCurve
{	//	インボリュート曲線
public:
	//	コンストラクタ
	CInvoluteCurve(D3DXVECTOR3 op, float rotvalue, float radius);

	//	インボリュート曲線計算
	D3DXVECTOR3 InvoluteCurve(void);

private:
	D3DXVECTOR3 m_OriginPoint;	//	原点

	float m_Rot;				//	角度
	float m_RotValue;			//	角度変化量
	float m_Radius;				//	半径
};

#endif
