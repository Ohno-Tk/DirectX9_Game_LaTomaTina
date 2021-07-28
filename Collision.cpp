/*=============================================================================

		�Փ˔���[ Collision.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/06/11
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/27
=============================================================================*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Collision.h"

/*-----------------------------------------------------------------------------
 �֐���:	bool CCollisionRectangle::Judge(const D3DXVECTOR3 OtherPos, const D3DXVECTOR3 OtherSize)
 ����:		const D3DXVECTOR3 OtherPos		����B�̍��W
			const D3DXVECTOR3 OtherSize		����B�̑傫��
 �߂�l:	�Փ˂���	return true;
			�Փ˂��Ȃ�  return false;
 ����:		��`�̏Փ˔���
-----------------------------------------------------------------------------*/
bool CCollisionRectangle::Judge(const D3DXVECTOR3 OtherPos, const D3DXVECTOR3 OtherSize)
{

	float x[] = { m_Pos.x , m_Pos.x + m_Size.x , OtherPos.x , OtherPos.x + OtherSize.x };
	float y[] = { m_Pos.y , m_Pos.y + m_Size.y , OtherPos.y , OtherPos.y + OtherSize.y };

	//	�Փ˔���
	if( x[ 0 ] < x[ 3 ] && x[ 2 ] < x[ 1 ] && y[ 0 ] < y[ 3 ] && y[ 2 ] < y[ 1 ] ) return true;

	return false;
}

/*-----------------------------------------------------------------------------
 �֐���:	bool CCollisionCircle::Judge(const D3DXVECTOR3 OtherPos, const float OtherRadius)
 ����:		const D3DXVECTOR3 OtherPos	����B�̍��W
			const float OtherRadius		����B�̔��a
 �߂�l:	�Փ˂���	return true;
			�Փ˂��Ȃ�  return false;
 ����:		�~�̏Փ˔���
-----------------------------------------------------------------------------*/
bool CCollisionCircle::Judge(const D3DXVECTOR3 OtherPos, const float OtherRadius)
{
	//	���W�̌v�Z
	float Pos[] = { ( OtherPos.x - m_Pos.x ) * ( OtherPos.x - m_Pos.x ) ,
					( OtherPos.y - m_Pos.y ) * ( OtherPos.y - m_Pos.y ) };

	//	���a�̌v�Z
	float Radius = ( m_Radius + OtherRadius ) * ( m_Radius + OtherRadius );

	//	�Փ˔���
	if( Pos[ 0 ] + Pos[ 1 ] <= Radius ) return true;

	return false;
}

/*-----------------------------------------------------------------------------
 �֐���:	bool CCollisionSphere::Judge(const D3DXVECTOR3 OtherPos, const float OtherRadius)
 ����:		const D3DXVECTOR3 OtherPos	����B�̍��W
			const float OtherRadius		����B�̔��a
 �߂�l:	�Փ˂���	return true;
			�Փ˂��Ȃ�  return false;
 ����:		���̏Փ˔���
-----------------------------------------------------------------------------*/
bool CCollisionSphere::Judge(const D3DXVECTOR3 OtherPos, const float OtherRadius)
{

	//	���W�̌v�Z
	float Pos[] = { ( OtherPos.x - m_Pos.x ) * ( OtherPos.x - m_Pos.x ) ,
					( OtherPos.y - m_Pos.y ) * ( OtherPos.y - m_Pos.y ) ,
					( OtherPos.z - m_Pos.z ) * ( OtherPos.z - m_Pos.z ) };

	//	���a�̌v�Z
	float Radius = ( m_Radius + OtherRadius ) * ( m_Radius + OtherRadius );

	//	�Փ˔���
	if( Pos[ 0 ] + Pos[ 1 ] + Pos[ 2 ] <= Radius ) return true;

	return false;
}