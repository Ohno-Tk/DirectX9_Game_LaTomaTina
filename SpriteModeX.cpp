/*=============================================================================

		X���f���`��[ SpriteModeLX.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/25
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/27
=============================================================================*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Manager.h"
#include "ModelManager.h"
#include "Scene.h"
#include "SpriteModeX.h"

/*-----------------------------------------------------------------------------
 �֐���:	CSpriteModeLX::CSpriteModeLX(int Priolity)
 ����:		int Priolity	�D��x
 �߂�l:	
 ����:		�R���X�g���N�^
-----------------------------------------------------------------------------*/
CSpriteModeLX::CSpriteModeLX(int Priolity) :CScene(Priolity)
{
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	��]
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//	�g�嗦
	m_FileName = NULL;
}

/*-----------------------------------------------------------------------------
�֐���:		CSpriteModeLX* CSpriteModeLX::Create(int Priolity)
����:		int Priolity			�D��x
�߂�l:
����:		����
-----------------------------------------------------------------------------*/
CSpriteModeLX* CSpriteModeLX::Create(int Priolity)
{
	CSpriteModeLX* spriteModelX;

	spriteModelX = new CSpriteModeLX(Priolity);

	spriteModelX->Init();	//	������

	return spriteModelX;
}

/*-----------------------------------------------------------------------------
�֐���:		void CSpriteModeLX::Draw(void)
����:
�߂�l:
����:		�`��
-----------------------------------------------------------------------------*/
void CSpriteModeLX::Draw(void)
{
	D3DMATERIAL9 matDef;

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();

	//	���f���Ǘ��̎擾
	CModelManager *ModelManager = CManager::GetModelManager();

	m_ModelParam = ModelManager->GetModelParam(m_FileName);

	//	���[���h���W�ϊ�
	SetWorld(Device);

	//	���݃f�o�C�X�ɐݒ肳��Ă���}�e���A�����̎擾
	Device->GetMaterial(&matDef);


	// ���݂̃}�e���A�����擾
	Device->GetMaterial(&matDef);


	// �}�e���A���ւ̃|�C���^���擾
	m_ModelParam.Mat = (D3DXMATERIAL*)m_ModelParam.BuffMat->GetBufferPointer();


	for (int nCntMat = 0; nCntMat < (int)m_ModelParam.NumMat; nCntMat++)
	{
		// �f�o�C�X�Ƀ}�e���A���̐ݒ�
		Device->SetMaterial(&m_ModelParam.Mat[nCntMat].MatD3D);

		// �e�N�X�`���̐ݒ�
		Device->SetTexture(0, m_ModelParam.Texture[nCntMat]);

		// �`��
		m_ModelParam.Mesh->DrawSubset(nCntMat);
	}

	// �}�e���A�������ɖ߂�
	Device->SetMaterial(&matDef);
}

/*-----------------------------------------------------------------------------
�֐���:		void CSpriteModeLX::SetWorld(LPDIRECT3DDEVICE9 Device)
����:		LPDIRECT3DDEVICE9 Device	�f�o�C�X
�߂�l:
����:		���[���h���W�ϊ�
-----------------------------------------------------------------------------*/
void CSpriteModeLX::SetWorld(LPDIRECT3DDEVICE9 Device)
{
	D3DXMATRIX mtxWorld, mtxScl, mtxRot, mtxPos;

	D3DXMatrixIdentity(&mtxWorld);	//	�s���P�ʍs��ɂ���

	//	�g��s������
	D3DXMatrixScaling(&mtxScl,	//�g��s�񂪍����
		m_Scale.x,	//	X���g��
		m_Scale.y,	//	Y���g��
		m_Scale.z);	//	Z���g��

	//	��]�s������
	D3DXMatrixRotationYawPitchRoll(&mtxRot,	//	��]�s�񂪍����
		D3DXToRadian(m_Rotation.y), //	Y����]
		D3DXToRadian(m_Rotation.x), //	X����]
		D3DXToRadian(m_Rotation.z)); //	Z����]

	//	���s�ړ��s������
	D3DXMatrixTranslation(&mtxPos,
		m_Position.x,	//	X���ړ�
		m_Position.y,	//	Y���ړ�
		m_Position.z);	//	Z���ړ�


	//	�|���Ă�����
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxPos);

	//	�f�o�C�X�Ƀ��[���h�ϊ��s���ݒ�
	Device->SetTransform(D3DTS_WORLD, &mtxWorld);
}