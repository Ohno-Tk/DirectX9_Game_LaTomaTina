/*=============================================================================

		ゲームシーン[ GameScene.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/24
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/24
=============================================================================*/

#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

/*-----------------------------------------------------------------------------
	マクロ定義
-----------------------------------------------------------------------------*/
#define MAX_HOUSE 16

/*-----------------------------------------------------------------------------
	前方宣言
-----------------------------------------------------------------------------*/
class CSprite2D;
class CGround;
class CPlayerUI;
class CKillCount;
class CHouse;
class CEnemyManager;
class CPlayer;

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CGameScene :public CMode
{
public:
	CGameScene();

	virtual void Init(void)override;	//	初期化
	virtual void Uninit(void)override;	//	終了
	virtual void Update(void)override;	//	更新
	virtual void Draw(void)override;	//	描画

	static void GameClear(void) { m_Clear = true; }
	static void GameOver(void) { m_GameOver = true; }

	//	Getter
	static CKillCount* GetKillCount(void) { return m_Kill; }
	static CPlayer* GetPlayer(void) { return m_Player; }

private:
	void ConditionalTransition(void);	//	遷移条件
	void ObjectCreate(void);			//	オブジェクトの生成

private:
	CGround* m_Ground;
	CPlayerUI* m_PlayerUI;
	CSprite2D* m_Game_UI;
	CSprite2D* m_Kill_Logo;
	static CKillCount* m_Kill;
	CHouse* m_House[MAX_HOUSE];
	CEnemyManager* m_EnemyManager;
	static CPlayer* m_Player;
	CSprite2D* m_Start_Logo;
	CSprite2D* m_Goal_Logo;

	static bool m_Clear;
	static bool m_GameOver;
	bool m_ModeChange;
};
#endif
