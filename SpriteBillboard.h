/*=============================================================================

		�r���{�[�h�`��[ SpriteBillboard.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/25
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/27
=============================================================================*/

#ifndef _SPRITEBILLBOARD_H_
#define _SPRITEBILLBOARD_H_

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CSpriteBillboard :public CScene
{
public:
	CSpriteBillboard(int Priolity);	//	�R���X�g���N�^

	static CSpriteBillboard* Create(int Priolity);	//	����

	virtual void Init(void)override;	//	������
	virtual void Uninit(void)override;	//	�I��
	virtual void Update(void)override;	//	�X�V
	virtual void Draw(void)override;	//	�`��

	virtual void TextureAnimation(void);	//	�e�N�X�`���A�j���[�V����

	//	Setter
	void SetRotation(const D3DXVECTOR3 Rot) { m_Rotation = Rot; }	//	��]
	void SetScale(const D3DXVECTOR3 Scl) { m_Scale = Scl; }			//	�g�嗦
	void SetNormal(const D3DXVECTOR3 Nor) { m_Normal = Nor; }		//	�@��
	void SetSize(const D3DXVECTOR2 Size) { m_Size = Size; }			//	���_���W
	void SetColor(const D3DXCOLOR Col) { m_Color = Col; }			//	�F
	void SetTexturePattern(const int Pattern) { m_TexturePattern = Pattern; }	//	�e�N�X�`���p�^�[��
	void SetAnimationTime(const float Time) { m_TextureAnimationTime = Time; }	//	�e�N�X�`���A�j���[�V�����^�C��
	void SetTextureID(const CTextureManager::TEXTURE_ID Id) { m_TextureId = Id; }//	�e�N�X�`��ID

	//	Getter
	D3DXVECTOR3 GetRotation(void) { return m_Rotation; }	//	��]
	D3DXVECTOR3 GetScale(void) { return m_Scale; }			//	�g�嗦
	D3DXVECTOR3 GetNormal(void) { return m_Normal; }		//	�@��
	D3DXVECTOR2 GetSize(void) { return m_Size; }			//	���_���W
	D3DXCOLOR GetColor(void) { return m_Color; }			//	�F

private:
	void MakeVerTex(void);						//	���_�̍쐬
	void SetUpVerTex(void);						//	���_�̐ݒ�
	void SetWorld(LPDIRECT3DDEVICE9 Device);	//	���[���h���W�ϊ�

private:
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;	//	���_�o�b�t�@
	D3DXVECTOR3	m_Rotation;				//	��]
	D3DXVECTOR3	m_Scale;				//	�g�嗦
	D3DXVECTOR3	m_Normal;				//	�@��
	D3DXVECTOR2 m_Size;					//	���_���W
	D3DXCOLOR m_Color;					//	�F
	int m_TexturePattern;				//	�e�N�X�`���p�^�[��
	float m_TextureAnimationCount;		//	�e�N�X�`���A�j���[�V�����J�E���^
	float m_TextureAnimationTime;		//	�e�N�X�`���A�j���[�V�����^�C��

	CTextureManager::TEXTURE_ID m_TextureId;	//	�e�N�X�`��ID
};
#endif
