/*=============================================================================

		モーション[ Motion.cpp ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/07
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/07
=============================================================================*/

/*-----------------------------------------------------------------------------
	warning防止
-----------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Manager.h"
#include "FileManager.h"
#include "ModelManager.h"
#include "Scene.h"
#include "Motion.h"

/*-----------------------------------------------------------------------------
	定数定義
-----------------------------------------------------------------------------*/
#define TEXTURE_PATH "data/TEXTURE/"	//	テクスチャのパス

/*-----------------------------------------------------------------------------
	静的メンバ変数
-----------------------------------------------------------------------------*/
char CMotion::m_Buff[] = {};
char *CMotion::m_FileToken[MAX_TOKEN] = {
	"SCRIPT",
	"END_SCRIPT",
	"NUM_MODEL",
	"MODEL_FILENAME",
	"CHARACTERSET",
	"END_CHARACTERSET",
	"PARTSSET",
	"END_PARTSSET",
	"INDEX",
	"PARENT",
	"POS",
	"ROT",
	"MOTIONSET",
	"END_MOTIONSET",
	"LOOP",
	"NUM_KEY",
	"KEYSET",
	"END_KEYSET",
	"FRAME",
	"KEY",
	"END_KEY",
	"=",
	"この行は絶対消さないこと！",
};

/*-----------------------------------------------------------------------------
 関数名:	CMotion::CMotion(int Priolity)
 引数:		int Priolity	優先度
 戻り値:	
 説明:		コンストラクタ
-----------------------------------------------------------------------------*/
CMotion::CMotion(int Priolity):CScene(Priolity)
{

	m_NumModel = 0;		//	モデル数
	m_MotionIndex = 0;	//	モーション番号
	m_NumKey = 0;		//	キー数
	m_UpdateCount = 0;	//	更新のカウンタ

	m_TextFileName = NULL;	//	テキストのファイル名
	m_ModelFileName = NULL;
	m_CharInfo = NULL;	//	キャラクター情報

	//	モーション情報
	for(int i = 0 ; i < MAX_MOTION ; i++)
	{
		m_Motion[i].Loop = 0;		//	ループするか
		m_Motion[i].NumKey = 0;		//	キー数
		m_Motion[i].Frame = NULL;	//	フレーム数
		m_Motion[i].Next = NULL;	//	次の場所
	}
}

CMotion::~CMotion()
{
	for (int i = 0; i < MAX_MOTION; i++)
	{
		for (int j = 0; j < m_Motion[i].NumKey; j++)
		{
			if (m_Motion[i].Next[j].Pos != NULL)
			{	//	座標

				delete m_Motion[i].Next[j].Pos;	//	解放
				m_Motion[i].Next[j].Pos = NULL;
			}

			if (m_Motion[i].Next[j].Rot != NULL)
			{	//	回転

				delete m_Motion[i].Next[j].Rot;	//	解放
				m_Motion[i].Next[j].Rot = NULL;
			}
		}

		if (m_Motion[i].Frame != NULL)
		{	//	ループするか

			delete m_Motion[i].Frame;	//	解放
			m_Motion[i].Frame = NULL;
		}

		if (m_Motion[i].Next != NULL)
		{	//	次の場所

			delete m_Motion[i].Next;	//	解放
			m_Motion[i].Next = NULL;
		}
	}

	for (int i = 0; i < m_NumModel; i++)
	{

		if (m_CharInfo[i].Mesh != NULL)
		{	//	メッシュ情報

			m_CharInfo[i].Mesh->Release();	//	解放
			m_CharInfo[i].Mesh = NULL;
		}

		if (m_CharInfo[i].BuffMat != NULL)
		{	//	マテリアル情報

			m_CharInfo[i].BuffMat->Release();	//	解放
			m_CharInfo[i].BuffMat = NULL;
		}
	}

	if (m_CharInfo != NULL)
	{	//	キャラクター情報

		delete[] m_CharInfo;	//	解放
		m_CharInfo = NULL;
	}
}

/*-----------------------------------------------------------------------------
 関数名:	CMotion *CMotion::Create(const int priolity, char *FileName)
 引数:		const int priolity		優先度
			char *FileName			ファイル名
 戻り値:	
 説明:		生成
-----------------------------------------------------------------------------*/
CMotion *CMotion::Create(const int priolity, char *FileName)
{
	CMotion *motion;

	motion = new CMotion(priolity);

	motion->m_TextFileName = FileName;	//	ファイル名

	motion->Init();	//	初期化

	return motion;
}

/*-----------------------------------------------------------------------------
 関数名:	void CMotion::Init( void )
 引数:		
 戻り値:	
 説明:		初期化
-----------------------------------------------------------------------------*/
void CMotion::Init( void )
{
	ReadText();	//	テキストファイルの読み込み
}

/*-----------------------------------------------------------------------------
 関数名:	void CMotion::Uninit( void )
 引数:		
 戻り値:	
 説明:		終了
-----------------------------------------------------------------------------*/
void CMotion::Uninit( void )
{
	for (int i = 0; i < m_NumModel; i++)
	{
		for (int j = 0; j < (int)m_CharInfo[i].NumMat; j++)
		{
			if (m_CharInfo[i].Texture[j] != NULL)
			{	//	テクスチャ

				m_CharInfo[i].Texture[j]->Release();	//	解放
				m_CharInfo[i].Texture[j] = NULL;
			}
		}

		delete[] m_CharInfo[i].Texture;	//	解放
	}

	CScene::Release();	//	オブジェクトの解放
}

/*-----------------------------------------------------------------------------
 関数名:	void CMotion::Update( void )
 引数:		
 戻り値:	
 説明:		更新
-----------------------------------------------------------------------------*/
void CMotion::Update( void )
{
	// 各モデルの座標と角度を更新
	for(int i = 0 ; i < m_NumModel ; i++)
	{
		m_CharInfo[i].Pos += m_CharInfo[i].MovePos;
		m_CharInfo[i].Rot += m_CharInfo[i].MoveRot;
	}

	if(m_Motion[m_MotionIndex].Frame[m_NumKey] < m_UpdateCount)
	{	//	モーションのフレーム数を超えたら

		if(m_Motion[m_MotionIndex].Loop == 0 && m_Motion[m_MotionIndex].NumKey <= m_NumKey)
		{
			m_NumKey = 0;
		}

		// 差分を計算して、移動量を出す
		for(int i = 0 ; i < m_NumModel ; i++)
		{
			// 座標
			m_CharInfo[i].MovePos.x = (m_Motion[m_MotionIndex].Next[m_NumKey].Pos[i].x - m_CharInfo[i].Pos.x) / m_Motion[m_MotionIndex].Frame[m_NumKey];
			m_CharInfo[i].MovePos.y = (m_Motion[m_MotionIndex].Next[m_NumKey].Pos[i].y - m_CharInfo[i].Pos.y) / m_Motion[m_MotionIndex].Frame[m_NumKey];
			m_CharInfo[i].MovePos.z = (m_Motion[m_MotionIndex].Next[m_NumKey].Pos[i].z - m_CharInfo[i].Pos.z) / m_Motion[m_MotionIndex].Frame[m_NumKey];

			// 角度
			m_CharInfo[i].MoveRot.x = (m_Motion[m_MotionIndex].Next[m_NumKey].Rot[i].x - m_CharInfo[i].Rot.x) / m_Motion[m_MotionIndex].Frame[m_NumKey];
			m_CharInfo[i].MoveRot.y = (m_Motion[m_MotionIndex].Next[m_NumKey].Rot[i].y - m_CharInfo[i].Rot.y) / m_Motion[m_MotionIndex].Frame[m_NumKey];
			m_CharInfo[i].MoveRot.z = (m_Motion[m_MotionIndex].Next[m_NumKey].Rot[i].z - m_CharInfo[i].Rot.z) / m_Motion[m_MotionIndex].Frame[m_NumKey];
		}

		m_UpdateCount = 0;
		m_NumKey++;

		//	ループするかどうか
		if(m_Motion[m_MotionIndex].Loop == 1 && m_NumKey == m_Motion[m_MotionIndex].NumKey)
		{
			m_NumKey = 0;
		}
	}

	m_UpdateCount++;
}

/*-----------------------------------------------------------------------------
 関数名:	void CMotion::Draw( void )
 引数:		
 戻り値:	
 説明:		描画
-----------------------------------------------------------------------------*/
void CMotion::Draw( void )
{
	//	デバイスの取得
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();

	//	現在デバイスに設定されているマテリアル情報の取得
	D3DMATERIAL9 matDef;
	Device->GetMaterial(&matDef);

	for(int i = 0 ; i < m_NumModel ; i++)
	{

		//	ワールド座標変換
		SetWorld(i, Device);

		for(int j = 0 ; j < (int)m_CharInfo[i].NumMat ; j++)
		{
			//	デバイスにマテリアルを設定
			Device->SetMaterial(&m_CharInfo[i].Mat[j].MatD3D);

			//	テクスチャ設定
			Device->SetTexture(0, m_CharInfo[i].Texture[j]);

			//	描画
			m_CharInfo[i].Mesh->DrawSubset(j);
		}
		Device->SetMaterial(&matDef);
	}
}

/*-----------------------------------------------------------------------------
 関数名:	void CMotion::SetWorld(const int cntmodel, LPDIRECT3DDEVICE9 Device)
 引数:		const int cntmodel			モデル数カウンタ
			LPDIRECT3DDEVICE9 Device	デバイス
 戻り値:	
 説明:		ワールド座標変換
-----------------------------------------------------------------------------*/
void CMotion::SetWorld(const int cntmodel, LPDIRECT3DDEVICE9 Device)
{

	D3DXMatrixIdentity(&m_CharInfo[cntmodel].MtxWorld);	//	行列を単位行列にする

	//	拡大行列を作る
	D3DXMatrixScaling(&m_CharInfo[cntmodel].MtxScl,	//拡大行列が作られる
		1.0f,								//	X軸拡大
		1.0f,								//	Y軸拡大
		1.0f);								//	Z軸拡大

	//	回転行列を作る
	D3DXMatrixRotationYawPitchRoll(&m_CharInfo[cntmodel].MtxRot,	//	回転行列が作られる
		m_CharInfo[cntmodel].Rot.y + m_CharInfo[cntmodel].OffsetRot.y,		//	Y軸回転
		m_CharInfo[cntmodel].Rot.x + m_CharInfo[cntmodel].OffsetRot.x,		//	X軸回転
		m_CharInfo[cntmodel].Rot.z + m_CharInfo[cntmodel].OffsetRot.z);		//	Z軸回転

	//	平行移動行列を作る
	D3DXMatrixTranslation(&m_CharInfo[cntmodel].MtxPos,	//	平行移動行列が作られる
		m_CharInfo[cntmodel].Pos.x + m_CharInfo[cntmodel].OffsetPos.x,	//	X軸移動
		m_CharInfo[cntmodel].Pos.y + m_CharInfo[cntmodel].OffsetPos.y,	//	Y軸移動
		m_CharInfo[cntmodel].Pos.z + m_CharInfo[cntmodel].OffsetPos.z);	//	Z軸移動

	//	マトリクスを掛ける
	D3DXMatrixMultiply(&m_CharInfo[cntmodel].MtxWorld, &m_CharInfo[cntmodel].MtxWorld, &m_CharInfo[cntmodel].MtxScl);
	D3DXMatrixMultiply(&m_CharInfo[cntmodel].MtxWorld, &m_CharInfo[cntmodel].MtxWorld, &m_CharInfo[cntmodel].MtxRot);
	D3DXMatrixMultiply(&m_CharInfo[cntmodel].MtxWorld, &m_CharInfo[cntmodel].MtxWorld, &m_CharInfo[cntmodel].MtxPos);

	if(m_CharInfo[cntmodel].Parent != -1)
	{	//	親子構造が-1だったら

		D3DXMatrixMultiply(&m_CharInfo[cntmodel].MtxWorld, &m_CharInfo[cntmodel].MtxWorld, &m_CharInfo[m_CharInfo[cntmodel].Parent].MtxWorld);
	}

	//	デバイスにワールド変換行列を設定
	Device -> SetTransform( D3DTS_WORLD, &m_CharInfo[cntmodel].MtxWorld);
}

/*-----------------------------------------------------------------------------
 関数名:	void CMotion::SetMotionIndex(const int index)
 引数:		int index	番号
 戻り値:	
 説明:		モーション番号のセット
-----------------------------------------------------------------------------*/
void CMotion::SetMotionIndex(const int index)
{
	if(m_MotionIndex == index) return;

	m_MotionIndex = index;
	m_UpdateCount = 0;
	m_NumKey = 0;
}

/*-----------------------------------------------------------------------------
 関数名:	void CMotion::ReadText(void)
 引数:		
 戻り値:	
 説明:		テキストファイルの読み込み
-----------------------------------------------------------------------------*/
void CMotion::ReadText(void)
{

	FILE *fp = CManager::GetFileManager()->OpenFile(m_TextFileName, "rt");

	while(1)
	{
		fscanf( fp , "%s" , m_Buff );

		if(strcmp( m_Buff , m_FileToken[SCRIPT] ) == 0)
		{	//	SCRIPTの検索

			ReadNumModel(fp);		//	モデル数の読み込み
			ReadModelFileName(fp);	//	モデルファイル名の読み込み
			ReadCharacterInfo(fp);	//	キャラクタ情報の読み込み
			ReadMotion(fp);			//	モーション情報の読み込み
		}

		//	END_SCRIPTの検索
		else if(strcmp( m_Buff , m_FileToken[LAST_WORD] ) == 0) break;
	}

	CManager::GetFileManager()->CloseFile(fp);	//	ファイルを閉じる
}

/*-----------------------------------------------------------------------------
 関数名:	void CMotion::ReadNumModel(FILE *fp)
 引数:		FILE *fp	ファイルポインタ
 戻り値:	
 説明:		モデル数の読み込み
-----------------------------------------------------------------------------*/
void CMotion::ReadNumModel(FILE *fp)
{
	while( 1 )
	{
		fscanf( fp , "%s" , m_Buff );

		if(strcmp( m_Buff , m_FileToken[NUM_MODEL] ) == 0)
		{	//	NUM_MODELの検索

			fscanf( fp , "%s" , m_Buff );

			if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
			{	//	=の検索

				fscanf( fp , "%d" , &m_NumModel );	//	モデル数の読み込み

				m_CharInfo = new CHARPARTSSET[m_NumModel];

				for(int i = 0 ; i < m_NumModel ; i++)
				{	//	初期化
					m_CharInfo[i].Index = 0;								//	パーツ番号
					m_CharInfo[i].Parent = 0;								//	親子構造
					m_CharInfo[i].OffsetPos = D3DXVECTOR3(0.0f,0.0f,0.0f);	//	初期座標
					m_CharInfo[i].OffsetRot = D3DXVECTOR3(0.0f,0.0f,0.0f);	//	初期回転
					m_CharInfo[i].MovePos = D3DXVECTOR3(0.0f,0.0f,0.0f);	//	移動量
					m_CharInfo[i].MoveRot = D3DXVECTOR3(0.0f,0.0f,0.0f);	//	回転量
					m_CharInfo[i].Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);		//	座標
					m_CharInfo[i].Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);		//	回転
/*					m_CharInfo[i].Texture = NULL;							//	テクスチャのポインタ
					m_CharInfo[i].Mesh = NULL;								//	メッシュ情報
					m_CharInfo[i].BuffMat = NULL;							//	マテリアル情報
*/				
				}

				break;
			}
		}
	}
}

/*-----------------------------------------------------------------------------
 関数名:	void CMotion::ReadModelFileName(FILE *fp)
 引数:		FILE *fp	ファイルポインタ
 戻り値:	
 説明:		モデルファイル名の読み込み
-----------------------------------------------------------------------------*/
void CMotion::ReadModelFileName(FILE *fp)
{

	int nummodel = 0;
	char ModelFileName[256];

	while(nummodel != m_NumModel)
	{	//	モデル数分

		fscanf( fp , "%s" , m_Buff );

		if(strcmp( m_Buff , m_FileToken[MODEL_FILENAME] ) == 0)
		{	//	MODEL_FILENAMEの検索

			fscanf( fp , "%s" , m_Buff );
			if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
			{	//	=の検索

				fscanf(fp, "%s", &ModelFileName);	//	モデルファイル名の読み込み

				LoadModel(nummodel, ModelFileName);		//	モデルのロード

				nummodel++;
			}
		}
	}
}

/*-----------------------------------------------------------------------------
 関数名:	void CMotion::LoadModel(const int nummodel, char *modelfilename)
 引数:		const int nummodel		モデル数のカウンタ
			char *modelfilename		モデルのファイル名
 戻り値:	
 説明:		モデルのロード
-----------------------------------------------------------------------------*/
void CMotion::LoadModel(const int nummodel, char *modelfilename)
{

	//CModelManager* ModelManager = CManager::GetModelManager();

	//m_CharInfo[nummodel].ModelParam = ModelManager->GetModelParam(modelfilename);


	//	デバイスの取得
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();

	HRESULT hr;

	// 読み込み
	hr = D3DXLoadMeshFromX(		modelfilename,		//	ファイル名
								D3DXMESH_SYSTEMMEM,
								Device,				//	デバイス
								NULL,					//	隣接バッファ
								&m_CharInfo[nummodel].BuffMat,			//	マテリアル情報を格納
								NULL,
								&m_CharInfo[nummodel].NumMat,				//	マテリアル数
								&m_CharInfo[nummodel].Mesh );				//	メッシュ

	//	モデルのエラーチェック
	if(FAILED(hr))
	{
		MessageBox( NULL , modelfilename , "Motion.cpp" , MB_OK | MB_ICONHAND );
	}

	//	マテリアル情報のポインタとしてバッファのアドレスを取得
	m_CharInfo[nummodel].Mat = ( D3DXMATERIAL* )m_CharInfo[nummodel].BuffMat->GetBufferPointer();

	//	テクスチャの動的確保
	m_CharInfo[nummodel].Texture = new LPDIRECT3DTEXTURE9[m_CharInfo[nummodel].NumMat];


	for(int j = 0 ; j < (int)m_CharInfo[nummodel].NumMat ; j++)
	{

		m_CharInfo[nummodel].Texture[j] = NULL;

		if(m_CharInfo[nummodel].Mat[j].pTextureFilename)
		{

			char filePath[MAX_PATH];
			strcpy(filePath, TEXTURE_PATH);
			strcat(filePath, m_CharInfo[nummodel].Mat[j].pTextureFilename);

			hr = D3DXCreateTextureFromFile( Device, filePath, &m_CharInfo[nummodel].Texture[j]);

			//	テクスチャのエラーチェック
			if(FAILED(hr))
			{
				MessageBox( NULL , "モデルのテクスチャパスがおかしいです" , "Motion.cpp" , MB_OK | MB_ICONHAND );
			}
		}
	}

}

/*-----------------------------------------------------------------------------
 関数名:	void CMotion::ReadCharacterInfo(FILE *fp)
 引数:		FILE *fp	ファイルポインタ
 戻り値:	
 説明:		キャラクタ情報の読み込み
-----------------------------------------------------------------------------*/
void CMotion::ReadCharacterInfo(FILE *fp)
{
	while( 1 )
	{
		fscanf( fp , "%s" , m_Buff );
		if(strcmp( m_Buff , m_FileToken[CHARACTERSET] ) == 0)
		{	//	CHARACTERSETの検索

			ReadPartsSet(fp);	//	キャラクタのパーツ情報の読み込み
		}

		//	END_CHARACTERSETの検索
		else if(strcmp( m_Buff , m_FileToken[END_CHARACTERSET] ) == 0) break;
	}
}

/*-----------------------------------------------------------------------------
 関数名:	void CMotion::ReadPartsSet(FILE *fp)
 引数:		FILE *fp	ファイルポインタ
 戻り値:	
 説明:		キャラクタのパーツ情報の読み込み
-----------------------------------------------------------------------------*/
void CMotion::ReadPartsSet(FILE *fp)
{
	int nummodel = 0;

	while( nummodel != m_NumModel )
	{	//	モデル数分

		fscanf( fp , "%s" , m_Buff );

		if(strcmp( m_Buff , m_FileToken[PARTSSET] ) == 0)
		{	//	PARTSSETの検索

			while( 1 )
			{
				fscanf( fp , "%s" , m_Buff );

				if(strcmp( m_Buff , m_FileToken[INDEX] ) == 0)
				{	//	INDEXの検索
					fscanf( fp , "%s" , m_Buff );
					if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
					{	//	=の検索

						fscanf( fp , "%d" , &m_CharInfo[nummodel].Index );	//	パーツ番号の読み込み
					}
				}

				else if(strcmp( m_Buff , m_FileToken[PARENT] ) == 0)
				{	//	PARENTの検索
					fscanf( fp , "%s" , m_Buff );
					if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
					{	//	=の検索

						fscanf( fp , "%d" , &m_CharInfo[nummodel].Parent );	//	親子構造の読み込み
					}
				}

				else if(strcmp( m_Buff , m_FileToken[POS] ) == 0)
				{	//	POSの検索
					fscanf( fp , "%s" , m_Buff );
					if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
					{	//	=の検索

						//	座標の読み込み
						fscanf( fp , "%f" , &m_CharInfo[nummodel].OffsetPos.x );
						fscanf( fp , "%f" , &m_CharInfo[nummodel].OffsetPos.y );
						fscanf( fp , "%f" , &m_CharInfo[nummodel].OffsetPos.z );
					}
				}

				else if(strcmp( m_Buff , m_FileToken[ROT] ) == 0)
				{	//	ROTの検索
					fscanf( fp , "%s" , m_Buff );
					if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
					{	//	=の検索

						//	回転の読み込み
						fscanf( fp , "%f" , &m_CharInfo[nummodel].OffsetRot.x );
						fscanf( fp , "%f" , &m_CharInfo[nummodel].OffsetRot.y );
						fscanf( fp , "%f" , &m_CharInfo[nummodel].OffsetRot.z );
					}
					break;
				}
			}
		}

		//	END_PARTSSETの検索
		if(strcmp( m_Buff , m_FileToken[END_PARTSSET] ) == 0)
		{
			nummodel++;
		}
	}
}

/*-----------------------------------------------------------------------------
 関数名:	void CMotion::ReadMotion(FILE *fp)
 引数:		FILE *fp	ファイルポインタ
 戻り値:	
 説明:		モーション情報の読み込み
-----------------------------------------------------------------------------*/
void CMotion::ReadMotion(FILE *fp)
{
	int cntmotion = 0;

	while(cntmotion != MAX_MOTION)
	{	//	モーション数を超えなかったら

		fscanf( fp , "%s" , m_Buff );

		if(strcmp( m_Buff , m_FileToken[MOTIONSET] ) == 0)
		{	//	MOTIONSETの検索

			while( 1 )
			{
				fscanf( fp , "%s" , m_Buff );

				if(strcmp( m_Buff , m_FileToken[LOOP] ) == 0)
				{	//	LOOPの検索
					fscanf( fp , "%s" , m_Buff );
					if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
					{	//	=の検索
						fscanf( fp , "%d" , &m_Motion[cntmotion].Loop );	//	ループするかの読み込み
					}
				}

				else if(strcmp( m_Buff , m_FileToken[NUMKEY] ) == 0)
				{	//	NUM_KEYの検索
					fscanf( fp , "%s" , m_Buff );
					if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
					{	//	=の検索
						fscanf( fp , "%d" , &m_Motion[cntmotion].NumKey );	//	キー数の読み込み

						m_Motion[cntmotion].Frame = new int[m_Motion[cntmotion].NumKey];

						m_Motion[cntmotion].Next = new KEYINFO[ m_Motion[cntmotion].NumKey ];
						for(int i = 0 ; i < m_Motion[cntmotion].NumKey ; i++ )
						{	//	キー数分

							m_Motion[cntmotion].Next[i].Pos = new D3DXVECTOR3[m_NumModel];
							m_Motion[cntmotion].Next[i].Rot = new D3DXVECTOR3[m_NumModel];
						}
						for(int j = 0 ; j < m_Motion[cntmotion].NumKey ; j++ )
						{	//	初期化
							for(int k = 0 ; k < m_NumModel ; k++ )
							{	//	モデル数分

								m_Motion[cntmotion].Next[j].Pos[k].x = 0.0f;
								m_Motion[cntmotion].Next[j].Pos[k].y = 0.0f;
								m_Motion[cntmotion].Next[j].Pos[k].z = 0.0f;
								m_Motion[cntmotion].Next[j].Rot[k].x = 0.0f;
								m_Motion[cntmotion].Next[j].Rot[k].y = 0.0f;
								m_Motion[cntmotion].Next[j].Rot[k].z = 0.0f;
							}
						}
					}
					break;
				}
			}

			int numkey = 0;

			while(numkey != m_Motion[cntmotion].NumKey)
			{	//	キー数分

				fscanf( fp , "%s" , m_Buff );

				if(strcmp( m_Buff , m_FileToken[KEYSET] ) == 0)
				{	//	KEYSETの検索

					int nummodel = 0;

					while( nummodel != m_NumModel )
					{	//	モデル数分

						fscanf( fp , "%s" , m_Buff );

						if(strcmp( m_Buff , m_FileToken[FRAME] ) == 0)
						{	//	FRAMEの検索
							fscanf( fp , "%s" , m_Buff );
							if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
							{	//	=の検索
								fscanf( fp , "%d" , &m_Motion[cntmotion].Frame[numkey] );//	フレーム数の読み込み
							}
						}

						else if(strcmp( m_Buff , m_FileToken[POS] ) == 0)
						{	//	POSの検索
							fscanf( fp , "%s" , m_Buff );
							if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
							{	//	=の検索

								//	座標の読み込み
								fscanf( fp , "%f" , &m_Motion[cntmotion].Next[numkey].Pos[nummodel].x );
								fscanf( fp , "%f" , &m_Motion[cntmotion].Next[numkey].Pos[nummodel].y );
								fscanf( fp , "%f" , &m_Motion[cntmotion].Next[numkey].Pos[nummodel].z );
							}
						}

						else if(strcmp( m_Buff , m_FileToken[ROT] ) == 0)
						{	//	ROTの検索
							fscanf( fp , "%s" , m_Buff );
							if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
							{	//	=の検索

								//	回転の読み込み
								fscanf( fp , "%f" , &m_Motion[cntmotion].Next[numkey].Rot[nummodel].x );
								fscanf( fp , "%f" , &m_Motion[cntmotion].Next[numkey].Rot[nummodel].y );
								fscanf( fp , "%f" , &m_Motion[cntmotion].Next[numkey].Rot[nummodel].z );
							}
						}

						else if(strcmp( m_Buff , m_FileToken[END_KEY] ) == 0)
						{	//	END_KEYの検索
							nummodel++;
						}
					}
				}

				else if(strcmp( m_Buff , m_FileToken[END_KEYSET] ) == 0)
				{	//	END_KEYSETの検索
					numkey++;
				}
			}
		}

		//	END_MOTIONSETの検索
		if(strcmp( m_Buff , m_FileToken[END_MOTIONSET] ) == 0) cntmotion++;

		//	END_SCRIPTの検索
		if(strcmp( m_Buff , m_FileToken[END_SCRIPT] ) == 0) break;
	}
}
