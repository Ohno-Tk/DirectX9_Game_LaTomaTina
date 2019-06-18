/*=============================================================================

		地面[ Ground.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/30
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/30
=============================================================================*/

#ifndef _GROUND_H_
#define _GROUND_H_

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CGround:public CSprite3D
{
public:
	//	コンストラクタ
	CGround(int Priolity) :CSprite3D(Priolity) {
		m_Scroll = 0.0f;
		m_ScrollSpeed = 0.0f;
	}

	static CGround* Create(int Priolity);	//	生成

	//	Setter
	void SetScroll(const float speed) { m_ScrollSpeed = speed; }

private:
	virtual void Init(void)override;	//	初期化
	virtual void Uninit(void)override;	//	終了
	virtual void Update(void)override;	//	更新
	virtual void Draw(void)override;	//	描画
	void SetUpVerTex(void);		//	頂点の設定

private:
	float m_Scroll;
	float m_ScrollSpeed;
};
#endif
