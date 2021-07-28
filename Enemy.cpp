/*=============================================================================

		[ Enemy.cpp ]

-------------------------------------------------------------------------------
	���@�쐬��
		2017/08/30
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/30
=============================================================================*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Collision.h"
#include "Scene.h"
#include "ModelManager.h"
#include "Motion.h"
#include "bullet.h"
#include "Enemy.h"
#include "Mode.h"
#include "GameScene.h"
#include "player.h"

#define TEX_DATA "data/MOTION/Player.txt"

/*-----------------------------------------------------------------------------
 �֐���:	
 ����:		
 �߂�l:	
 ����:		
-----------------------------------------------------------------------------*/
CEnemy* CEnemy::Create(D3DXVECTOR3 pos, float speed)
{
	CEnemy* enemy;

	enemy = new CEnemy;

	enemy->m_Pos = pos;

	enemy->m_Speed = speed;

	enemy->Init();

	return enemy;
}

void CEnemy::Init(void)
{
	CMotion::SetFileName(TEX_DATA);

	CMotion::SetMotionIndex(1);

	CScene::SetObjeType(OBJTYPE_ENEMY);

	CMotion::Init();

	CMotion::SetMotionPosition(0, m_Pos);

}


void CEnemy::Uninit(void)
{
	CMotion::Uninit();
}


void CEnemy::Update(void)
{
	D3DXVECTOR3* Pos = CMotion::GetMotionPositionPointer(0);
	
	Pos->z -= m_Speed;

	CMotion::Update();

	if (Pos->z<-100.0f)
	{
		Uninit();

		CPlayer* player = CGameScene::GetPlayer();
		player->SubHp();
	}
}


void CEnemy::Draw(void)
{
	CMotion::Draw();
}