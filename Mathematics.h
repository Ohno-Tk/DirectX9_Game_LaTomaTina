/*=============================================================================

		���w�n�֐�[ Mathematics.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/07/20
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/17
=============================================================================*/

#ifndef _MATHEMATICS_H_
#define _MATHEMATICS_H_

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CAngle2Vector
{	//	2�̃x�N�g���̂Ȃ��p�x�����߂�
public:
	//	�R���X�g���N�^
	CAngle2Vector(D3DXVECTOR3 VectorA) :m_VectorA(VectorA) {}

	//	�p�x�����߂�
	float Angle2Vector(D3DXVECTOR3 VectorB);
private:
	D3DXVECTOR3 m_VectorA;	//	�x�N�g��A
};

class CAstroidCurve
{	//	�A�X�e���C�h�Ȑ�
public:
	//	�R���X�g���N�^
	CAstroidCurve(D3DXVECTOR3 op, float rotvalue, float radius);

	//	�A�X�e���C�h�Ȑ��v�Z
	D3DXVECTOR3 AstroidCurve();

private:
	D3DXVECTOR3 m_OriginPoint;	//	���_

	float m_Rot;				//	�p�x
	float m_RotValue;			//	�p�x�ω���
	float m_Radius;				//	���a
};

class CInvoluteCurve
{	//	�C���{�����[�g�Ȑ�
public:
	//	�R���X�g���N�^
	CInvoluteCurve(D3DXVECTOR3 op, float rotvalue, float radius);

	//	�C���{�����[�g�Ȑ��v�Z
	D3DXVECTOR3 InvoluteCurve(void);

private:
	D3DXVECTOR3 m_OriginPoint;	//	���_

	float m_Rot;				//	�p�x
	float m_RotValue;			//	�p�x�ω���
	float m_Radius;				//	���a
};

#endif
