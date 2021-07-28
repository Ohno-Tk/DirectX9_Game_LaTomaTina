/*=============================================================================

		���U���g�V�[��[ ResultScene.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/25
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/25
=============================================================================*/

#ifndef _RESULTSCENE_H_
#define _RESULTSCENE_H_

class CSprite2D;
class CFadeRogo;
class CGround;
class CKillCount;
class CHouse;

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CResultScene :public CMode
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
	CFadeRogo* m_Push_Buttom;
	CGround* m_Ground;
	CKillCount* m_Kill;
	CSprite2D* m_Kill_Logo;
	CSprite2D* m_Result_Logo;
	CHouse* m_House[16];
};
#endif
