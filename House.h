/*=============================================================================

		家[ House.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/30
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/30
=============================================================================*/

#ifndef _HOUSE_H_
#define _HOUSE_H_

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CHouse:public CSpriteModeLX
{
public:
	CHouse(int Priolity = 2):CSpriteModeLX(Priolity){
		m_Speed = 0.05f;
	}

	static CHouse* Create(void);	//	生成

	//	Setter
	void SetSpeed(const float speed) { m_Speed = speed; }

private:
	virtual void Init(void)override {}	//	初期化
	virtual void Uninit(void)override;	//	終了
	virtual void Update(void)override;	//	更新
	virtual void Draw(void)override;	//	描画

private:
	float m_Speed;
};
#endif
