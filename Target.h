/*=============================================================================

		[ Target.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/09/02
------------------------------------------------------------------------------- 
	■　更新日
		2017/09/02
=============================================================================*/

#ifndef _TARGET_H_
#define _TARGET_H_

/*-----------------------------------------------------------------------------
	クラス
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
	}	//	初期化
	virtual void Uninit(void)override { CSpriteBillboard::Uninit(); }	//	終了
	virtual void Update(void)override { CSpriteBillboard::Update(); }	//	更新
	virtual void Draw(void)override { CSpriteBillboard::Draw(); }	//	描画
};
#endif
