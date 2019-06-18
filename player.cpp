#include "DirectX.h"
#include "ModelManager.h"
#include "Scene.h"
#include "SpriteModeX.h"
#include "player.h"
#include "Input.h"
#include "Manager.h"
#include "Camera.h"
#include "bullet.h"
#include "Mode.h"
#include "GameScene.h"

#define MODEL_ID MODEL_PATH"tomato.x"

int CPlayer::m_HP = 3;

CPlayer* CPlayer::Create(void) {
	CPlayer* pPlayer = new CPlayer(3);

	pPlayer->m_FileName = MODEL_ID;
	pPlayer->Init();

	return pPlayer;
}

void CPlayer::Init() {
	m_Position = D3DXVECTOR3(0.0f, 8.0f, -98.0f);	//�J����-POS_CAMERA_TO_PLAYER
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	��]
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//	�g�嗦

	m_offset = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	m_HP = 3;
}

void CPlayer::Uninit() {
	CScene::Release();
}

void CPlayer::Update() {
	CInputMouse* pMouse = CManager::GetMouse();
	CCamera* pCamera = CManager::GetCamera();

	//if (pMouse->GetKeyTrigger(1)) {
	//	pCamera->SwitchFrag();
	//}
	//if (pCamera->GetFrag()) {
	//	m_Position = D3DXVECTOR3(0.0f, 8.0f, -98.0f);
	//}
	//else {
	//	m_Position = D3DXVECTOR3(0.0f, 5.0f, -98.0f);
	//}

//	if (pMouse->GetKeyPress(CInputMouse::MOUSE_LEFT) && pCamera->GetFrag())
	if (pMouse->GetKeyTrigger(CInputMouse::MOUSE_LEFT) && pCamera->GetFrag())
	{
		D3DXVECTOR3 cameraVec = pCamera->GetForwardVector();
		D3DXVec3Normalize(&cameraVec, &cameraVec);

		CBullet::Create(m_offset, cameraVec);
	}

}
void CPlayer::Draw() {
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
void CPlayer::SetWorld(LPDIRECT3DDEVICE9 Device)
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


	CCamera* pCamera = CManager::GetCamera();
	D3DXVECTOR2 cameraVH = pCamera->GetCameraRotVH();
	D3DXVECTOR3 offset;
	D3DXVECTOR3 cameraRot, cameraPos;

	cameraPos = pCamera->GetCameraPos();
	offset = cameraPos - m_Position;

	D3DXMATRIX mtxOffset, mtxCameraRot, mtxCameraTrans;

	D3DXMatrixTranslation(&mtxOffset, offset.x, offset.y, offset.z);

	cameraRot.y = -cameraVH.y - D3DXToRadian(90);
	cameraRot.x = cameraVH.x * sinf(cameraVH.y);
	cameraRot.z = cameraVH.x * cosf(cameraVH.y);

	D3DXMatrixRotationYawPitchRoll(&mtxCameraRot, cameraRot.y, cameraRot.x, cameraRot.z);


	D3DXMatrixTranslation(&mtxCameraTrans, cameraPos.x, cameraPos.y, cameraPos.z);


	m_offset = cameraPos - m_Position;
	D3DXVec3TransformCoord(&m_offset, &m_offset, &mtxOffset);
	D3DXVec3TransformCoord(&m_offset, &m_offset, &mtxCameraRot);
	D3DXVec3TransformCoord(&m_offset, &m_offset, &mtxCameraTrans);


	//	�|���Ă�����
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxRot);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxOffset);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxCameraRot);
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxCameraTrans);
	//D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxOffset);


	//	�f�o�C�X�Ƀ��[���h�ϊ��s���ݒ�
	Device->SetTransform(D3DTS_WORLD, &mtxWorld);
}


void CPlayer::SubHp(void)
{
	m_HP--;

	if (m_HP <= 0)
	{
		m_HP = 0;
		CGameScene::GameOver();
	}
}