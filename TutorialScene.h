/*=============================================================================

		�`���[�g���A���V�[��[ TutorialScene.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/09/01
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/09/01
=============================================================================*/

#ifndef _TUTORAILSCENE_H_
#define _TUTORAILSCENE_H_

class CSprite2D;
class CFadeRogo;
class CGround;
class CHouse;
class CTarget;

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CTutorialScene:public CMode
{
public:
	virtual void Init(void)override;	//	������
	virtual void Uninit(void)override;	//	�I��
	virtual void Update(void)override;	//	�X�V
	virtual void Draw(void)override;	//	�`��

private:
	void ConditionalTransition(void);	//	�J�ڏ���
	void ObjectCreate(void);			//	�I�u�W�F�N�g�̐���

private:
	CSprite2D* m_bg;
	CFadeRogo* m_Push_Buttom;
	CGround* m_Ground;
	CHouse* m_House[16];
	CTarget* m_Target;
};
#endif
