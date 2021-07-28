/*=============================================================================

		�^�C�g���V�[��[ TitleScene.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/24
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/24
=============================================================================*/

#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

/*-----------------------------------------------------------------------------
	�O���錾
-----------------------------------------------------------------------------*/
class CSprite2D;			//	2D�`��
class CSpriteModeLX;		//	���f���`��
class CFadeRogo;
class CGround;
class CHouse;

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CTitleScene:public CMode
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
	CSprite2D* m_Title_Logo;
	CFadeRogo* m_Push_Buttom;
	CGround* m_Ground;
	CHouse* m_House[16];
};
#endif
