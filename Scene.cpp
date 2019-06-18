/*=============================================================================

		シーン( リスト構造 )[ Scene.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/04/26
-------------------------------------------------------------------------------
	■　更新日
		2017/08/27
=============================================================================*/

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include <stdio.h>
#include "DirectX.h"
#include "Scene.h"

/*-----------------------------------------------------------------------------
	静的変数
-----------------------------------------------------------------------------*/
CScene *CScene::m_Top[] = { NULL };		//	先頭のポインタ

/*-----------------------------------------------------------------------------
 関数名:	CScene::CScene(int Priolity)
 引数:		int Priolity	優先度
 戻り値:	
 説明:		コンストラクタ
-----------------------------------------------------------------------------*/
CScene::CScene(int Priolity)
{
	m_Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//	座標

	m_objType = OBJTYPE_NONE;	//	オブジェクトの種類

	m_Delete = false;	//	削除フラグ


	if (m_Top[Priolity] == NULL)
	{

		m_Top[Priolity] = this;

	}
	else
	{

		CScene *Scene = m_Top[Priolity];

		while (Scene->m_Next != NULL)
		{

			//	m_Nextの指し示す先のポインタを入れている
			Scene = Scene->m_Next;

		}

		Scene->m_Next = this;

	}

	this->m_Next = NULL;
}

/*-----------------------------------------------------------------------------
 関数名:	void CScene::UpdateAll(void)
 引数:		
 戻り値:	
 説明:		全オブジェクトの更新
-----------------------------------------------------------------------------*/
void CScene::UpdateAll(void)
{
/*
	for (int CntPriolity = 0; CntPriolity < PRIOLITY_MAX; CntPriolity++)
	{

		CScene *Scene = m_Top[CntPriolity];
		CScene *ScenePrev = m_Top[CntPriolity];	//	前のシーンポインタ
		CScene *SceneNext;			//	次のシーンポインタ

		while (Scene != NULL)
		{
			Scene->Update();	//	更新

			Scene = Scene->m_Next;
		}

		while (Scene != NULL)
		{	//	リスト構造を1つずつ調べていく

			SceneNext = Scene->m_Next;

			if (Scene->m_Delete == true)
			{	//	削除フラグがtrueだったら

				if (Scene == m_Top[CntPriolity])
				{
					m_Top[CntPriolity] = Scene->m_Next;
				}
				else
				{					
					ScenePrev->m_Next = Scene->m_Next;	//	リスト構造のつなぎ変え
				}

				Scene->Uninit();	//	終了
				delete Scene;		//	削除
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
			// 削除依頼されてないモノは更新
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
					// 先頭を破棄する準備
					m_Top[i] = scene->m_Next;
				}
				else
				{
					// リスト構造のつなぎ変え
					scenePrev->m_Next = scene->m_Next;
				}

				// 破棄
				delete scene;
				scene = NULL;

			}
			else
			{
				scenePrev = scene;
			}

			// 進める
			scene = sceneNext;

		}
	}
}

/*-----------------------------------------------------------------------------
 関数名:	void CScene::DrawAll(void)
 引数:		
 戻り値:	
 説明:		全オブジェクトの描画
-----------------------------------------------------------------------------*/
void CScene::DrawAll(void)
{

	for (int CntPriolity = 0; CntPriolity < PRIOLITY_MAX; CntPriolity++)
	{
		CScene *Scene = m_Top[CntPriolity];

		while (Scene != NULL)
		{			
			Scene->Draw();	//	描画
		
			Scene = Scene->m_Next;	//	次を指し示すポインタを格納
		}
	}
}

/*-----------------------------------------------------------------------------
 関数名:	void CScene::ReleaseAll( void )
 引数:		
 戻り値:	
 説明:		全オブジェクトの解放
-----------------------------------------------------------------------------*/
void CScene::ReleaseAll(void)
{

	for (int CntPriolity = 0; CntPriolity < PRIOLITY_MAX; CntPriolity++)
	{

		CScene *Scene = m_Top[CntPriolity];
		CScene *SceneNext;

		while (Scene != NULL)
		{
	
			SceneNext = Scene->m_Next;	//	次のポインタを保存
			
			Scene->Uninit();	//	終了

			delete Scene;	//	シーンのデリート

			Scene = SceneNext;	//	シーンに次のシーンを入れる

		}	
		m_Top[ CntPriolity ] = NULL;	//	トップにNULLをいれる
	}
}
