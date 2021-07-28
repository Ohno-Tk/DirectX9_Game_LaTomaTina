/*=============================================================================

		[ Target.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/09/02
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/09/02
=============================================================================*/

#ifndef _TARGET_H_
#define _TARGET_H_

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CTarget:public CSpriteBillboard
{
public:
	CTarget(int Priolity = 2) :CSpriteBillboard(Priolity) {}

	static CTarget* Create(void);

private:
	virtual void Init(void)override { 
		CSpriteBillboard::Init();
		CScene::SetObjeType(OBJTYPE_TARGET);
	}	//	������
	virtual void Uninit(void)override { CSpriteBillboard::Uninit(); }	//	�I��
	virtual void Update(void)override { CSpriteBillboard::Update(); }	//	�X�V
	virtual void Draw(void)override { CSpriteBillboard::Draw(); }	//	�`��
};
#endif
