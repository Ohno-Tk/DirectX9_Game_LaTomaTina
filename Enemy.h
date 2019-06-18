/*=============================================================================

		[ Enemy.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/30
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/30
=============================================================================*/

#ifndef _ENEMY_H_
#define _ENEMY_H_

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CEnemy:public CMotion
{
public:
	CEnemy(int Priolity = 3):CMotion(Priolity){}

	static CEnemy* Create(D3DXVECTOR3 pos ,float speed);

	virtual void Init(void)override;	//	初期化
	virtual void Uninit(void)override;	//	終了
	virtual void Update(void)override;	//	更新
	virtual void Draw(void)override;	//	描画

private:
	D3DXVECTOR3 m_Pos;
	float m_Speed;
};
#endif
