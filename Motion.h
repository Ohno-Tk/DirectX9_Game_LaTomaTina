/*=============================================================================

		モーション[ Motion.h ]

-------------------------------------------------------------------------------
	■　製作者
		大野拓也

	■　作成日
		2017/08/07
------------------------------------------------------------------------------- 
	■　更新日
		2017/08/27
=============================================================================*/

/*-----------------------------------------------------------------------------
	二重インクルード防止
-----------------------------------------------------------------------------*/
#ifndef _MOTION_H_
#define _MOTION_H_

/*-----------------------------------------------------------------------------
	ヘッダファイル
-----------------------------------------------------------------------------*/
#include <stdio.h>

/*-----------------------------------------------------------------------------
	定数定義
-----------------------------------------------------------------------------*/
#define MOTION_PATH "data/MOTION/"	//	モーションパス
#define MAX_MOTION (10)	//	最大モーション数

/*-----------------------------------------------------------------------------
	クラス
-----------------------------------------------------------------------------*/
class CMotion:public CScene
{
public:
	CMotion(int Priolity);	//	コンストラクタ
	~CMotion();

	static CMotion *Create(const int priolity, char *FileName);	//	生成

	virtual void Init(void)override;	//	初期化
	virtual void Uninit(void)override;	//	終了
	virtual void Update(void)override;	//	更新
	virtual void Draw(void)override;	//	描画

	//	Setter
	void SetFileName(char *data) { m_TextFileName = data; }	//	ファイル名のセット
	void SetMotionIndex(const int index);	//	モーション番号のセット
	void SetMotionPosition(const int index, const D3DXVECTOR3 pos) { m_CharInfo[index].OffsetPos = pos; }	//	座標
	void SetMotionRotation(const int index, const D3DXVECTOR3 rot) { m_CharInfo[index].OffsetRot = rot; }	//	回転

																											//	Getter
	D3DXVECTOR3 GetMotionPosition(const int index) 
	{
		return m_CharInfo[index].OffsetPos;
	}	//	座標
	D3DXVECTOR3 *GetMotionPositionPointer(const int index) { return &m_CharInfo[index].OffsetPos; }	//	座標のポインタ
	D3DXVECTOR3 GetMotionRotation(const int index) { return m_CharInfo[index].OffsetRot; }	//	回転

private:
	void SetWorld(const int cntmodel, LPDIRECT3DDEVICE9 Device);	//	ワールド座標変換
	void ReadText(void);											//	テキストファイルの読み込み
	void ReadNumModel(FILE *fp);									//	モデル数の読み込み
	void ReadModelFileName(FILE *fp);								//	モデルファイル名の読み込み
	void LoadModel(const int nummodel, char *modelfilename);		//	モデルのロード
	void ReadCharacterInfo(FILE *fp);								//	キャラクタ情報の読み込み
	void ReadPartsSet(FILE *fp);									//	キャラクタのパーツ情報の読み込み
	void ReadMotion(FILE *fp);										//	モーション情報の読み込み

private:
	enum TOKEN
	{
		SCRIPT = 0,
		END_SCRIPT,
		NUM_MODEL,
		MODEL_FILENAME,
		CHARACTERSET,
		END_CHARACTERSET,
		PARTSSET,
		END_PARTSSET,
		INDEX,
		PARENT,
		POS,
		ROT,
		MOTIONSET,
		END_MOTIONSET,
		LOOP,
		NUMKEY,
		KEYSET,
		END_KEYSET,
		FRAME,
		KEY,
		END_KEY,
		EQUAL,
		LAST_WORD,
		MAX_TOKEN
	};

	struct KEYINFO
	{
		D3DXVECTOR3 *Pos;
		D3DXVECTOR3 *Rot;
	};

	struct CHARPARTSSET
	{
		int					Index;		//	パーツ番号
		int					Parent;		//	親子構造
		D3DXVECTOR3			OffsetPos;	//	初期座標
		D3DXVECTOR3			OffsetRot;	//	初期回転
		D3DXVECTOR3			MovePos;	//	補間移動量
		D3DXVECTOR3			MoveRot;	//	補間回転量
		D3DXVECTOR3			Pos;		//	補間座標
		D3DXVECTOR3			Rot;		//	補間回転
		D3DXMATRIX			MtxWorld;	//	ワールドマトリックス
		D3DXMATRIX			MtxScl;		//	拡大マトリクス
		D3DXMATRIX			MtxRot;		//	回転マトリクス
		D3DXMATRIX			MtxPos;		//	座標マトリクス
		LPD3DXBUFFER		BuffMat;	//	マテリアル情報
		D3DXMATERIAL		*Mat;		//	マテリアルポインタ
		LPD3DXMESH			Mesh;		//	メッシュ情報
		DWORD				NumMat;		//	マテリアル情報の数
		LPDIRECT3DTEXTURE9	*Texture;	//	テクスチャのポインタ
	};

	struct MOTION
	{
		int Loop;		//	ループするか
		int NumKey;		//	キー数
		int *Frame;		//	フレーム数
		KEYINFO *Next;	//	次の場所
	};

	int m_NumModel;		//	モデル数
	int m_MotionIndex;	//	モーション番号
	int m_NumKey;		//	キー数
	int m_UpdateCount;	//	更新のカウンタ

	static char* m_FileToken[MAX_TOKEN];	//	トークン
	static char CMotion::m_Buff[256];		//	テキストデータ読み込みのバッファ
	char* m_TextFileName;	//	テキストのファイル名
	char* m_ModelFileName;

	CHARPARTSSET *m_CharInfo;		//	キャラクター情報
	MOTION m_Motion[MAX_MOTION];	//	モーション情報
};
#endif
