/*=============================================================================

		2D�`��[ Sprite2D.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/24
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/24
=============================================================================*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Manager.h"
#include "TextureManager.h"
#include "Scene.h"
#include "Sprite2D.h"

/*-----------------------------------------------------------------------------
 �֐���:	CSprite2D::CSprite2D(int Priolity)
 ����:		int Priolity	�D��x
 �߂�l:	
 ����:		�R���X�g���N�^
-----------------------------------------------------------------------------*/
CSprite2D::CSprite2D(int Priolity) :CScene(Priolity)
{
	m_VtxBuff = NULL;							// ���_�o�b�t�@
	m_Size = D3DXVECTOR2(0.0f, 0.0f);			//	�傫��
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);//	�F
	m_TexturePattern = 0;						//	�e�N�X�`���p�^�[��
	m_TextureAnimationCount = 0.0f;				//	�e�N�X�`���A�j���[�V�����J�E���^
	m_TextureAnimationTime = 0.0f;				//	�e�N�X�`���A�j���[�V�����^�C��
}

/*-----------------------------------------------------------------------------
�֐���:		CSprite2D* CSprite2D::Create(int Priolity)
����:		int Priolity	�D��x
�߂�l:		return sprite2D;	�N���X�̃|�C���^
����:		����
-----------------------------------------------------------------------------*/
CSprite2D* CSprite2D::Create(int Priolity)
{
	CSprite2D* sprite2D;

	sprite2D = new CSprite2D(Priolity);

	sprite2D->Init();	//	������

	return sprite2D;
}

/*-----------------------------------------------------------------------------
�֐���:		void CSprite2D::Init(void)
����:
�߂�l:
����:		������
-----------------------------------------------------------------------------*/
void CSprite2D::Init(void)
{
	MakeVerTex();	//	���_�̍쐬
}

/*-----------------------------------------------------------------------------
�֐���:		void CSprite2D::Uninit(void)
����:
�߂�l:
����:		�I��
-----------------------------------------------------------------------------*/
void CSprite2D::Uninit(void)
{
	if (m_VtxBuff != NULL)
	{	//	���_�o�b�t�@

		m_VtxBuff->Release();	// ���
		m_VtxBuff = NULL;
	}

	CScene::Release();	//	�I�u�W�F�N�g���g�̉��
}

/*-----------------------------------------------------------------------------
�֐���:		void CSprite2D::Update(void)
����:
�߂�l:
����:		�X�V
-----------------------------------------------------------------------------*/
void CSprite2D::Update(void)
{
	SetUpVerTex();	//	���_�̕ύX
}

/*-----------------------------------------------------------------------------
�֐���:		void CSprite2D::Draw(void)
����:
�߂�l:
����:		�`��
-----------------------------------------------------------------------------*/
void CSprite2D::Draw(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();


	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	Device->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, CManager::GetTextureManager()->GetTextureInfo(m_TextureId).Texture);

	// �`��
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

/*-----------------------------------------------------------------------------
�֐���:		void CSprite2D::TextureAnimation(void)
����:
�߂�l:
����:		�e�N�X�`���A�j���[�V����
-----------------------------------------------------------------------------*/
void CSprite2D::TextureAnimation(void)
{
	CTextureManager::TEXTUREINFO TextureInfo = CManager::GetTextureManager()->GetTextureInfo(m_TextureId);

	m_TexturePattern = (int)m_TextureAnimationCount % (int)TextureInfo.Div.x;

	m_TextureAnimationCount += m_TextureAnimationTime;
}

/*-----------------------------------------------------------------------------
�֐���:		void CSprite2D::MakeVerTex(void)
����:
�߂�l:
����:		���_�̍쐬
-----------------------------------------------------------------------------*/
void CSprite2D::MakeVerTex(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();


	// ���_�o�b�t�@�̐���
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VtxBuff, NULL)))
	{

		MessageBox(NULL, "���_�o�b�t�@�̐����Ɏ��s", "Sprite2D.cpp", MB_OK | MB_ICONHAND);
		return;
	}


	// ���_����ݒ�
	// �\���̂̃|�C���^�錾
	VERTEX_2D* pVtx;

	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//	���_���W�̐ݒ�
	pVtx[0].Pos = D3DXVECTOR3(m_Position.x, m_Position.y, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(m_Position.x + m_Size.x, m_Position.y, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(m_Position.x, m_Position.y + m_Size.y, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(m_Position.x + m_Size.x, m_Position.y + m_Size.y, 0.0f);


	//	���W�ϊ��ςݒ��_�t���O
	pVtx[0].Rhw = 1.0f;
	pVtx[1].Rhw = 1.0f;
	pVtx[2].Rhw = 1.0f;
	pVtx[3].Rhw = 1.0f;


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
�֐���:		void CSprite2D::SetUpVerTex(void)
����:
�߂�l:
����:		���_�̕ύX
-----------------------------------------------------------------------------*/
void CSprite2D::SetUpVerTex(void)
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
	VERTEX_2D* pVtx;

	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//	���_���W�̐ݒ�
	pVtx[0].Pos = D3DXVECTOR3(m_Position.x, m_Position.y, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(m_Position.x + m_Size.x, m_Position.y, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(m_Position.x, m_Position.y + m_Size.y, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(m_Position.x + m_Size.x, m_Position.y + m_Size.y, 0.0f);


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