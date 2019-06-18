//=============================================================================
//
// �T�E���h���� [sound.h]
// Author : AKIRA TANAKA
//
//=============================================================================
#ifndef _SOUND_H_
#define _SOUND_H_

#include "DirectX.h"

//*********************************************************
// �T�E���h�N���X
//*********************************************************
class CSound
{
public:
	CSound();	//	�R���X�g���N�^
	~CSound();	//	�f�X�X�g���N�^

	// �T�E���h�t�@�C��
	typedef enum
	{
		SOUND_LABEL_BGM_TITLE = 0,	// BGM
		SOUND_LABEL_SE_TOMATO,	//	�g�}�g��
		SOUND_LABEL_SE_DEATH,		//	���ꐺ
		SOUND_LABEL_SE_MODE,		//�J��
		SOUND_LABEL_SE_GAMECLEAR,//	��C
		SOUND_LABEL_MAX

	} SOUND_LABEL;

	HRESULT Init(void);	//	������
	void Uninit(void);		//	�I��

	HRESULT Play(SOUND_LABEL label);					//	���y�Đ�
	void Stop(SOUND_LABEL label);						//	���Ԗڂ̉����~�߂�
	void Stop(void);									//	��~
	void SetVolume(SOUND_LABEL label, float fValue);	//	�{�����[���ݒ�

private:
	// �p�����[�^�\����
	typedef struct
	{
		char *pFilename;	// �t�@�C����
		int nCntLoop;		// ���[�v�J�E���^

	} PARAM;

	HRESULT CheckChunk(HANDLE hFile, DWORD dwFormat, DWORD *pChunkSize, DWORD *pChunkDataPosition);
	HRESULT ReadChunkData(HANDLE hFile, void *pBuffer, DWORD dwBuffersize, DWORD dwBufferoffset);

	IXAudio2 *m_pXAudio2;									// XAudio2�I�u�W�F�N�g�ւ̃C���^�[�t�F�C�X
	IXAudio2MasteringVoice *m_pMasteringVoice;				// �}�X�^�[�{�C�X
	IXAudio2SourceVoice *m_apSourceVoice[SOUND_LABEL_MAX];	// �\�[�X�{�C�X
	BYTE *m_apDataAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^
	DWORD m_aSizeAudio[SOUND_LABEL_MAX];					// �I�[�f�B�I�f�[�^�T�C�Y

	static PARAM m_aParam[SOUND_LABEL_MAX];					// �p�����[�^
};
#endif
