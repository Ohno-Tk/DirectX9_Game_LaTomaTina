/*=============================================================================

		ウェーブ[ Wave.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/30
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/30
=============================================================================*/

#ifndef _KILLCOUNT_H_
#define _KILLCOUNT_H_

/*-----------------------------------------------------------------------------
	前方宣言
-----------------------------------------------------------------------------*/
class CNumber2D;

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CKillCount:public CScene
{
public:
	CKillCount(int Priolity) :CScene(Priolity) {
		m_Number[0] = NULL;
		m_Number[1] = NULL;
		m_KillCount = 0;
	}

	static CKillCount* Create(D3DXVECTOR2 pos, D3DXVECTOR2 size);

	void AddCount(const int add) { m_KillCount += add; }	//	加算
	void SetCount(const int count) { m_KillCount = count; }

	int GetCount(void) { return m_KillCount; }

private:
	virtual void Init(void);	//	初期化
	virtual void Uninit(void);	//	終了
	virtual void Update(void);	//	更新
	virtual void Draw(void);	//	描画

private:
	CNumber2D* m_Number[2];

	D3DXVECTOR2 m_Pos;
	D3DXVECTOR2 m_Size;

	int m_KillCount;	//	ウェーブ数
};
#endif
