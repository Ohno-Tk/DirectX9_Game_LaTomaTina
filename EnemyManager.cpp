/*=============================================================================

		[ EnemyManager.cpp ]

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
#include "ModelManager.h"
#include "Scene.h"
#include "Motion.h"
#include "EnemyManager.h"
#include "Enemy.h"

/*-----------------------------------------------------------------------------
 �֐���:	
 ����:		
 �߂�l:	
 ����:		
-----------------------------------------------------------------------------*/
void CEnemyManager::Update(void)
{

	m_Cont++;

	int i = rand() % 50 + 100;

	if (m_Cont > i)
	{
		float speed = (float)(rand() % 2);

		float pos = (float)(rand() % 7 - 7);

		CEnemy::Create(D3DXVECTOR3(pos,-5.0f,0.0f), 0.5f+ speed);

		m_Cont = 0;
	}
}