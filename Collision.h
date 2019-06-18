/*=============================================================================

		衝突判定[ Collision.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/06/11
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/27
=============================================================================*/

#ifndef _COLLISION_H_
#define _COLLISION_H_

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CCollisionRectangle
{	//	矩形
public:
	//	コンストラクタ
	CCollisionRectangle(const D3DXVECTOR3 Pos , const D3DXVECTOR3 Size):m_Pos(Pos), m_Size(Size){}

	//	衝突判定
	bool Judge(const D3DXVECTOR3 OtherPos, const D3DXVECTOR3 OtherSize);

private:
	D3DXVECTOR3 m_Pos;	//	座標
	D3DXVECTOR3 m_Size;	//	大きさ
};

class CCollisionCircle
{	//	円
public:
	//	コンストラクタ
	CCollisionCircle(const D3DXVECTOR3 Pos, const float Radius):m_Pos(Pos), m_Radius(Radius){}

	//	円の衝突判定
	bool Judge(const D3DXVECTOR3 OtherPos, const float OtherRadius);

private:
	D3DXVECTOR3 m_Pos;	//	座標
	float m_Radius;		//	半径
};

class CCollisionSphere
{	//	球
public:
	//	コンストラクタ
	CCollisionSphere(const D3DXVECTOR3 Pos, const float Radius):m_Pos(Pos), m_Radius(Radius){}

	//	球の衝突判定
	bool Judge(const D3DXVECTOR3 OtherPos, const float OtherRadius);

private:
	D3DXVECTOR3 m_Pos;	//	座標
	float m_Radius;		//	半径
};
#endif
