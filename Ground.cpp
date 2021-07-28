/*=============================================================================

		�n��[ Ground.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/30
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/30
=============================================================================*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Manager.h"
#include "TextureManager.h"
#include "Scene.h"
#include "Sprite3D.h"
#include "Ground.h"

/*-----------------------------------------------------------------------------
 �֐���:	CGround* CGround::Create(int Priolity)
 ����:		
 �߂�l:	return ground;	�N���X�̃|�C���^
 ����:		����
-----------------------------------------------------------------------------*/
CGround* CGround::Create(int Priolity)
{
	CGround* ground;

	ground = new CGround(Priolity);

	ground->Init();

	return ground;
}

/*-----------------------------------------------------------------------------
�֐���:		void CGround::Init(void)
����:
�߂�l:
����:		������
-----------------------------------------------------------------------------*/
void CGround::Init(void)
{
	CSprite3D::Init();
}

/*-----------------------------------------------------------------------------
�֐���:		void CGround::Uninit(void)
����:
�߂�l:
����:		�I��
-----------------------------------------------------------------------------*/
void CGround::Uninit(void)
{
	CSprite3D::Uninit();
}

/*-----------------------------------------------------------------------------
�֐���:		void CGround::Update(void)
����:
�߂�l:
����:		�X�V
-----------------------------------------------------------------------------*/
void CGround::Update(void)
{
	m_Scroll += m_ScrollSpeed;

	CSprite3D::Update();
}

/*-----------------------------------------------------------------------------
�֐���:		void CGround::Draw(void)
����:
�߂�l:
����:		�`��
-----------------------------------------------------------------------------*/
void CGround::Draw(void)
{
	CSprite3D::Draw();
}

/*-----------------------------------------------------------------------------
�֐���:		void CGround::SetUpVerTex(void)
����:
�߂�l:
����:		���_�̐ݒ�
-----------------------------------------------------------------------------*/
void CGround::SetUpVerTex(void)
{
	//	���_�o�b�t�@�擾
	LPDIRECT3DVERTEXBUFFER9 VtxBuff = CSprite3D::GetVtxBuff();

	// ���_����ݒ�
	// �\���̂̃|�C���^�錾
	VERTEX_3D* pVtx;

	// �o�b�t�@�����b�N���A���z�A�h���X���擾
	VtxBuff->Lock(0, 0, (void**)&pVtx, 0);

	//	���_���W�̐ݒ�
	pVtx[0].Pos = D3DXVECTOR3(-m_Size.x, m_Size.y, m_Size.z);
	pVtx[1].Pos = D3DXVECTOR3(m_Size.x, m_Size.y, m_Size.z);
	pVtx[2].Pos = D3DXVECTOR3(-m_Size.x, -m_Size.y, -m_Size.z);
	pVtx[3].Pos = D3DXVECTOR3(m_Size.x, -m_Size.y, -m_Size.z);


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

	pVtx[0].Tex = D3DXVECTOR2(0, 0 + m_Scroll);
	pVtx[1].Tex = D3DXVECTOR2(10, 0 + m_Scroll);
	pVtx[2].Tex = D3DXVECTOR2(0, 10 + m_Scroll);
	pVtx[3].Tex = D3DXVECTOR2(10, 10 + m_Scroll);

	VtxBuff->Unlock();	//	�o�b�t�@���A�����b�N
}