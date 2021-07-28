/*=============================================================================

�J����[ Camera.h ]

-------------------------------------------------------------------------------

���@�쐬��
2017/08/25
-------------------------------------------------------------------------------
���@�X�V��
2017/08/25
=============================================================================*/

#ifndef _CAMERA_H_
#define _CAMERA_H_

/*-----------------------------------------------------------------------------
�}�N��
-----------------------------------------------------------------------------*/
#define ENABLE_PEOC_DEBUG_CAMERA
#undef ENABLE_PEOC_DEBUG_CAMERA

/*-----------------------------------------------------------------------------
�N���X
-----------------------------------------------------------------------------*/
class CCamera
{
public:
	CCamera();	//	�R���X�g���N�^

	void Update(void);		//	�X�V

							//void NormalizeCamera(void);	//	�J�����̐��K�����v�Z

							//	Setter
	void SetPosition(const D3DXVECTOR3 Pos);		//	���W
	void SetPositionAt(const D3DXVECTOR3 PosAt);	//	�����_

													//	Getter

	D3DXVECTOR3 GetCameraPos(void) { return m_Pos; }	//	�J�������W
	D3DXVECTOR3 GetCameraPosAt(void) { return m_LookAt; }	//	�����_
	D3DXVECTOR3 GetCameraVecUp(void) { return m_VecUp; }	//	��̎��_
	D3DXVECTOR3 GetForwardVector(void) { return m_VecAtCa; }	//	�O�����x�N�g��

	D3DXVECTOR2 GetCameraRotVH(void) { return D3DXVECTOR2(m_fRotV, m_fRotH); }

	//	�s��
	const D3DXMATRIX GetMtxView(void)const { return m_MtxView; };	//	�r���[�s��
	const D3DXMATRIX &GetMtxProjection(void)const { return m_mtxProj; }	//	�v���W�F�N�V�����s��

																		//	�t�s��
	const D3DXMATRIX GetInversedView(void)const;	//	�r���[�s��

	void SwitchFrag(void) { m_bUp = !m_bUp; }
	bool GetFrag(void) { return m_bUp; }

private:
	void InputProcess(void);

	void SetProjection(void);	//	�v���W�F�N�V�����̃Z�b�g

private:
	D3DXVECTOR3 m_LookAt;			//�����_���W
	D3DXVECTOR3 m_Pos;				//���_�ʒu
	D3DXVECTOR3 m_VecUp;			//�J���������
	D3DXVECTOR3 m_VecAtCa;			//�����_����J�����ւ̃x�N�g��
									//D3DXVECTOR3 m_NorVecAtCa;		//���̐��K��
	float m_fLength;				//�����_����J�����ւ̋���
	float m_fRotV;					//XZ���ʎ��̊p�x
	float m_fRotH;					//�J�����ƒ����_��XZ���ʏ�̊p�x(Y����])
	float m_fFov;					//����p�A��p(�Y�[���C���A�Y�[���A�E�g)


	D3DXMATRIX m_MtxView;		//	�r���[�s��}�g���N�X
	D3DXMATRIX m_mtxProj;		//	�v���W�F�N�V�����s��}�g���N�X

	bool m_bUp;
};
#endif
