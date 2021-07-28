/*=============================================================================

		�t�F�[�h���S[ FadeLogo.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/07/20
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/27
=============================================================================*/

#ifndef _FADE_LOGO_H_
#define _FADE_LOGO_H_

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CFadeRogo :public CSprite2D
{
public:
	CFadeRogo(int Priolity);		//	�R���X�g���N�^

	static CFadeRogo* Create(int Priolity);	//	����

	virtual void Init(void)override { CSprite2D::Init(); }	//	������
	virtual void Uninit(void)override { CSprite2D::Uninit(); }	//	�I��
	virtual void Update(void)override;	//	�X�V
	virtual void Draw(void)override { CSprite2D::Draw(); }	//	�`��

	//	Setter
	void SetUpLimit(const float limit) { m_UplimitFade = limit; }	//	����l
	void SetLowerLimit(const float limit) { m_LowerFade = limit; }	//	�����l
	void SetFadeFlag(const bool Flag) { m_FadeFlag = Flag; }//	�t�F�[�h�t���O
	void SetAlpha(const float value) { m_Color.a = value; }	//	���l

private:

private:
	typedef enum
	{	//	�t�F�[�h�̏��
		FADE_IN = 0,	//	�t�F�[�h�C��
		FADE_OUT,		//	�t�F�[�h�A�E�g
		FADE_MAX
	}FADE;

	D3DXCOLOR m_Color;	//	�F
	float m_UplimitFade;	//	�t�F�[�h�̏���l
	float m_LowerFade;		//	�t�F�[�h�̉����l
	bool m_FadeFlag;		//	�t�F�[�h�t���O

	FADE m_Fade;//	�t�F�[�h���
};
#endif
