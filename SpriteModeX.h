/*=============================================================================

		Xモデル描画[ SpriteModeX.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/25
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/27
=============================================================================*/

#ifndef _SPRITEMODELX_H_
#define _SPRITEMODELX_H_

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CSpriteModeLX:public CScene
{
public:
	CSpriteModeLX(int Priolity);	//	コンストラクタ

	//	生成
	static CSpriteModeLX* Create(int Priolity);

	virtual void Init(void)override {}	//	初期化
	virtual void Uninit(void)override { CScene::Release(); }	//	終了
	virtual void Update(void)override {}	//	更新
	virtual void Draw(void)override;	//	描画

	//	Setter
	void SetRotation(const D3DXVECTOR3 Rot) { m_Rotation = Rot; }	//	回転
	void SetScale(const D3DXVECTOR3 Scl) { m_Scale = Scl; }			//	拡大率
	void SetModel(char *FileName) { m_FileName = FileName; }	//	ファイル名

	//	Getter
	D3DXVECTOR3 GetRotation(void) { return m_Rotation; }	//	回転
	D3DXVECTOR3 GetScale(void) { return m_Scale; }			//	拡大率

private:
	void SetWorld(LPDIRECT3DDEVICE9 Device);	//	ワールド座標変換

private:
	D3DXVECTOR3	m_Rotation;				//	回転
	D3DXVECTOR3	m_Scale;				//	拡大率

	char *m_FileName;	//	ファイル名

	CModelManager::MODEL_PARAM m_ModelParam;	//	モデル構造体
};
#endif
