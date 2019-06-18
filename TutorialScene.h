/*=============================================================================

		チュートリアルシーン[ TutorialScene.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/09/01
------------------------------------------------------------------------------- 
	■　更新日
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
	クラス
-----------------------------------------------------------------------------*/
class CTutorialScene:public CMode
{
public:
	virtual void Init(void)override;	//	初期化
	virtual void Uninit(void)override;	//	終了
	virtual void Update(void)override;	//	更新
	virtual void Draw(void)override;	//	描画

private:
	void ConditionalTransition(void);	//	遷移条件
	void ObjectCreate(void);			//	オブジェクトの生成

private:
	CSprite2D* m_bg;
	CFadeRogo* m_Push_Buttom;
	CGround* m_Ground;
	CHouse* m_House[16];
	CTarget* m_Target;
};
#endif
