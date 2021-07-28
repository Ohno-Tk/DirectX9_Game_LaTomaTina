/*=============================================================================

		�V�[��( ���X�g�\�� )[ Scene.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/04/26
-------------------------------------------------------------------------------
	���@�X�V��
		2017/08/27
=============================================================================*/

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include "DirectX.h"
#include "Scene.h"

/*-----------------------------------------------------------------------------
	�ÓI�ϐ�
-----------------------------------------------------------------------------*/
CScene *CScene::m_Top[] = { NULL };		//	�擪�̃|�C���^

/*-----------------------------------------------------------------------------
 �֐���:	CScene::CScene(int Priolity)
 ����:		int Priolity	�D��x
 �߂�l:	
 ����:		�R���X�g���N�^
-----------------------------------------------------------------------------*/
CScene::CScene(int Priolity)
{
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	���W

	m_objType = OBJTYPE_NONE;	//	�I�u�W�F�N�g�̎��

	m_Delete = false;	//	�폜�t���O


	if (m_Top[Priolity] == NULL)
	{

		m_Top[Priolity] = this;

	}
	else
	{

		CScene *Scene = m_Top[Priolity];

		while (Scene->m_Next != NULL)
		{

			//	m_Next�̎w��������̃|�C���^�����Ă���
			Scene = Scene->m_Next;

		}

		Scene->m_Next = this;

	}

	this->m_Next = NULL;
}

/*-----------------------------------------------------------------------------
 �֐���:	void CScene::UpdateAll(void)
 ����:		
 �߂�l:	
 ����:		�S�I�u�W�F�N�g�̍X�V
-----------------------------------------------------------------------------*/
void CScene::UpdateAll(void)
{
/*
	for (int CntPriolity = 0; CntPriolity < PRIOLITY_MAX; CntPriolity++)
	{

		CScene *Scene = m_Top[CntPriolity];
		CScene *ScenePrev = m_Top[CntPriolity];	//	�O�̃V�[���|�C���^
		CScene *SceneNext;			//	���̃V�[���|�C���^

		while (Scene != NULL)
		{
			Scene->Update();	//	�X�V

			Scene = Scene->m_Next;
		}

		while (Scene != NULL)
		{	//	���X�g�\����1�����ׂĂ���

			SceneNext = Scene->m_Next;

			if (Scene->m_Delete == true)
			{	//	�폜�t���O��true��������

				if (Scene == m_Top[CntPriolity])
				{
					m_Top[CntPriolity] = Scene->m_Next;
				}
				else
				{					
					ScenePrev->m_Next = Scene->m_Next;	//	���X�g�\���̂Ȃ��ς�
				}

				Scene->Uninit();	//	�I��
				delete Scene;		//	�폜
			}
			else
			{
				ScenePrev = Scene;
			}
			Scene = SceneNext;
		}
	}
	*/
	for (int i = 0; i < PRIOLITY_MAX; i++)
	{
		CScene *scene = m_Top[i];
		CScene *scenePrev = m_Top[i];
		CScene *sceneNext = NULL;

		while (scene != NULL)
		{
			// �폜�˗�����ĂȂ����m�͍X�V
			if (!scene->m_Delete)scene->Update();
			scene = scene->m_Next;
		}

		scene = m_Top[i];
		while (scene != NULL)
		{
			sceneNext = scene->m_Next;

			if (scene->m_Delete == true)
			{
				if (scene == m_Top[i])
				{
					// �擪��j�����鏀��
					m_Top[i] = scene->m_Next;
				}
				else
				{
					// ���X�g�\���̂Ȃ��ς�
					scenePrev->m_Next = scene->m_Next;
				}

				// �j��
				delete scene;
				scene = NULL;

			}
			else
			{
				scenePrev = scene;
			}

			// �i�߂�
			scene = sceneNext;

		}
	}
}

/*-----------------------------------------------------------------------------
 �֐���:	void CScene::DrawAll(void)
 ����:		
 �߂�l:	
 ����:		�S�I�u�W�F�N�g�̕`��
-----------------------------------------------------------------------------*/
void CScene::DrawAll(void)
{

	for (int CntPriolity = 0; CntPriolity < PRIOLITY_MAX; CntPriolity++)
	{
		CScene *Scene = m_Top[CntPriolity];

		while (Scene != NULL)
		{			
			Scene->Draw();	//	�`��
		
			Scene = Scene->m_Next;	//	�����w�������|�C���^���i�[
		}
	}
}

/*-----------------------------------------------------------------------------
 �֐���:	void CScene::ReleaseAll( void )
 ����:		
 �߂�l:	
 ����:		�S�I�u�W�F�N�g�̉��
-----------------------------------------------------------------------------*/
void CScene::ReleaseAll(void)
{

	for (int CntPriolity = 0; CntPriolity < PRIOLITY_MAX; CntPriolity++)
	{

		CScene *Scene = m_Top[CntPriolity];
		CScene *SceneNext;

		while (Scene != NULL)
		{
	
			SceneNext = Scene->m_Next;	//	���̃|�C���^��ۑ�
			
			Scene->Uninit();	//	�I��

			delete Scene;	//	�V�[���̃f���[�g

			Scene = SceneNext;	//	�V�[���Ɏ��̃V�[��������

		}	
		m_Top[ CntPriolity ] = NULL;	//	�g�b�v��NULL�������
	}
}
