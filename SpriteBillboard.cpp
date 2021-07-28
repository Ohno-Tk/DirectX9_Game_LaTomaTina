/*=============================================================================

		�r���{�[�h�`��[ SpriteBillboard.cpp ]

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
#include "Manager.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Scene.h"
#include "SpriteBillboard.h"

/*-----------------------------------------------------------------------------
�֐���:		CSpriteBillboard::CSprite2D(int Priolity)
����:		int Priolity	�D��x
�߂�l:
����:		�R���X�g���N�^
-----------------------------------------------------------------------------*/
CSpriteBillboard::CSpriteBillboard(int Priolity) :CScene(Priolity)
{
	m_VtxBuff = NULL;							// ���_�o�b�t�@
	m_Rotation = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	��]
	m_Scale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);	//	�g�嗦
	m_Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	�@��
	m_Size = D3DXVECTOR2(0.0f, 0.0f);			//	���_���W
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//	�F
	m_TexturePattern = 0;						//	�e�N�X�`���p�^�[��
	m_TextureAnimationCount = 0.0f;				//	�e�N�X�`���A�j���[�V�����J�E���^
	m_TextureAnimationTime = 0.0f;				//	�e�N�X�`���A�j���[�V�����^�C��
}

/*-----------------------------------------------------------------------------
�֐���:		CSpriteBillboard* CSpriteBillboard::Create(int Priolity)
����:		int Priolity				�D��x
�߂�l:		return spriteBillboard;		�N���X�̃|�C���^
����:		����
-----------------------------------------------------------------------------*/
CSpriteBillboard* CSpriteBillboard::Create(int Priolity)
{
	CSpriteBillboard* spriteBillboard;

	spriteBillboard = new CSpriteBillboard(Priolity);

	spriteBillboard->Init();	//	������

	return spriteBillboard;
}

/*-----------------------------------------------------------------------------
�֐���:		void CSpriteBillboard::Init(void)
����:
�߂�l:
����:		������
-----------------------------------------------------------------------------*/
void CSpriteBillboard::Init(void)
{
	MakeVerTex();	//	���_�̍쐬
}

/*-----------------------------------------------------------------------------
�֐���:		void CSpriteBillboard::Uninit(void)
����:
�߂�l:
����:		�I��
-----------------------------------------------------------------------------*/
void CSpriteBillboard::Uninit(void)
{
	if (m_VtxBuff != NULL)
	{	//	���_�o�b�t�@

		m_VtxBuff->Release();	// ���
		m_VtxBuff = NULL;
	}

	CScene::Release();	//	�I�u�W�F�N�g���g�̉��
}

/*-----------------------------------------------------------------------------
�֐���:		void CSpriteBillboard::Update(void)
����:
�߂�l:
����:		�X�V
-----------------------------------------------------------------------------*/
void CSpriteBillboard::Update(void)
{
	SetUpVerTex();	//	���_�̐ݒ�
}

/*-----------------------------------------------------------------------------
�֐���:		void CSpriteBillboard::Draw(void)
����:
�߂�l:
����:		�`��
-----------------------------------------------------------------------------*/
void CSpriteBillboard::Draw(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();


	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	Device->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_3D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, CManager::GetTextureManager()->GetTextureInfo(m_TextureId).Texture);

	SetWorld(Device);	//	���[���h���W�ϊ�

						// �`��
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

/*-----------------------------------------------------------------------------
�֐���:		void CSpriteBillboard::TextureAnimation(void)
����:
�߂�l:
����:		�e�N�X�`���A�j���[�V����
-----------------------------------------------------------------------------*/
void CSpriteBillboard::TextureAnimation(void)
{
	CTextureManager::TEXTUREINFO TextureInfo = CManager::GetTextureManager()->GetTextureInfo(m_TextureId);

	m_TexturePattern = (int)m_TextureAnimationCount % (int)TextureInfo.Div.x;

	m_TextureAnimationCount += m_TextureAnimationTime;
}

/*-----------------------------------------------------------------------------
�֐���:		void CSpriteBillboard::MakeVerTex(void)
����:
�߂�l:
����:		���_�̍쐬
-----------------------------------------------------------------------------*/
void CSpriteBillboard::MakeVerTex(void)
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();


	// ���_�o�b�t�@�̐���
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_3D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VtxBuff, NULL)))
	{

		MessageBox(NULL, "���_�o�b�t�@�̐����Ɏ��s", "SpriteBillboard.cpp", MB_OK | MB_ICONHAND);
		return;
	}

	// ���_����ݒ�
	// �\���̂̃|�C���^�錾
	VERTEX_3D* pVtx;

	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	//	���_���W�̐ݒ�
	pVtx[0].Pos = D3DXVECTOR3(-m_Size.x, m_Size.y, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(m_Size.x, m_Size.y, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(-m_Size.x, 0.0f, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(m_Size.x, 0.0f, 0.0f);


	//	�@��
	pVtx[0].Nor = m_Normal;
	pVtx[1].Nor = m_Normal;
	pVtx[2].Nor = m_Normal;
	pVtx[3].Nor = m_Normal;


	// ���_�J���[
	pVtx[0].Color = m_Color;
	pVtx[1].Color = m_Color;
	pVtx[2].Color = m_Color;
	pVtx[3].Color = m_Color;


	// �e�N�X�`�����W
	pVtx[0].Tex = D3DXVECTOR2(0, 0);
	pVtx[1].Tex = D3DXVECTOR2(1, 0);
	pVtx[2].Tex = D3DXVECTOR2(0, 1);
	pVtx[3].Tex = D3DXVECTOR2(1, 1);


	//	�o�b�t�@���A�����b�N
	m_VtxBuff->Unlock();
}

/*-----------------------------------------------------------------------------
�֐���:		void CSpriteBillboard::SetUpVerTex(void)
����:
�߂�l:
����:		���_�̐ݒ�
-----------------------------------------------------------------------------*/
void CSpriteBillboard::SetUpVerTex(void)
{
	CTextureManager::TEXTUREINFO TextureInfo = CManager::GetTextureManager()->GetTextureInfo(m_TextureId);

	const int tw = (int)(TextureInfo.Div.x);
	const int th = (int)(TextureInfo.Div.y);
	const int tcx = m_TexturePattern % (int)TextureInfo.Div.x;
	const int tcy = (int)(m_TexturePattern / TextureInfo.Div.x) % (int)TextureInfo.Div.y;
	const int tcw = 1;
	const int tch = 1;

	const float v0 = (float)tcy / th;
	const float u0 = (float)tcx / tw;
	const float u1 = (float)(tcx + tcw) / tw;
	const float v1 = (float)(tcy + tch) / th;

	// ���_����ݒ�
	// �\���̂̃|�C���^�錾
	VERTEX_3D* pVtx;

	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	//	���_���W�̐ݒ�
	pVtx[0].Pos = D3DXVECTOR3(-m_Size.x, m_Size.y, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(m_Size.x, m_Size.y, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(-m_Size.x, 0.0f, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(m_Size.x, 0.0f, 0.0f);


	//	�@��
	pVtx[0].Nor = m_Normal;
	pVtx[1].Nor = m_Normal;
	pVtx[2].Nor = m_Normal;
	pVtx[3].Nor = m_Normal;


	// ���_�J���[
	pVtx[0].Color = m_Color;
	pVtx[1].Color = m_Color;
	pVtx[2].Color = m_Color;
	pVtx[3].Color = m_Color;


	// �e�N�X�`�����W
	pVtx[0].Tex = D3DXVECTOR2(u0, v0);
	pVtx[1].Tex = D3DXVECTOR2(u1, v0);
	pVtx[2].Tex = D3DXVECTOR2(u0, v1);
	pVtx[3].Tex = D3DXVECTOR2(u1, v1);


	//	�o�b�t�@���A�����b�N
	m_VtxBuff->Unlock();
}

/*-----------------------------------------------------------------------------
�֐���:		void CSpriteBillboard::SetWorld(LPDIRECT3DDEVICE9 Device)
����:		LPDIRECT3DDEVICE9 Device	�f�o�C�X
�߂�l:
����:		���[���h���W�ϊ�
-----------------------------------------------------------------------------*/
void CSpriteBillboard::SetWorld(LPDIRECT3DDEVICE9 Device)
{
	//	�r���[�s��̋t�s����擾
	D3DXMATRIX mtxViewInverse = CManager::GetCamera()->GetInversedView();


	D3DXMATRIX mtxWorld, mtxScl, mtxPos;

	D3DXMatrixIdentity(&mtxWorld);	//	�s���P�ʍs��ɂ���

	//	�g��s������
	D3DXMatrixScaling(&mtxScl,	//�g��s�񂪍����
		m_Scale.x,	//	X���g��
		m_Scale.y,	//	Y���g��
		m_Scale.z);	//	Z���g��


	//	���s�ړ��s������
	D3DXMatrixTranslation(&mtxPos,
		m_Position.x,	//	X���ړ�
		m_Position.y,	//	Y���ړ�
		m_Position.z);	//	Z���ړ�


	//	�|����
	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxViewInverse);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxScl);

	D3DXMatrixMultiply(&mtxWorld, &mtxWorld, &mtxPos);

	//	�f�o�C�X�Ƀ��[���h�ϊ��s���ݒ�
	Device->SetTransform(D3DTS_WORLD, &mtxWorld);
}