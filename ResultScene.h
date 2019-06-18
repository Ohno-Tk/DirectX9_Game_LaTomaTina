/*=============================================================================

		リザルトシーン[ ResultScene.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/25
------------------------------------------------------------------------------- 
	■　更新日
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
	クラス
-----------------------------------------------------------------------------*/
class CResultScene :public CMode
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
	CFadeRogo* m_Push_Buttom;
	CGround* m_Ground;
	CKillCount* m_Kill;
	CSprite2D* m_Kill_Logo;
	CSprite2D* m_Result_Logo;
	CHouse* m_House[16];
};
#endif
