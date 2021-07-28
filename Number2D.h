/*=============================================================================

		����2D[ Number2D.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/07/14
-------------------------------------------------------------------------------
	���@�X�V��
		2017/08/27
=============================================================================*/

#ifndef _NUMBER2D_H_
#define _NUMBER2D_H_

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CNumber2D
{
public:
	CNumber2D();	//	�R���X�g���N�^

	//	����
	static CNumber2D *Create(D3DXVECTOR2 Pos, D3DXVECTOR2 Size, CTextureManager::TEXTURE_ID TextureID, int CntWidth);

	void SetNumber(int Number);		//	�����̒l�ݒ�

	void Uninit(void);	//	�I��
	void Update(void);	//	�X�V
	void Draw( void );	//	�`��

	//	Setter
	void SetColor(const D3DXCOLOR color) { m_Color = color; }	//	�F�̃Z�b�g

private:
	void Init(int CntWidth);		//	������
	void MakeVerTex(int CntWidth);	//	���_�̍쐬
	void SetVerTex( void );		//	���_�̕ύX

	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^

	D3DXVECTOR2 m_Position;	//	���W
	D3DXVECTOR2 m_Size;	//	�傫��
	D3DXVECTOR2 m_USet;	//	�e�N�X�`�����W

	D3DXCOLOR m_Color;	//	�F

	CTextureManager::TEXTURE_ID m_TextureId;	//	�e�N�X�`����ID

};
#endif