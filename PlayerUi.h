/*=============================================================================



-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/30
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/30
=============================================================================*/

#ifndef _PLAYERUI_H_
#define _PLAYERUI_H_

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CPlayerUI:public CSprite2D
{
public:
	CPlayerUI(int Priolity):CSprite2D(Priolity){}	//	コンストラクタ

	static CPlayerUI* Create(int Priolity);	//	生成


private:
	virtual void Init(void)override;	//	初期化
	virtual void Uninit(void)override;	//	終了
	virtual void Update(void)override;	//	更新
	virtual void Draw(void)override;	//	描画

};
#endif
