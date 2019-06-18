/*=============================================================================

		タイトルシーン[ TitleScene.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/24
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/24
=============================================================================*/

#ifndef _TITLESCENE_H_
#define _TITLESCENE_H_

/*-----------------------------------------------------------------------------
	前方宣言
-----------------------------------------------------------------------------*/
class CSprite2D;			//	2D描画
class CSpriteModeLX;		//	モデル描画
class CFadeRogo;
class CGround;
class CHouse;

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CTitleScene:public CMode
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
	CSprite2D* m_Title_Logo;
	CFadeRogo* m_Push_Buttom;
	CGround* m_Ground;
	CHouse* m_House[16];
};
#endif
