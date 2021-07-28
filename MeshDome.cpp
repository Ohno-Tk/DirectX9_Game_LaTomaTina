/*=============================================================================

		���b�V������[ MeshDome.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/05/12
-------------------------------------------------------------------------------
	���@�X�V��
		2017/08/18
=============================================================================*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Manager.h"
#include "TextureManager.h"
#include "Scene.h"
#include "MeshDome.h"

/*-----------------------------------------------------------------------------
	�ÓI�����o�ϐ�
-----------------------------------------------------------------------------*/
LPDIRECT3DTEXTURE9 CMeshDome::m_Texture = NULL;	// �e�N�X�`���ւ̃|�C���^

/*-----------------------------------------------------------------------------
�֐���:		CMeshDome::CMeshDome(int Priolity)
����:
�߂�l:
����:		������
-----------------------------------------------------------------------------*/
CMeshDome::CMeshDome(int Priolity) : CScene(Priolity)
{
	m_VtxBuff = NULL;		// ���_�o�b�t�@�ւ̃|�C���^

	m_IdxBuff = NULL;	//	�C���f�b�N�X�o�b�t�@

	m_Rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ��]
	m_Scl = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	// �g�嗦

	m_UVSet = D3DXVECTOR2(0.0f, 0.0f);	//	UV���W

	m_NumBlock_X = 0;	//	���̖���
	m_NumBlock_Y = 0;	//	�c�̖���

	m_Vertex = 0;		//	���_��
	m_IdxVerTex = 0;	//	�C���f�b�N�X�o�b�t�@��

	m_Radius = 0.0f;	//	���a

	m_IdxBackDraw = IDXBACK_DRAW_CLOCKWISE;	//	�ǂ�������ŕ`�悳���邩
}

/*-----------------------------------------------------------------------------
 �֐���:	CMeshDome *CMeshDome::Create(D3DXVECTOR3 Pos, UINT NumBlock_X, UINT NumBlock_Y, float Radius, IDXBACK_DRAW IdxBack, CTextureManager::TEXTURE_ID TextureID)
 ����:		D3DXVECTOR3 Pos							���W
			UINT NumBlock_X							���̖���
			UINT NumBlock_Y							�c�̖���
			float Radius							���a
			IDXBACK_DRAW IdxBack					�ǂ�������ŕ`�悳���邩
			CTextureManager::TEXTURE_ID TextureID	�e�N�X�`����ID
 �߂�l:	return MeshDome;	�N���X�̃|�C���^
 ����:		����
-----------------------------------------------------------------------------*/
CMeshDome *CMeshDome::Create(D3DXVECTOR3 Pos, UINT NumBlock_X, UINT NumBlock_Y, float Radius, IDXBACK_DRAW IdxBack, CTextureManager::TEXTURE_ID TextureID)
{

	CMeshDome *MeshDome;

	//	����
	MeshDome = new CMeshDome;


	//	���W�̃Z�b�g
	MeshDome->SetPosition( Pos );

	//	�c���̖����̃Z�b�g
	MeshDome->SetNumBlock( NumBlock_X , NumBlock_Y );

	//	���_���̌v�Z
	MeshDome->SetVertexCount( NumBlock_X , NumBlock_Y );

	//	�C���f�b�N�X�o�b�t�@�̌v�Z
	MeshDome->SetIdxVerTex( NumBlock_X , NumBlock_Y );

	//	�ǂ�������ŕ`�悳���邩
	MeshDome->SetIdxBackDraw( IdxBack );

	//	�e�N�X�`����ID�̃Z�b�g
	MeshDome->SetTextureID( TextureID );

	MeshDome->m_Radius = Radius;	//	���a

	MeshDome->Init();	//	������

	return MeshDome;
}

/*-----------------------------------------------------------------------------
�֐���:		void CMeshDome::Init(void)
����:
�߂�l:
����:		������
-----------------------------------------------------------------------------*/
void CMeshDome::Init(void)
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();

	//	���_�o�b�t�@�̐���
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX * m_Vertex, D3DUSAGE_WRITEONLY, FVF_VERTEX_3D, D3DPOOL_MANAGED, &m_VtxBuff, NULL)))
	{

		MessageBox(NULL, "���_�o�b�t�@�̐����G���[", "MeshDome.cpp", MB_OK | MB_ICONHAND);

	}
	
	MakeVerTex();	//	���_�̍쐬
		
	MakeIndex();	//	�C���f�b�N�X�o�b�t�@�̍쐬

}

/*-----------------------------------------------------------------------------
�֐���:		void CMeshDome::Uninit(void)
����:
�߂�l:
����:		�I��
-----------------------------------------------------------------------------*/
void CMeshDome::Uninit(void)
{

	//	�k���`�F�b�N
	if (m_VtxBuff != NULL)
	{

		m_VtxBuff->Release();
		m_VtxBuff = NULL;

	}

	if (m_IdxBuff != NULL)
	{

		m_IdxBuff->Release();
		m_IdxBuff = NULL;

	}

	CScene::Release();	//	�I�u�W�F�N�g���g�̉��

}

/*---------------------------------------------------------------------------- -
�֐���:		void CMeshDome::Update(void)
���� :
�߂�l :
���� :		�X�V
---------------------------------------------------------------------------- - */
void CMeshDome::Update(void)
{
	m_Rot.y += 0.01f;
}

/*-----------------------------------------------------------------------------
�֐���:		void CMeshDome::Draw(void)
����:
�߂�l:
����:		�`��
-----------------------------------------------------------------------------*/
void CMeshDome::Draw(void)
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();


	//	�p�C�v���C���̃X�g���[��
	Device->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_3D));

	Device->SetIndices(m_IdxBuff);

	//	���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, CManager::GetTextureManager()->GetTextureInfo(m_TextureId).Texture);

	SetWorld(Device);	//	���[���h���W�ϊ�

	//	�`��
	Device->DrawIndexedPrimitive(D3DPT_TRIANGLESTRIP, 0, 0, m_IdxVerTex, 0, m_IdxVerTex - 2);

}

/*-----------------------------------------------------------------------------
 �֐���:	void CMeshDome::MakeVerTex(void)
 ����:		
 �߂�l:	
 ����:		���_�̍쐬
-----------------------------------------------------------------------------*/
void CMeshDome::MakeVerTex(void)
{

	//	���z�A�h���X���擾����|�C���^�ϐ�
	VERTEX_3D* pVtx;

	//	���W�̊i�[�ϐ�
	D3DXVECTOR3 Pos;

	//	360�x�̈���̊p�x���߂�
	float Rot_XZ = 360.0f / m_NumBlock_X;

	//	90�x�̈���̊p�x���߂�
	float Rot_Y = 90.0f / m_NumBlock_Y;

	//	���UV���W�����߂�
	m_UVSet.x = 1.0f / m_NumBlock_X;
	m_UVSet.y = 1.0f / m_NumBlock_Y;


	//	�o�b�t�@�����b�N�����z�A�h���X���擾����
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//	�c
	for (UINT Cnt1 = 0; Cnt1 < m_NumBlock_Y + 1; Cnt1++)
	{

		//	�p�x�̐ݒ�
		float ��y = 90 - (Cnt1 * Rot_Y);

		//	�ŏ���90�x���狁�߂�
		//	90�x��������Ă���
		Pos.y = m_Radius * sinf(D3DXToRadian(��y));

		//	��
		for (UINT Cnt2 = 0; Cnt2 < m_NumBlock_X + 1; Cnt2++)
		{
			//	�p�x�̐ݒ�
			float ��xz = Cnt2 * Rot_XZ;

			//	XZ����360�x���߂�
			Pos.x = m_Radius * cosf(D3DXToRadian(��y)) * cosf(D3DXToRadian(��xz));
			Pos.z = m_Radius * cosf(D3DXToRadian(��y)) * sinf(D3DXToRadian(��xz));


			//	���_���W�̐ݒ�
			pVtx[0].Pos = Pos;


			//	�@���̐ݒ�
			pVtx[0].Nor = D3DXVECTOR3(0.0f, 10.0f, 0.0f);


			//	���_�F�̐ݒ�
			pVtx[0].Color = D3DCOLOR_RGBA(255, 255, 255, 255);


			//	�e�N�X�`�����W�̐ݒ�
			pVtx[0].Tex = D3DXVECTOR2(Cnt2 * m_UVSet.x, Cnt1 * m_UVSet.y);

			pVtx++;	//	�|�C���^�����炷

		}
	}

	//	�o�b�t�@�̃A�����b�N
	m_VtxBuff->Unlock();

}

/*-----------------------------------------------------------------------------
�֐���:		void CMeshDome::MakeIndex(void)
����:
�߂�l:
����:		�C���f�b�N�X�o�b�t�@�̍쐬
-----------------------------------------------------------------------------*/
void CMeshDome::MakeIndex(void)
{

	HRESULT hr;

	WORD* pIdx;	//	�|�C���^�ϐ�

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();


	//	�C���f�b�N�X�o�b�t�@�̐���
	hr = Device->CreateIndexBuffer(
		sizeof(WORD) * m_IdxVerTex,	//	�o�b�t�@��
		D3DUSAGE_WRITEONLY,	//	�g�p���@�t���O
		D3DFMT_INDEX16, //	�C���f�b�N�X�t�H�[�}�b�g
		D3DPOOL_MANAGED, //	�������̊Ǘ����@
		&m_IdxBuff,	//	�C���f�b�N�X�o�b�t�@�C���^�[�t�F�[�X�ւ̃|�C���^�̃A�h���X
		NULL);


	//	�C���f�b�N�X�o�b�t�@�̃G���[�`�F�b�N
	if (FAILED(hr))
	{

		MessageBox(NULL, "�C���f�b�N�X�o�b�t�@�̐������s", "Mesh.cpp", MB_OK | MB_ICONHAND);

	}


	//	�C���f�b�N�X�o�b�t�@�����b�N
	m_IdxBuff->Lock(0, 0, (void**)&pIdx, 0);


	if (m_IdxBackDraw == IDXBACK_DRAW_CLOCKWISE)
	{	//	���v���

		//	���v���𗠖ʂƂ���
		//	�c
		for (UINT Cnt1 = 0; Cnt1 < m_NumBlock_Y; Cnt1++)
		{

			//	�͂��߂���Ȃ�������
			//	�k�ރ|���S��
			if (Cnt1 != 0)
			{

				//	1�_�ł�
				pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1));

				pIdx++;	//	�|�C���^�����炷

			}

				//	2�_�ł�
			pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1));
			pIdx[1] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1) - (m_NumBlock_X + 1));

			pIdx += 2;	//	�|�C���^�����炷

			//	��
			for (UINT Cnt2 = 0; Cnt2 < m_NumBlock_X; Cnt2++)
			{

				//	2�_�ł�
				pIdx[0] = (WORD)(((Cnt1 + 1) * (m_NumBlock_X + 1) + 1) + Cnt2);
				pIdx[1] = (WORD)(((Cnt1 + 1) * (m_NumBlock_X + 1) + 1) - (m_NumBlock_X + 1) + Cnt2);

				pIdx += 2;	//	�|�C���^�����炷

			}

				//	�Ōザ��Ȃ�������
				//	�k�ރ|���S��
			if (Cnt1 != m_NumBlock_Y - 1)
			{

				//	1�_�ł�
				pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1) - 1);

				pIdx++;	//	�|�C���^�����炷

			}
		}
	}
	else
	{

		//	�t���v���𗠖ʂƂ���
		//	�c
		for (UINT Cnt1 = 0; Cnt1 < m_NumBlock_Y; Cnt1++)
		{
			//	�͂��߂���Ȃ�������
			//	�k�ރ|���S��
			if (Cnt1 != 0)
			{
				//	1�_�ł�

				pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1) - 1);

				pIdx++;	//	�|�C���^�����炷

			}

				//	2�_�ł�
			pIdx[1] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1));
			pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1) - (m_NumBlock_X + 1));

			pIdx += 2;	//	�|�C���^�����炷

			//	��
			for (UINT Cnt2 = 0; Cnt2 < m_NumBlock_X; Cnt2++)
			{
				//	2�_�ł�
				pIdx[1] = (WORD)(((Cnt1 + 1) * (m_NumBlock_X + 1) + 1) + Cnt2);
				pIdx[0] = (WORD)(((Cnt1 + 1) * (m_NumBlock_X + 1) + 1) - (m_NumBlock_X + 1) + Cnt2);

				pIdx += 2;	//	�|�C���^�����炷

			}

				//	�Ōザ��Ȃ�������
				//	�k�ރ|���S��
			if (Cnt1 != m_NumBlock_Y - 1)
			{
				//	1�_�ł�
				pIdx[0] = (WORD)((Cnt1 + 1) * (m_NumBlock_X + 1));

				pIdx++;	//	�|�C���^�����炷

			}
		}
	}

	//	�C���f�b�N�X�o�b�t�@�̃A�����b�N
	m_IdxBuff->Unlock();

}

/*-----------------------------------------------------------------------------
�֐���:		void CMeshDome::SetWorld(LPDIRECT3DDEVICE9 Device)
����:		LPDIRECT3DDEVICE9 Device	�f�o�C�X
�߂�l:
����:		���[���h���W�ϊ�
-----------------------------------------------------------------------------*/
void CMeshDome::SetWorld(LPDIRECT3DDEVICE9 Device)
{
	D3DXMATRIX mtxScl, mtxRot, mtxPos;

	D3DXMatrixIdentity(&m_MtxWorld);	//	�s���P�ʍs��ɂ���


	//	�g��s������
	D3DXMatrixScaling(&mtxScl,	//�g��s�񂪍����
		m_Scl.x,	//	X���g��
		m_Scl.y,	//	Y���g��
		m_Scl.z);	//	Z���g��

	//	��]�s������
	D3DXMatrixRotationYawPitchRoll(&mtxRot,	//	��]�s�񂪍����
		D3DXToRadian(m_Rot.y), //	Y����]
		D3DXToRadian(m_Rot.x), //	X����]
		D3DXToRadian(m_Rot.z)); //	Z����]

	//	���s�ړ��s������
	D3DXMatrixTranslation(&mtxPos,
		m_Position.x,	//	X���ړ�
		m_Position.y,	//	Y���ړ�
		m_Position.z);	//	Z���ړ�


	//	�|����
	D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &mtxScl);

	D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &mtxRot);

	D3DXMatrixMultiply(&m_MtxWorld, &m_MtxWorld, &mtxPos);

	//	�f�o�C�X�Ƀ��[���h�ϊ��s���ݒ�
	Device->SetTransform(D3DTS_WORLD, &m_MtxWorld);

}