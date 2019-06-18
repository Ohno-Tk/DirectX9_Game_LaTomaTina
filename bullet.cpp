#include "DirectX.h"
#include "Sound.h"
#include "Collision.h"
#include "TextureManager.h"
#include "Manager.h"
#include "Mode.h"
#include "GameScene.h"
#include "ModelManager.h"
#include "Scene.h"
#include "SpriteBillboard.h"
#include "SpriteModeX.h"
#include "Motion.h"
#include "Enemy.h"
#include "bullet.h"
#include "KillCont.h"
#include "Target.h"

#define BULLET_SPEED		(1.0f)
#define MODEL_ID MODEL_PATH"tomato.x"

CBullet* CBullet::Create(D3DXVECTOR3 pos, D3DXVECTOR3 vec) {
	CBullet* pBullet = new CBullet;

	pBullet->m_Move = vec * BULLET_SPEED;

	pBullet->SetModel(MODEL_ID);
	pBullet->SetPosition(pos);
	pBullet->Init();

	return pBullet;
}

void CBullet::Init() {
	CSpriteModeLX::Init();

	CScene::SetObjeType(OBJTYPE_BULLET);
}

void CBullet::Uninit() {
	CSpriteModeLX::Uninit();
}
void CBullet::Update() {
	SetPosition(GetPosition() + m_Move);

	//地面と当たったら削除
	
	if(GetPosition().y <= 0.0f || GetPosition().z > -60.0f)
	{

		CSound* sound = CManager::GetSound();

		sound->Play(CSound::SOUND_LABEL_SE_TOMATO);

		//エフェクトを発生させる
		Uninit();
	}
	

	CSpriteModeLX::Update();

	D3DXVECTOR3 *Pos = CScene::GetPositionPointer();

	CCollisionSphere CollisionSphere(*Pos, 20.0f);

	CSound* sound = CManager::GetSound();

	for (int CntPriolity = 0; CntPriolity < PRIOLITY_MAX; CntPriolity++)
	{

		CScene *Scene = CScene::GetList(CntPriolity);

		while (Scene != NULL)
		{

			if (Scene->GetObjType() == CScene::OBJTYPE_ENEMY)
			{
				CEnemy *enemy = (CEnemy*)Scene;

				D3DXVECTOR3 EnemyPos = enemy->GetMotionPosition(0);

				if (CollisionSphere.Judge(D3DXVECTOR3(EnemyPos.x, EnemyPos.y + 5.0f, EnemyPos.z), 5.0f))
				{	//	衝突判定

					enemy->Uninit();
					this->Uninit();

					CKillCount* kill = CGameScene::GetKillCount();
					kill->AddCount(1);

					sound->Play(CSound::SOUND_LABEL_SE_TOMATO);

					sound->Play(CSound::SOUND_LABEL_SE_DEATH);
				}
			}
			if (Scene->GetObjType() == CScene::OBJTYPE_TARGET)
			{
				CTarget *target = (CTarget*)Scene;

				D3DXVECTOR3 TargetPos = target->GetPosition();

				if (CollisionSphere.Judge(D3DXVECTOR3(TargetPos.x, TargetPos.y + 5.0f, TargetPos.z), 1.0f))
				{	//	衝突判定

					this->Uninit();

					sound->Play(CSound::SOUND_LABEL_SE_TOMATO);
				}
			}

			Scene = Scene->GetNext();
		}
	}
}
void CBullet::Draw() {
	CSpriteModeLX::Draw();
}
