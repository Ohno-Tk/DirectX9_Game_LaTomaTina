/*=============================================================================

		�Q�[���V�[��[ GameScene.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/24
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/24
=============================================================================*/

#ifndef _GAMESCENE_H_
#define _GAMESCENE_H_

/*-----------------------------------------------------------------------------
	�}�N����`
-----------------------------------------------------------------------------*/
#define MAX_HOUSE 16

/*-----------------------------------------------------------------------------
	�O���錾
-----------------------------------------------------------------------------*/
class CSprite2D;
class CGround;
class CPlayerUI;
class CKillCount;
class CHouse;
class CEnemyManager;
class CPlayer;

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CGameScene :public CMode
{
public:
	CGameScene();

	virtual void Init(void)override;	//	������
	virtual void Uninit(void)override;	//	�I��
	virtual void Update(void)override;	//	�X�V
	virtual void Draw(void)override;	//	�`��

	static void GameClear(void) { m_Clear = true; }
	static void GameOver(void) { m_GameOver = true; }

	//	Getter
	static CKillCount* GetKillCount(void) { return m_Kill; }
	static CPlayer* GetPlayer(void) { return m_Player; }

private:
	void ConditionalTransition(void);	//	�J�ڏ���
	void ObjectCreate(void);			//	�I�u�W�F�N�g�̐���

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
