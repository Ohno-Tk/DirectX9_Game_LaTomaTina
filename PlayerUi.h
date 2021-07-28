/*=============================================================================



-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/30
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/30
=============================================================================*/

#ifndef _PLAYERUI_H_
#define _PLAYERUI_H_

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CPlayerUI:public CSprite2D
{
public:
	CPlayerUI(int Priolity):CSprite2D(Priolity){}	//	�R���X�g���N�^

	static CPlayerUI* Create(int Priolity);	//	����


private:
	virtual void Init(void)override;	//	������
	virtual void Uninit(void)override;	//	�I��
	virtual void Update(void)override;	//	�X�V
	virtual void Draw(void)override;	//	�`��

};
#endif
