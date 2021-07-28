/*=============================================================================

		���w�n�֐�[ Mathematics.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/07/20
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/17
=============================================================================*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Mathematics.h"

/*-----------------------------------------------------------------------------
	�}�N����`
-----------------------------------------------------------------------------*/
#define PI ((float)3.141592654)	//	�~����
#define DEGREETORADIAN ( degree ) ((degree) * (PI / 180.0f))//	�p�x�����߂�
#define RADIANTODEGREE ( radian ) ((radian) * (180.0f / PI))//	�x�����߂�

/*-----------------------------------------------------------------------------
�֐���:		float CAngle2Vector::Angle2Vector(D3DXVECTOR3 VectorB)
����:		D3DXVECTOR3 VectorB		�x�N�g��B
�߂�l:		return angle;			�p�x
����:		�p�x�����߂�
-----------------------------------------------------------------------------*/
float CAngle2Vector::Angle2Vector(D3DXVECTOR3 VectorB)
{
	//	���������߂�
	float len1 = D3DXVec3Length(&m_VectorA);
	float len2 = D3DXVec3Length(&VectorB);

	//	�p�x�����߂�
	float angle = (float)(acos(D3DXVec3Dot(&VectorB, &m_VectorA) / (len1*len2)));

	return angle;
}

/*-----------------------------------------------------------------------------
 �֐���:	CAstroidCurve::CAstroidCurve(D3DXVECTOR3 op, float rotvalue, float radius)
 ����:		D3DXVECTOR3 op		���_
			float rotvalue		�p�x�ω���
			float radius		���a
 �߂�l:	
 ����:		�R���X�g���N�^
-----------------------------------------------------------------------------*/
CAstroidCurve::CAstroidCurve(D3DXVECTOR3 op, float rotvalue, float radius)
{
	m_OriginPoint = op;		//	���_

	m_Rot = 0.0f;			//	�p�x
	m_RotValue = rotvalue;	//	�p�x�ω���
	m_Radius = radius;		//	���a
}

/*-----------------------------------------------------------------------------
�֐���:		D3DXVECTOR3 CAstroidCurve::AstroidCurve()
����:
�߂�l:		return pos;		���W
����:		�A�X�e���C�h�Ȑ��v�Z
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
�֐���:		CInvoluteCurve::CInvoluteCurve(D3DXVECTOR3 op, float rotvalue, float radius)
����:		D3DXVECTOR3 op		���_
			float rotvalue		�p�x�ω���
			float radius		���a
�߂�l:
����:		�R���X�g���N�^
-----------------------------------------------------------------------------*/
CInvoluteCurve::CInvoluteCurve(D3DXVECTOR3 op, float rotvalue, float radius)
{
	m_OriginPoint = op;		//	���_

	m_Rot = 0.0f;			//	�p�x
	m_RotValue = rotvalue;	//	�p�x�ω���
	m_Radius = radius;		//	���a
}

/*-----------------------------------------------------------------------------
�֐���:		D3DXVECTOR3 CInvoluteCurve::InvoluteCurve(void)
����:
�߂�l:		return pos;		���W
����:		�C���{�����[�g�Ȑ��v�Z
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