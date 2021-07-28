/*=============================================================================

		�Փ˔���[ Collision.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/06/11
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/27
=============================================================================*/

#ifndef _COLLISION_H_
#define _COLLISION_H_

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CCollisionRectangle
{	//	��`
public:
	//	�R���X�g���N�^
	CCollisionRectangle(const D3DXVECTOR3 Pos , const D3DXVECTOR3 Size):m_Pos(Pos), m_Size(Size){}

	//	�Փ˔���
	bool Judge(const D3DXVECTOR3 OtherPos, const D3DXVECTOR3 OtherSize);

private:
	D3DXVECTOR3 m_Pos;	//	���W
	D3DXVECTOR3 m_Size;	//	�傫��
};

class CCollisionCircle
{	//	�~
public:
	//	�R���X�g���N�^
	CCollisionCircle(const D3DXVECTOR3 Pos, const float Radius):m_Pos(Pos), m_Radius(Radius){}

	//	�~�̏Փ˔���
	bool Judge(const D3DXVECTOR3 OtherPos, const float OtherRadius);

private:
	D3DXVECTOR3 m_Pos;	//	���W
	float m_Radius;		//	���a
};

class CCollisionSphere
{	//	��
public:
	//	�R���X�g���N�^
	CCollisionSphere(const D3DXVECTOR3 Pos, const float Radius):m_Pos(Pos), m_Radius(Radius){}

	//	���̏Փ˔���
	bool Judge(const D3DXVECTOR3 OtherPos, const float OtherRadius);

private:
	D3DXVECTOR3 m_Pos;	//	���W
	float m_Radius;		//	���a
};
#endif
