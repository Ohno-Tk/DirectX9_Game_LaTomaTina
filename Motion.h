/*=============================================================================

		���[�V����[ Motion.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/07
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/27
=============================================================================*/

/*-----------------------------------------------------------------------------
	��d�C���N���[�h�h�~
-----------------------------------------------------------------------------*/
#ifndef _MOTION_H_
#define _MOTION_H_

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include <stdio.h>

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define MOTION_PATH "data/MOTION/"	//	���[�V�����p�X
#define MAX_MOTION (10)	//	�ő僂�[�V������

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CMotion:public CScene
{
public:
	CMotion(int Priolity);	//	�R���X�g���N�^
	~CMotion();

	static CMotion *Create(const int priolity, char *FileName);	//	����

	virtual void Init(void)override;	//	������
	virtual void Uninit(void)override;	//	�I��
	virtual void Update(void)override;	//	�X�V
	virtual void Draw(void)override;	//	�`��

	//	Setter
	void SetFileName(char *data) { m_TextFileName = data; }	//	�t�@�C�����̃Z�b�g
	void SetMotionIndex(const int index);	//	���[�V�����ԍ��̃Z�b�g
	void SetMotionPosition(const int index, const D3DXVECTOR3 pos) { m_CharInfo[index].OffsetPos = pos; }	//	���W
	void SetMotionRotation(const int index, const D3DXVECTOR3 rot) { m_CharInfo[index].OffsetRot = rot; }	//	��]

																											//	Getter
	D3DXVECTOR3 GetMotionPosition(const int index) 
	{
		return m_CharInfo[index].OffsetPos;
	}	//	���W
	D3DXVECTOR3 *GetMotionPositionPointer(const int index) { return &m_CharInfo[index].OffsetPos; }	//	���W�̃|�C���^
	D3DXVECTOR3 GetMotionRotation(const int index) { return m_CharInfo[index].OffsetRot; }	//	��]

private:
	void SetWorld(const int cntmodel, LPDIRECT3DDEVICE9 Device);	//	���[���h���W�ϊ�
	void ReadText(void);											//	�e�L�X�g�t�@�C���̓ǂݍ���
	void ReadNumModel(FILE *fp);									//	���f�����̓ǂݍ���
	void ReadModelFileName(FILE *fp);								//	���f���t�@�C�����̓ǂݍ���
	void LoadModel(const int nummodel, char *modelfilename);		//	���f���̃��[�h
	void ReadCharacterInfo(FILE *fp);								//	�L�����N�^���̓ǂݍ���
	void ReadPartsSet(FILE *fp);									//	�L�����N�^�̃p�[�c���̓ǂݍ���
	void ReadMotion(FILE *fp);										//	���[�V�������̓ǂݍ���

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
		int					Index;		//	�p�[�c�ԍ�
		int					Parent;		//	�e�q�\��
		D3DXVECTOR3			OffsetPos;	//	�������W
		D3DXVECTOR3			OffsetRot;	//	������]
		D3DXVECTOR3			MovePos;	//	��Ԉړ���
		D3DXVECTOR3			MoveRot;	//	��ԉ�]��
		D3DXVECTOR3			Pos;		//	��ԍ��W
		D3DXVECTOR3			Rot;		//	��ԉ�]
		D3DXMATRIX			MtxWorld;	//	���[���h�}�g���b�N�X
		D3DXMATRIX			MtxScl;		//	�g��}�g���N�X
		D3DXMATRIX			MtxRot;		//	��]�}�g���N�X
		D3DXMATRIX			MtxPos;		//	���W�}�g���N�X
		LPD3DXBUFFER		BuffMat;	//	�}�e���A�����
		D3DXMATERIAL		*Mat;		//	�}�e���A���|�C���^
		LPD3DXMESH			Mesh;		//	���b�V�����
		DWORD				NumMat;		//	�}�e���A�����̐�
		LPDIRECT3DTEXTURE9	*Texture;	//	�e�N�X�`���̃|�C���^
	};

	struct MOTION
	{
		int Loop;		//	���[�v���邩
		int NumKey;		//	�L�[��
		int *Frame;		//	�t���[����
		KEYINFO *Next;	//	���̏ꏊ
	};

	int m_NumModel;		//	���f����
	int m_MotionIndex;	//	���[�V�����ԍ�
	int m_NumKey;		//	�L�[��
	int m_UpdateCount;	//	�X�V�̃J�E���^

	static char* m_FileToken[MAX_TOKEN];	//	�g�[�N��
	static char CMotion::m_Buff[256];		//	�e�L�X�g�f�[�^�ǂݍ��݂̃o�b�t�@
	char* m_TextFileName;	//	�e�L�X�g�̃t�@�C����
	char* m_ModelFileName;

	CHARPARTSSET *m_CharInfo;		//	�L�����N�^�[���
	MOTION m_Motion[MAX_MOTION];	//	���[�V�������
};
#endif
