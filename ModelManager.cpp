/*=============================================================================

		���f���Ǘ�[ ModelManager.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/25
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/25
=============================================================================*/

/*-----------------------------------------------------------------------------
	scanf ��warning�h�~
-----------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include <string.h>
#include <assert.h>
#include "DirectX.h"
#include "ModelManager.h"

/*-----------------------------------------------------------------------------
	�}�N����`
-----------------------------------------------------------------------------*/
#define TEXTURE_PATH "data/TEXTURE/"

/*-----------------------------------------------------------------------------
�֐���:	
����:		
�߂�l:
����:		
-----------------------------------------------------------------------------*/
void CModelManager::Init(void)
{
	Load(MODEL_PATH"tomato.x");
	Load(MODEL_PATH"house.x");
	Load(MODEL_PATH"house2.x");
	Load(MODEL_PATH"taihou.x");

	Load(MODEL_PATH"Player/00_head.x");
	Load(MODEL_PATH"Player/01_body.x");
	Load(MODEL_PATH"Player/02_Hip.x");
	Load(MODEL_PATH"Player/03_JointAll_R.x");
	Load(MODEL_PATH"Player/04_Arm01_R.x");
	Load(MODEL_PATH"Player/05_Arm02_R.x");
	Load(MODEL_PATH"Player/06_Wrist_R.x");
	Load(MODEL_PATH"Player/07_Hand_R.x");
	Load(MODEL_PATH"Player/08_Hand_L.x");
	Load(MODEL_PATH"Player/09_LegJointAll.x");
	Load(MODEL_PATH"Player/10_Leg01.x");
	Load(MODEL_PATH"Player/11_Leg02.x");
	Load(MODEL_PATH"Player/12_foot.x");
	Load(MODEL_PATH"Player/13_Arm01_L.x");
	Load(MODEL_PATH"Player/14_Arm02_L.x");
	Load(MODEL_PATH"Player/15_JointAll_L.x");
	Load(MODEL_PATH"Player/16_Wrist_L.x");
}

/*-----------------------------------------------------------------------------
 �֐���:	
 ����:		
 �߂�l:	
 ����:		���f���̃��[�h
-----------------------------------------------------------------------------*/
void CModelManager::Load(char* Name)
{
	//	�����t�@�C�������݂��邩�̃`�F�b�N
	auto it = m_Model_Map.find(Name);

	if (it == m_Model_Map.end())
	{	//	���݂��Ȃ�������

		HRESULT hr;

		//	�f�o�C�X�̎擾
		LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();

		// X�t�@�C���̓ǂݍ���
		hr = D3DXLoadMeshFromX(Name,		//	�t�@�C����
			D3DXMESH_SYSTEMMEM,
			Device,					//	�f�o�C�X
			NULL,					//	�אڃo�b�t�@
			&m_Model.BuffMat,		//	�}�e���A�������i�[
			NULL,
			&m_Model.NumMat,		//	�}�e���A����
			&m_Model.Mesh);			//	���b�V��

		if (FAILED(hr))
		{

			MessageBox(NULL, "���f�����ǂݍ��߂܂���ł���", "Model.cpp", MB_OK | MB_ICONHAND);
			return;
		}


		//	�e�N�X�`���̓ǂݍ���
		m_Model.Mat = (D3DXMATERIAL*)m_Model.BuffMat->GetBufferPointer();
		m_Model.Texture = new LPDIRECT3DTEXTURE9[m_Model.NumMat];
		for (int i = 0; i < (int)m_Model.NumMat; i++)
		{

			m_Model.Texture[i] = NULL;

			if (m_Model.Mat[i].pTextureFilename)
			{

				char filePath[MAX_PATH];
				strcpy(filePath, TEXTURE_PATH);
				strcat(filePath, m_Model.Mat[i].pTextureFilename);

				hr = D3DXCreateTextureFromFile(Device, filePath, &m_Model.Texture[i]);

				if (FAILED(hr))
				{

					MessageBox(NULL, "�e�N�X�`�����ǂݍ��߂܂���ł���", "Model.cpp", MB_OK | MB_ICONHAND);
					return;
				}
			}
		}


		//	�L�[�ƒl��A��������
		m_Model_Map[Name] = m_Model;
	}
}

/*-----------------------------------------------------------------------------
�֐���:		void CModelManager::UnloadAll(void)
����:
�߂�l:
����:		�S���f���̔j��
-----------------------------------------------------------------------------*/
void CModelManager::UnloadAll(void)
{
	for (auto it = m_Model_Map.begin(); it != m_Model_Map.end(); ++it)
	{

		//	�e�N�X�`���̉��
		for (unsigned int i = 0; i < it->second.NumMat; i++)
		{

			if (it->second.Texture[i] == NULL) continue;

			it->second.Texture[i]->Release();	//	���

		}

		delete[] it->second.Texture;	//	���

		if (it->second.Mesh != NULL)    it->second.Mesh->Release();	//	���

		if (it->second.BuffMat != NULL) it->second.BuffMat->Release();	//	���

	}

	m_Model_Map.clear();	//	�S�v�f�̍폜
}

/*-----------------------------------------------------------------------------
�֐���:		
����:		
�߂�l:
����:		���f��ID�̎擾
-----------------------------------------------------------------------------*/
const CModelManager::MODEL_PARAM CModelManager::GetModelParam(char* Name)const
{
	//	������
	MODEL_PARAM Model;
	Model.BuffMat = NULL;
	Model.Mat = 0;
	Model.Mesh = NULL;
	Model.NumMat = 0;

	//	�t�@�C�������݂��邩�̃`�F�b�N
	auto it = m_Model_Map.find(Name);


	if (it != m_Model_Map.end())
	{	//	���݂��Ă�����

		return it->second;

	}

	assert(!"[ ModelManager.cpp ]   ���f�����擾�ł��܂���ł���");

	return Model;
}