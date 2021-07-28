/*=============================================================================

		����2D[ Number2D.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/07/14
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
#include "Number2D.h"

/*-----------------------------------------------------------------------------
	�}�N����`
-----------------------------------------------------------------------------*/
#define BUNKATUSU ( 0.1f )	//	�e�N�X�`���̕�����

/*-----------------------------------------------------------------------------
 �֐���:	CNumber2D :: CNumber2D()
 ����:		
 �߂�l:	
 ����:		�R���X�g���N�^
-----------------------------------------------------------------------------*/
CNumber2D::CNumber2D()
{

	m_VtxBuff = NULL;							// ���_�o�b�t�@

	m_Position = D3DXVECTOR2(0.0f, 0.0f);		//	���W
	m_Size = D3DXVECTOR2(0.0f, 0.0f);			//	�傫��
	m_USet = D3DXVECTOR2(0.0f, 0.0f);			//	�e�N�X�`�����W
	m_Color = D3DXCOLOR(255, 255, 255, 255);	//	�F
}

/*-----------------------------------------------------------------------------
 �֐���:	CNumber2D *CNumber2D::Create(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, CTextureManager::TEXTURE_ID TextureID, int CntWidth)
 ����:		D3DXVECTOR3 Pos							���W
			D3DXVECTOR3 Size						�傫��
			CTextureManager::TEXTURE_ID TextureID	�e�N�X�`����ID
			int CntWidth							���̃J�E���^
			NUMBERTYPE numbertype
 �߂�l:	return number2D;	�N���X�̃|�C���^
 ����:		����
-----------------------------------------------------------------------------*/
CNumber2D *CNumber2D::Create(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, CTextureManager::TEXTURE_ID TextureID, int CntWidth)
{

	CNumber2D *number2D;

	//	����
	number2D = new CNumber2D;

	number2D->m_Position = Pos;	//	���W

	number2D->m_Size = Size;	//	�傫��

	number2D->m_TextureId = TextureID;	//	�e�N�X�`����ID

	//	������
	number2D->Init(CntWidth);

	return number2D;
}

/*-----------------------------------------------------------------------------
 �֐���:	void CNumber2D::Init(int CntWidth)
 ����:		int CntWidth		���̃J�E���^
 �߂�l:	
 ����:		������
-----------------------------------------------------------------------------*/
void CNumber2D::Init(int CntWidth)
{
	MakeVerTex(CntWidth);
}

/*-----------------------------------------------------------------------------
�֐���:		void CNumber2D::Uninit( void )
����:
�߂�l:
����:		�I��
-----------------------------------------------------------------------------*/
void CNumber2D::Uninit(void)
{

	// ���_�o�b�t�@�̔j��
	if (m_VtxBuff != NULL)	//	���_�o�b�t�@�C���^�t�F�[�X�J��
	{

		m_VtxBuff->Release();
		m_VtxBuff = NULL;

	}
}

/*-----------------------------------------------------------------------------
�֐���:		void CNumber2D::Update( void )
����:		
�߂�l:
����:		�X�V
-----------------------------------------------------------------------------*/
void CNumber2D::Update(void)
{

	//	���_�̕ύX
	SetVerTex();

}

/*-----------------------------------------------------------------------------
 �֐���:	void CNumber2D::Draw( void )
 ����:		
 �߂�l:	
 ����:		�`��
-----------------------------------------------------------------------------*/
void CNumber2D::Draw( void )
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
 �֐���:	void CNumber2D::MakeVerTex( int CntWidth)
 ����:		int CntWidth	���̃J�E���^
 �߂�l:	
 ����:		���_�̍쐬
-----------------------------------------------------------------------------*/
void CNumber2D::MakeVerTex(int CntWidth)
{

	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();


	// ���_�o�b�t�@�̐���
	if (FAILED(Device->CreateVertexBuffer(sizeof(VERTEX_2D) * NUM_VERTEX, D3DUSAGE_WRITEONLY, FVF_VERTEX_2D, D3DPOOL_MANAGED, &m_VtxBuff, NULL)))
	{
		MessageBox(NULL, "���_�o�b�t�@�̐������s", "Number2D.cpp", MB_OK | MB_ICONHAND);
	}

	// �\���̂̃|�C���^�錾
	VERTEX_2D* pVtx;


	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	m_VtxBuff-> Lock ( 0 , 0 , ( void** )&pVtx , 0 );


	//	���_���W�̐ݒ�
	pVtx[ 0 ].Pos = D3DXVECTOR3( m_Position.x            - m_Size.x * CntWidth , m_Position.y            , 0.0f);
	pVtx[ 1 ].Pos = D3DXVECTOR3( m_Position.x + m_Size.x - m_Size.x * CntWidth , m_Position.y            , 0.0f);
	pVtx[ 2 ].Pos = D3DXVECTOR3( m_Position.x            - m_Size.x * CntWidth , m_Position.y + m_Size.y , 0.0f);
	pVtx[ 3 ].Pos = D3DXVECTOR3( m_Position.x + m_Size.x - m_Size.x * CntWidth , m_Position.y + m_Size.y , 0.0f);


	//	���W�ϊ��ςݒ��_�t���O�̐ݒ�
	pVtx[ 0 ].Rhw = 1.0f;
	pVtx[ 1 ].Rhw = 1.0f;
	pVtx[ 2 ].Rhw = 1.0f;
	pVtx[ 3 ].Rhw = 1.0f;


	//	���_�F�̐ݒ�
	pVtx[ 0 ].Color = m_Color;
	pVtx[ 1 ].Color = m_Color;
	pVtx[ 2 ].Color = m_Color;
	pVtx[ 3 ].Color = m_Color;


	//	�e�N�X�`�����W�̐ݒ�
	pVtx[ 0 ].Tex = D3DXVECTOR2( m_USet.x             , 0 );
	pVtx[ 1 ].Tex = D3DXVECTOR2( m_USet.x + BUNKATUSU , 0 );
	pVtx[ 2 ].Tex = D3DXVECTOR2( m_USet.x             , 1 );
	pVtx[ 3 ].Tex = D3DXVECTOR2( m_USet.x + BUNKATUSU , 1 );


	//	�o�b�t�@�̃��b�N
	m_VtxBuff-> Unlock();

}

/*-----------------------------------------------------------------------------
 �֐���:	void CNumber2D :: SetVerTex( ivoid )
 ����:		
 �߂�l:	
 ����:		���_�̕ύX
-----------------------------------------------------------------------------*/
void CNumber2D::SetVerTex( void )
{

	// �\���̂̃|�C���^�錾
	VERTEX_2D* pVtx;


	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	m_VtxBuff -> Lock ( 0 , 0 , ( void** )&pVtx , 0 );


	//	���_�F�̐ݒ�
	pVtx[0].Color = m_Color;
	pVtx[1].Color = m_Color;
	pVtx[2].Color = m_Color;
	pVtx[3].Color = m_Color;


	//	�e�N�X�`�����W�̐ݒ�
	pVtx[0].Tex = D3DXVECTOR2(m_USet.x, 0);
	pVtx[1].Tex = D3DXVECTOR2(m_USet.x + BUNKATUSU, 0);
	pVtx[2].Tex = D3DXVECTOR2(m_USet.x, 1);
	pVtx[3].Tex = D3DXVECTOR2(m_USet.x + BUNKATUSU, 1);


	//	�o�b�t�@�̃��b�N
	m_VtxBuff -> Unlock();

}

/*-----------------------------------------------------------------------------
�֐���:		void CNumber2D::SetNumber(int Number)
����:		int Number	����
�߂�l:
����:		���_�̕ύX
-----------------------------------------------------------------------------*/
void CNumber2D::SetNumber(int Number)
{
	m_USet.x = Number * 0.1f;

}