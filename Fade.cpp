/*=============================================================================

		�t�F�[�h[ Fade.cpp ]

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
#include "TextureManager.h"
#include "Mode.h"
#include "Fade.h"

/*-----------------------------------------------------------------------------
	�}�N����`
-----------------------------------------------------------------------------*/
#define FADE_RATE ( 1.0f / 60 )	//	�ǂ̂��炢�Ńt�F�[�h������̂�
#define TEX_ID ( CTextureManager::TEX_FADE )	//	�e�N�X�`����ID

/*-----------------------------------------------------------------------------
	�ÓI�ϐ�
-----------------------------------------------------------------------------*/
CFade::FADE CFade::m_Fade = FADE_NONE;	//	�t�F�[�h���
CMode *CFade::m_Mode = NULL;			//	��ʑJ�ڂ̃|�C���^

/*-----------------------------------------------------------------------------
 �֐���:	CFade::CFade()
 ����:		
 �߂�l:	
 ����:		�R���X�g���N�^
-----------------------------------------------------------------------------*/
CFade::CFade()
{
	m_VtxBuff = NULL;	// ���_�o�b�t�@

	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f);	//	�F
}

/*-----------------------------------------------------------------------------
�֐���:		CFade *CFade::Create(void)
����:
�߂�l:		return fade;	�N���X�̃|�C���^
����:		����
-----------------------------------------------------------------------------*/
CFade *CFade::Create(void)
{
	CFade* fade;

	fade = new CFade;

	fade->Init();	//	������

	return fade;
}

/*-----------------------------------------------------------------------------
�֐���:		void CFade::Init(void)
����:
�߂�l:
����:		������
-----------------------------------------------------------------------------*/
void CFade::Init(void)
{
	//	�e�N�X�`���̎擾
	CTextureManager* Texture = CManager::GetTextureManager();

	Texture->Load(TEX_ID);

	MakeVerTex();	//	���_�̍쐬
}

/*-----------------------------------------------------------------------------
�֐���:		void CFade::Uninit(void)
����:
�߂�l:
����:		�I��
-----------------------------------------------------------------------------*/
void CFade::Uninit(void)
{
	if (m_VtxBuff)
	{
		m_VtxBuff->Release();	//	���
		m_VtxBuff = NULL;
	}

	m_Mode = NULL;
}

/*-----------------------------------------------------------------------------
�֐���:		void CFade::Update(void)
����:
�߂�l:
����:		�X�V
-----------------------------------------------------------------------------*/
void CFade::Update(void)
{
	AlphaFade();	//	���l�̃t�F�[�h

	ChangeVerTex();	//	���_�̕ύX
}

/*-----------------------------------------------------------------------------
�֐���:		void CFade::Draw(void)
����:
�߂�l:
����:		�`��
-----------------------------------------------------------------------------*/
void CFade::Draw(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();


	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	Device->SetStreamSource(0, m_VtxBuff, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	Device->SetFVF(FVF_VERTEX_2D);

	// �e�N�X�`���̐ݒ�
	Device->SetTexture(0, CManager::GetTextureManager()->GetTextureInfo(TEX_ID).Texture);

	// �`��
	Device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, NUM_POLYGON);
}

/*-----------------------------------------------------------------------------
�֐���:		void CFade::MakeVerTex(void)
����:
�߂�l:
����:		���_�̍쐬
-----------------------------------------------------------------------------*/
void CFade::MakeVerTex(void)
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();


	// ���_�o�b�t�@�̐���
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VtxBuff, NULL)))
	{

		MessageBox(NULL, "���_�o�b�t�@�̐����Ɏ��s", "Fade.cpp", MB_OK | MB_ICONHAND);
		return;
	}


	// ���_����ݒ�
	// �\���̂̃|�C���^�錾
	VERTEX_2D* pVtx;

	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//	���_���W�̐ݒ�
	pVtx[0].Pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	pVtx[1].Pos = D3DXVECTOR3(SCREEN_WIDTH, 0.0f, 0.0f);
	pVtx[2].Pos = D3DXVECTOR3(0.0f, SCREEN_HEIGHT, 0.0f);
	pVtx[3].Pos = D3DXVECTOR3(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);

	//	���W�ϊ��ςݒ��_�t���O�̐ݒ�
	pVtx[0].Rhw = 1.0f;
	pVtx[1].Rhw = 1.0f;
	pVtx[2].Rhw = 1.0f;
	pVtx[3].Rhw = 1.0f;

	//	���_�F�̐ݒ�
	pVtx[0].Color = m_Color;
	pVtx[1].Color = m_Color;
	pVtx[2].Color = m_Color;
	pVtx[3].Color = m_Color;

	//	�e�N�X�`�����W�̐ݒ�
	pVtx[0].Tex = D3DXVECTOR2(0, 0);
	pVtx[1].Tex = D3DXVECTOR2(1, 0);
	pVtx[2].Tex = D3DXVECTOR2(0, 1);
	pVtx[3].Tex = D3DXVECTOR2(1, 1);

	//	�o�b�t�@���A�����b�N
	m_VtxBuff->Unlock();
}

/*-----------------------------------------------------------------------------
�֐���:		void CFade::ChangeVerTex(void)
����:
�߂�l:
����:		���_�̕ύX
-----------------------------------------------------------------------------*/
void CFade::ChangeVerTex(void)
{
	// ���_����ݒ�
	// �\���̂̃|�C���^�錾
	VERTEX_2D* pVtx;

	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	m_VtxBuff->Lock(0, 0, (void**)&pVtx, 0);


	//	���_�F�̐ݒ�
	pVtx[0].Color = m_Color;
	pVtx[1].Color = m_Color;
	pVtx[2].Color = m_Color;
	pVtx[3].Color = m_Color;


	//	�o�b�t�@���A�����b�N
	m_VtxBuff->Unlock();
}

/*-----------------------------------------------------------------------------
�֐���:		void CFade::AlphaFade(void)
����:
�߂�l:
����:		���l�̃t�F�[�h
-----------------------------------------------------------------------------*/
void CFade::AlphaFade(void)
{
	//	�t�F�[�h���Ȃ����̏���
	if (m_Fade == FADE_NONE) return;

	if (m_Fade == FADE_IN)
	{	//	�t�F�[�h�C�����̏���

		m_Color.a -= FADE_RATE;	//	a�l�����Z���Č��̉�ʂ𕂂��яオ�点��

		if (m_Color.a < 0.0f)
		{	//	�t�F�[�h�C���̏I��

			m_Color.a = 0.0f;
			m_Fade = FADE_NONE;
		}
	}

	else if (m_Fade == FADE_OUT)
	{	//	�t�F�[�h�A�E�g���̏���

		m_Color.a += FADE_RATE;	//	a�l�����Z���Č��̉�ʂ������Ă���

		if (m_Color.a > 1.0f)
		{	//	�t�F�[�h�A�E�g�̏I��

			m_Color.a = 1.0f;
			m_Fade = FADE_IN;	//	�t�F�[�h�C���ɏ����̐؂�ւ�

			//	�J�ڂ̐ݒ�
			CManager::SetMode(m_Mode);
		}
	}
}