//=============================================================================
//
// サウンド処理 [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "DirectX.h"

//*********************************************************
// サウンドクラス
//*********************************************************
class CSound
{
public:
	CSound();	//	コンストラクタ
	~CSound();	//	デスストラクタ

	// サウンドファイル
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,	// BGM
		SOUND_LABEL_SE_TOMATO,	//	トマト音
		SOUND_LABEL_SE_DEATH,		//	やられ声
		SOUND_LABEL_SE_MODE,		//遷移
		SOUND_LABEL_SE_GAMECLEAR,//	大砲
		SOUND_LABEL_MAX

	} SOUND_LABEL;

	HRESULT Init(void);	//	初期化
	void Uninit(void);		//	終了

	HRESULT Play(SOUND_LABEL label);					//	音楽再生
	void Stop(SOUND_LABEL label);						//	何番目の音を止める
	void Stop(void);									//	停止
	void SetVolume(SOUND_LABEL label, float fValue);	//	ボリューム設定

private:
	// パラメータ構造体
	typedef struct
	{
		char *pFilename;	// ファイル名
		int nCntLoop;		// ループカウンタ

	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD dwFormat, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;									// XAudio2オブジェクトへのインターフェイス
	IXAudio2MasteringVoice *m_pMasteringVoice;				// マスターボイス
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// ソースボイス
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// オーディオデータ
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// オーディオデータサイズ

	static PARAM m_aParam[SOUND_LABEL_MAX];					// パラメータ
};
#endif
