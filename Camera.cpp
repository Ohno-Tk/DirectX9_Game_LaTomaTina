/*=============================================================================

�J����[ Camera.cpp ]

-------------------------------------------------------------------------------

���@�쐬��
2017/08/25
-------------------------------------------------------------------------------
���@�X�V��
2017/08/25
=============================================================================*/

/*-----------------------------------------------------------------------------
�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Camera.h"
#include "Input.h"
#include "Manager.h"

/*-----------------------------------------------------------------------------
�}�N����`
-----------------------------------------------------------------------------*/
#define CAMERA_NEAR ( 1.0f )	//	near
#define CAMERA_FAR ( 2000.0f )	//	far

#define CAMERA_MOVE_SPEED (2.0f)	//	�ړ���


#define CAMERA_RANGE_V_MAX		(10.0f)
#define CAMERA_RANGE_V_MIN		(-20.0f)
#define CAMERA_RANGE_H_MAX		(30.0f)
#define CAMERA_RANGE_H_MIN		(-30.0f)


/*-----------------------------------------------------------------------------
�֐���:	CCamera::CCamera()
����:
�߂�l:
����:		�R���X�g���N�^
-----------------------------------------------------------------------------*/
CCamera::CCamera()
{
	m_Pos = D3DXVECTOR3(0.0f, 0.5f, -100.0f);	//	�J�������W
	m_LookAt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//	�����_
	m_VecUp = D3DXVECTOR3(0.0f, 1.0f, 0.0f);			//	��̎��_

	m_VecAtCa = m_LookAt - m_Pos;
	m_fLength = D3DXVec3Length(&m_VecAtCa);		//	����

	m_fRotH = 0.0f;
	m_fRotV = 0.0f;
	//XY���ʏ�ł̓�_�Ԃ̊p�x�����߂�
	m_fRotH = atan2f(m_VecAtCa.z, m_VecAtCa.x);	//����]
												//XZ���ʏ��Y���W�̊p�x�����߂�
	m_fRotV = atan2f(m_VecAtCa.y, sqrtf((m_VecAtCa.x * m_VecAtCa.x) + (m_VecAtCa.z * m_VecAtCa.z)));		//�c��]

	m_fFov = D3DX_PI / 3.0f;					//��p60

												//	�s���P�ʍs��ɂ���
	D3DXMatrixIdentity(&m_MtxView);	//	�r���[�s��}�g���N�X
	D3DXMatrixIdentity(&m_mtxProj);	//	�v���W�F�N�V�����s��}�g���N�X

	m_bUp = true;
}

/*-----------------------------------------------------------------------------
�֐���:		void CCamera::Update(void)
����:
�߂�l:
����:		�X�V
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

	SetProjection();	//	�v���W�F�N�V�����̃Z�b�g
}

/*-----------------------------------------------------------------------------
�֐���:		void CCamera::SetProjection(void)
����:
�߂�l:
����:		�v���W�F�N�V�����̃Z�b�g
-----------------------------------------------------------------------------*/
void CCamera::SetProjection(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();

	//	���[���h���W�ϊ�
	//	���[���h�}�g���N�X�̍쐬
	D3DXMATRIX mtxWorld;

	D3DXMatrixIdentity(&mtxWorld);	//	�s���P�ʍs��ɂ���

									//	�f�o�C�X�Ƀ��[���h�ϊ��s���ݒ�
	Device->SetTransform(D3DTS_WORLD, &mtxWorld);

	//	�r���[���W�ϊ�
	D3DXMatrixLookAtLH(&m_MtxView, &m_Pos, &m_LookAt, &m_VecUp);

	//	�f�o�C�X�Ƀr���[�ϊ��s���ݒ�
	Device->SetTransform(D3DTS_VIEW, &m_MtxView);

	//	�v���W�F�N�V�����ϊ�


	//	�p�[�X�y�N�e�B�u�s��
	D3DXMatrixPerspectiveFovLH(&m_mtxProj,
		m_fFov,	//	��p
		(float)SCREEN_WIDTH / SCREEN_HEIGHT,	//	�A�X�y�N�g��
		CAMERA_NEAR,	//	near	�l����0�ȉ��ɂ��Ȃ�
		CAMERA_FAR);	//	far

						//	�f�o�C�X�Ƀv���W�F�N�V�����ϊ��s���ݒ�
	Device->SetTransform(D3DTS_PROJECTION, &m_mtxProj);

}


/*-----------------------------------------------------------------------------
�֐���:		void CCamera::SetPosition(const D3DXVECTOR3 Pos)
����:		const D3DXVECTOR3 Pos	���W
�߂�l:
����:		�J�������W�̃Z�b�g
-----------------------------------------------------------------------------*/
void CCamera::SetPosition(const D3DXVECTOR3 Pos) {
	m_Pos = Pos;
}

/*-----------------------------------------------------------------------------
�֐���:		void CCamera::SetPositionAt(const D3DXVECTOR3 PosAt)
����:		const D3DXVECTOR3 PosAt		�����_
�߂�l:
����:		�����_�̃Z�b�g
-----------------------------------------------------------------------------*/
void CCamera::SetPositionAt(const D3DXVECTOR3 PosAt) {
	m_LookAt = PosAt;
}


/*-----------------------------------------------------------------------------
�֐���:		const D3DXMATRIX CCamera::GetInversedView(void)const
����:
�߂�l:		return mtxViewInverse;	�t�s��r���[
����:		�t�s��r���[�̎擾
-----------------------------------------------------------------------------*/
const D3DXMATRIX CCamera::GetInversedView(void)const
{
	D3DXMATRIX mtxViewInverse;

	//	�]�u�s��
	D3DXMatrixTranspose(&mtxViewInverse, &m_MtxView);

	//	���s�ړ��������J�b�g
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

	//�����_����J�����ւ̃x�N�g�����X�V����
	m_VecAtCa.x = (float)(cos(m_fRotH) * cos(m_fRotV) * m_fLength);
	m_VecAtCa.y = (float)(sin(m_fRotV) * m_fLength);
	m_VecAtCa.z = (float)(sin(m_fRotH) * cos(m_fRotV) * m_fLength);

	//�����_
	m_LookAt = m_Pos + m_VecAtCa;
}

