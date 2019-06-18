/*=============================================================================

		シーン描画( リスト構造 )[ Scene.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/04/26
-------------------------------------------------------------------------------
	■　更新日
		2017/08/24
=============================================================================*/

#ifndef _SCENE_H_
#define _SCENE_H_

/*-----------------------------------------------------------------------------
	定数定義
-----------------------------------------------------------------------------*/
#define PRIOLITY_MAX (6)	//	優先順位

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CScene
{
public:
	typedef enum	//	オブジェクトの種類
	{
		OBJTYPE_NONE = 0,	//	なし
		OBJTYPE_BULLET,	//	弾
		OBJTYPE_ENEMY,
		OBJTYPE_TARGET,
		OBJTYPE_MAX			//	最大数
	}OBJTYPE;

	CScene(int Priolity);	//	コンストラクタ

	virtual void Init(void) = 0;	//	初期化
	virtual void Uninit(void) = 0;	//	終了
	virtual void Update(void) = 0;	//	更新
	virtual void Draw(void) = 0;	//	描画

	static void UpdateAll(void);	//	全オブジェクトの更新
	static void DrawAll(void);		//	全オブジェクトの描画
	static void ReleaseAll(void);	//	全オブジェクトの解放

	//	Setter
	void SetPosition(const D3DXVECTOR3 Position) { m_Position = Position; }	//	座標
	void SetObjeType(const OBJTYPE objType) { m_objType = objType; }		//	オブジェクト種類


	//	Getter
	D3DXVECTOR3 GetPosition(void) { return m_Position; }		//	座標
	D3DXVECTOR3* GetPositionPointer(void) { return &m_Position; }//	座標のポインタ
	const OBJTYPE GetObjType(void)const { return m_objType; }	//	オブジェクト種類
	static CScene *GetList(int Priority) { return m_Top[Priority]; }	//	リストの先頭
	CScene *GetNext(void) { return m_Next; }	//	次のリスト

private:
	bool m_Delete;	//	削除フラグ

	OBJTYPE m_objType;	//	オブジェクトの種類

	static CScene *m_Top[PRIOLITY_MAX];	//	先頭のポインタ
	CScene *m_Next;			//	次のポインタ

protected:
	D3DXVECTOR3 m_Position;	//	座標

	void Release(void) { m_Delete = true; }	//	リリース

};
#endif