/*=============================================================================

		�t�F�[�h���S[ FadeLogo.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/07/20
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/27
=============================================================================*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "TextureManager.h"
#include "Scene.h"
#include "Sprite2D.h"
#include "FadeLogo.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define FADE_RATE ( 1.0f / 60 )	//	�ǂ̂��炢�Ńt�F�[�h������̂�

/*-----------------------------------------------------------------------------
�֐���:		CFadeRogo::CFadeRogo(int Priolity)
����:		int Priolity	�D��x
�߂�l:
����:		�R���X�g���N�^
-----------------------------------------------------------------------------*/
CFadeRogo::CFadeRogo(int Priolity) :CSprite2D(Priolity)
{
	m_Color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);	//	�F
	m_UplimitFade = 0.0f;	//	�t�F�[�h�̏���l
	m_LowerFade = 0.0f;		//	�t�F�[�h�̉����l
	m_FadeFlag = true;		//	�t�F�[�h�t���O

	m_Fade = FADE_IN;
}

/*-----------------------------------------------------------------------------
�֐���:		CFadeRogo* CFadeRogo::Create(int Priolity)
����:		int Priolity	�D��x
�߂�l:
����:		����
-----------------------------------------------------------------------------*/
CFadeRogo* CFadeRogo::Create(int Priolity)
{
	CFadeRogo* faderogo;

	faderogo = new CFadeRogo(Priolity);

	faderogo->Init();

	return faderogo;
}

/*-----------------------------------------------------------------------------
�֐���:		void CFadeRogo::Update(void)
����:
�߂�l:
����:		�X�V
-----------------------------------------------------------------------------*/
void CFadeRogo::Update(void)
{
	if (m_FadeFlag)
	{
		if (m_Fade == FADE_IN)
		{	//	�t�F�[�h�C�����̏���


			m_Color.a -= FADE_RATE;	//	a�l�����Z���Č��̉�ʂ𕂂��яオ�点��

			if (m_Color.a < m_LowerFade)
			{	//	�t�F�[�h�C���̏I��

				m_Color.a = m_LowerFade;
				m_Fade = FADE_OUT;

			}
		}


		else if (m_Fade == FADE_OUT)
		{	//	�t�F�[�h�A�E�g���̏���

			m_Color.a += FADE_RATE;	//	a�l�����Z���Č��̉�ʂ������Ă���


			if (m_Color.a > m_UplimitFade)
			{	//	�t�F�[�h�A�E�g�̏I��

				m_Color.a = m_UplimitFade;
				m_Fade = FADE_IN;	//	�t�F�[�h�C���ɏ����̐؂�ւ�

			}
		}
	}

	CSprite2D::SetColor(m_Color);

	CSprite2D::Update();
}