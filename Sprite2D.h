/*=============================================================================

		2D�`��[ Sprite2D.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/24
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/27
=============================================================================*/

#ifndef _SPRITE2D_H_
#define _SPRITE2D_H_

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CSprite2D:public CScene
{
public:
	CSprite2D(int Priolity);	//	�R���X�g���N�^

	static CSprite2D* Create(int Priolity);	//	����

	virtual void Init(void)override;	//	������
	virtual void Uninit(void)override;	//	�I��
	virtual void Update(void)override;	//	�X�V
	virtual void Draw(void)override;	//	�`��

	virtual void TextureAnimation(void);		//	�e�N�X�`���A�j���[�V����

	//	Setter
	void SetSize(const D3DXVECTOR2 Size) { m_Size = Size; }	//	�傫��
	void SetColor(const D3DXCOLOR Col) { m_Color = Col; }	//	�F
	void SetTexturePattern(const int Pattern) { m_TexturePattern = Pattern; }	//	�e�N�X�`���p�^�[��
	void SetAnimationTime(const float Time) { m_TextureAnimationTime = Time; }	//	�e�N�X�`���A�j���[�V�����^�C��
	void SetTextureID(const CTextureManager::TEXTURE_ID Id) { m_TextureId = Id; }//	�e�N�X�`��ID

	//	Getter
	D3DXVECTOR2 GetSize(void) { return m_Size; }	//	�傫��
	D3DXCOLOR GetColor(void) { return m_Color; }	//	�F

private:
	void MakeVerTex(void);		//	���_�̍쐬
	void SetUpVerTex(void);		//	���_�̐ݒ�
private:
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;	//	���_�o�b�t�@
	D3DXVECTOR2 m_Size;					//	�傫��
	D3DXCOLOR m_Color;					//	�F
	int m_TexturePattern;				//	�e�N�X�`���p�^�[��
	float m_TextureAnimationCount;		//	�e�N�X�`���A�j���[�V�����J�E���^
	float m_TextureAnimationTime;		//	�e�N�X�`���A�j���[�V�����^�C��

	CTextureManager::TEXTURE_ID m_TextureId;	//	�e�N�X�`��ID
};
#endif
