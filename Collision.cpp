/*=============================================================================

		衝突判定[ Collision.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/06/11
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/27
=============================================================================*/

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Collision.h"

/*-----------------------------------------------------------------------------
 関数名:	bool CCollisionRectangle::Judge(const D3DXVECTOR3 OtherPos, const D3DXVECTOR3 OtherSize)
 引数:		const D3DXVECTOR3 OtherPos		物体Bの座標
			const D3DXVECTOR3 OtherSize		物体Bの大きさ
 戻り値:	衝突した	return true;
			衝突しない  return false;
 説明:		矩形の衝突判定
-----------------------------------------------------------------------------*/
bool CCollisionRectangle::Judge(const D3DXVECTOR3 OtherPos, const D3DXVECTOR3 OtherSize)
{

	float x[] = { m_Pos.x , m_Pos.x + m_Size.x , OtherPos.x , OtherPos.x + OtherSize.x };
	float y[] = { m_Pos.y , m_Pos.y + m_Size.y , OtherPos.y , OtherPos.y + OtherSize.y };

	//	衝突判定
	if( x[ 0 ] < x[ 3 ] && x[ 2 ] < x[ 1 ] && y[ 0 ] < y[ 3 ] && y[ 2 ] < y[ 1 ] ) return true;

	return false;
}

/*-----------------------------------------------------------------------------
 関数名:	bool CCollisionCircle::Judge(const D3DXVECTOR3 OtherPos, const float OtherRadius)
 引数:		const D3DXVECTOR3 OtherPos	物体Bの座標
			const float OtherRadius		物体Bの半径
 戻り値:	衝突した	return true;
			衝突しない  return false;
 説明:		円の衝突判定
-----------------------------------------------------------------------------*/
bool CCollisionCircle::Judge(const D3DXVECTOR3 OtherPos, const float OtherRadius)
{
	//	座標の計算
	float Pos[] = { ( OtherPos.x - m_Pos.x ) * ( OtherPos.x - m_Pos.x ) ,
					( OtherPos.y - m_Pos.y ) * ( OtherPos.y - m_Pos.y ) };

	//	半径の計算
	float Radius = ( m_Radius + OtherRadius ) * ( m_Radius + OtherRadius );

	//	衝突判定
	if( Pos[ 0 ] + Pos[ 1 ] <= Radius ) return true;

	return false;
}

/*-----------------------------------------------------------------------------
 関数名:	bool CCollisionSphere::Judge(const D3DXVECTOR3 OtherPos, const float OtherRadius)
 引数:		const D3DXVECTOR3 OtherPos	物体Bの座標
			const float OtherRadius		物体Bの半径
 戻り値:	衝突した	return true;
			衝突しない  return false;
 説明:		球の衝突判定
-----------------------------------------------------------------------------*/
bool CCollisionSphere::Judge(const D3DXVECTOR3 OtherPos, const float OtherRadius)
{

	//	座標の計算
	float Pos[] = { ( OtherPos.x - m_Pos.x ) * ( OtherPos.x - m_Pos.x ) ,
					( OtherPos.y - m_Pos.y ) * ( OtherPos.y - m_Pos.y ) ,
					( OtherPos.z - m_Pos.z ) * ( OtherPos.z - m_Pos.z ) };

	//	半径の計算
	float Radius = ( m_Radius + OtherRadius ) * ( m_Radius + OtherRadius );

	//	衝突判定
	if( Pos[ 0 ] + Pos[ 1 ] + Pos[ 2 ] <= Radius ) return true;

	return false;
}