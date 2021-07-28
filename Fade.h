/*=============================================================================

		�t�F�[�h[ Fade.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/25
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/25
=============================================================================*/

#ifndef _FADE_H_
#define _FADE_H_

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CFade
{
public:
	enum FADE
	{	//	�t�F�[�h�̏��
		FADE_NONE = 0,
		FADE_IN,	//	�t�F�[�h�C��
		FADE_OUT,	//	�t�F�[�h�A�E�g
	};

	CFade();	//	�R���X�g���N�^

	//	�t�F�[�h�̃Z�b�g
	static void SetFade(const FADE Fade, CMode *Mode) { m_Fade = Fade, m_Mode = Mode; }

	static CFade *Create(void);	//	����
	
	void Uninit(void);	//	�I��
	void Update(void);	//	�X�V
	void Draw(void);	//	�`��

private:
	void Init(void);			//	������
	void MakeVerTex(void);		//	���_�̍쐬
	void ChangeVerTex(void);	//	���_�̕ύX
	void AlphaFade(void);		//	���l�̃t�F�[�h

private:
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;	// ���_�o�b�t�@�̃|�C���^

	D3DXCOLOR m_Color;					//	�F

	static FADE m_Fade;					//	�t�F�[�h���
	static CMode *m_Mode;				//	��ʑJ�ڂ̃|�C���^
};
#endif
