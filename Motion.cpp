/*=============================================================================

		���[�V����[ Motion.cpp ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/07
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/07
=============================================================================*/

/*-----------------------------------------------------------------------------
	warning�h�~
-----------------------------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS

/*-----------------------------------------------------------------------------
	�w�b�_�t�@�C��
-----------------------------------------------------------------------------*/
#include "DirectX.h"
#include "Manager.h"
#include "FileManager.h"
#include "ModelManager.h"
#include "Scene.h"
#include "Motion.h"

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define TEXTURE_PATH "data/TEXTURE/"	//	�e�N�X�`���̃p�X

/*-----------------------------------------------------------------------------
	�ÓI�����o�ϐ�
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
	"���̍s�͐�Ώ����Ȃ����ƁI",
};

/*-----------------------------------------------------------------------------
 �֐���:	CMotion::CMotion(int Priolity)
 ����:		int Priolity	�D��x
 �߂�l:	
 ����:		�R���X�g���N�^
-----------------------------------------------------------------------------*/
CMotion::CMotion(int Priolity):CScene(Priolity)
{

	m_NumModel = 0;		//	���f����
	m_MotionIndex = 0;	//	���[�V�����ԍ�
	m_NumKey = 0;		//	�L�[��
	m_UpdateCount = 0;	//	�X�V�̃J�E���^

	m_TextFileName = NULL;	//	�e�L�X�g�̃t�@�C����
	m_ModelFileName = NULL;
	m_CharInfo = NULL;	//	�L�����N�^�[���

	//	���[�V�������
	for(int i = 0 ; i < MAX_MOTION ; i++)
	{
		m_Motion[i].Loop = 0;		//	���[�v���邩
		m_Motion[i].NumKey = 0;		//	�L�[��
		m_Motion[i].Frame = NULL;	//	�t���[����
		m_Motion[i].Next = NULL;	//	���̏ꏊ
	}
}

CMotion::~CMotion()
{
	for (int i = 0; i < MAX_MOTION; i++)
	{
		for (int j = 0; j < m_Motion[i].NumKey; j++)
		{
			if (m_Motion[i].Next[j].Pos != NULL)
			{	//	���W

				delete m_Motion[i].Next[j].Pos;	//	���
				m_Motion[i].Next[j].Pos = NULL;
			}

			if (m_Motion[i].Next[j].Rot != NULL)
			{	//	��]

				delete m_Motion[i].Next[j].Rot;	//	���
				m_Motion[i].Next[j].Rot = NULL;
			}
		}

		if (m_Motion[i].Frame != NULL)
		{	//	���[�v���邩

			delete m_Motion[i].Frame;	//	���
			m_Motion[i].Frame = NULL;
		}

		if (m_Motion[i].Next != NULL)
		{	//	���̏ꏊ

			delete m_Motion[i].Next;	//	���
			m_Motion[i].Next = NULL;
		}
	}

	for (int i = 0; i < m_NumModel; i++)
	{

		if (m_CharInfo[i].Mesh != NULL)
		{	//	���b�V�����

			m_CharInfo[i].Mesh->Release();	//	���
			m_CharInfo[i].Mesh = NULL;
		}

		if (m_CharInfo[i].BuffMat != NULL)
		{	//	�}�e���A�����

			m_CharInfo[i].BuffMat->Release();	//	���
			m_CharInfo[i].BuffMat = NULL;
		}
	}

	if (m_CharInfo != NULL)
	{	//	�L�����N�^�[���

		delete[] m_CharInfo;	//	���
		m_CharInfo = NULL;
	}
}

/*-----------------------------------------------------------------------------
 �֐���:	CMotion *CMotion::Create(const int priolity, char *FileName)
 ����:		const int priolity		�D��x
			char *FileName			�t�@�C����
 �߂�l:	
 ����:		����
-----------------------------------------------------------------------------*/
CMotion *CMotion::Create(const int priolity, char *FileName)
{
	CMotion *motion;

	motion = new CMotion(priolity);

	motion->m_TextFileName = FileName;	//	�t�@�C����

	motion->Init();	//	������

	return motion;
}

/*-----------------------------------------------------------------------------
 �֐���:	void CMotion::Init( void )
 ����:		
 �߂�l:	
 ����:		������
-----------------------------------------------------------------------------*/
void CMotion::Init( void )
{
	ReadText();	//	�e�L�X�g�t�@�C���̓ǂݍ���
}

/*-----------------------------------------------------------------------------
 �֐���:	void CMotion::Uninit( void )
 ����:		
 �߂�l:	
 ����:		�I��
-----------------------------------------------------------------------------*/
void CMotion::Uninit( void )
{
	for (int i = 0; i < m_NumModel; i++)
	{
		for (int j = 0; j < (int)m_CharInfo[i].NumMat; j++)
		{
			if (m_CharInfo[i].Texture[j] != NULL)
			{	//	�e�N�X�`��

				m_CharInfo[i].Texture[j]->Release();	//	���
				m_CharInfo[i].Texture[j] = NULL;
			}
		}

		delete[] m_CharInfo[i].Texture;	//	���
	}

	CScene::Release();	//	�I�u�W�F�N�g�̉��
}

/*-----------------------------------------------------------------------------
 �֐���:	void CMotion::Update( void )
 ����:		
 �߂�l:	
 ����:		�X�V
-----------------------------------------------------------------------------*/
void CMotion::Update( void )
{
	// �e���f���̍��W�Ɗp�x���X�V
	for(int i = 0 ; i < m_NumModel ; i++)
	{
		m_CharInfo[i].Pos += m_CharInfo[i].MovePos;
		m_CharInfo[i].Rot += m_CharInfo[i].MoveRot;
	}

	if(m_Motion[m_MotionIndex].Frame[m_NumKey] < m_UpdateCount)
	{	//	���[�V�����̃t���[�����𒴂�����

		if(m_Motion[m_MotionIndex].Loop == 0 && m_Motion[m_MotionIndex].NumKey <= m_NumKey)
		{
			m_NumKey = 0;
		}

		// �������v�Z���āA�ړ��ʂ��o��
		for(int i = 0 ; i < m_NumModel ; i++)
		{
			// ���W
			m_CharInfo[i].MovePos.x = (m_Motion[m_MotionIndex].Next[m_NumKey].Pos[i].x - m_CharInfo[i].Pos.x) / m_Motion[m_MotionIndex].Frame[m_NumKey];
			m_CharInfo[i].MovePos.y = (m_Motion[m_MotionIndex].Next[m_NumKey].Pos[i].y - m_CharInfo[i].Pos.y) / m_Motion[m_MotionIndex].Frame[m_NumKey];
			m_CharInfo[i].MovePos.z = (m_Motion[m_MotionIndex].Next[m_NumKey].Pos[i].z - m_CharInfo[i].Pos.z) / m_Motion[m_MotionIndex].Frame[m_NumKey];

			// �p�x
			m_CharInfo[i].MoveRot.x = (m_Motion[m_MotionIndex].Next[m_NumKey].Rot[i].x - m_CharInfo[i].Rot.x) / m_Motion[m_MotionIndex].Frame[m_NumKey];
			m_CharInfo[i].MoveRot.y = (m_Motion[m_MotionIndex].Next[m_NumKey].Rot[i].y - m_CharInfo[i].Rot.y) / m_Motion[m_MotionIndex].Frame[m_NumKey];
			m_CharInfo[i].MoveRot.z = (m_Motion[m_MotionIndex].Next[m_NumKey].Rot[i].z - m_CharInfo[i].Rot.z) / m_Motion[m_MotionIndex].Frame[m_NumKey];
		}

		m_UpdateCount = 0;
		m_NumKey++;

		//	���[�v���邩�ǂ���
		if(m_Motion[m_MotionIndex].Loop == 1 && m_NumKey == m_Motion[m_MotionIndex].NumKey)
		{
			m_NumKey = 0;
		}
	}

	m_UpdateCount++;
}

/*-----------------------------------------------------------------------------
 �֐���:	void CMotion::Draw( void )
 ����:		
 �߂�l:	
 ����:		�`��
-----------------------------------------------------------------------------*/
void CMotion::Draw( void )
{
	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();

	//	���݃f�o�C�X�ɐݒ肳��Ă���}�e���A�����̎擾
	D3DMATERIAL9 matDef;
	Device->GetMaterial(&matDef);

	for(int i = 0 ; i < m_NumModel ; i++)
	{

		//	���[���h���W�ϊ�
		SetWorld(i, Device);

		for(int j = 0 ; j < (int)m_CharInfo[i].NumMat ; j++)
		{
			//	�f�o�C�X�Ƀ}�e���A����ݒ�
			Device->SetMaterial(&m_CharInfo[i].Mat[j].MatD3D);

			//	�e�N�X�`���ݒ�
			Device->SetTexture(0, m_CharInfo[i].Texture[j]);

			//	�`��
			m_CharInfo[i].Mesh->DrawSubset(j);
		}
		Device->SetMaterial(&matDef);
	}
}

/*-----------------------------------------------------------------------------
 �֐���:	void CMotion::SetWorld(const int cntmodel, LPDIRECT3DDEVICE9 Device)
 ����:		const int cntmodel			���f�����J�E���^
			LPDIRECT3DDEVICE9 Device	�f�o�C�X
 �߂�l:	
 ����:		���[���h���W�ϊ�
-----------------------------------------------------------------------------*/
void CMotion::SetWorld(const int cntmodel, LPDIRECT3DDEVICE9 Device)
{

	D3DXMatrixIdentity(&m_CharInfo[cntmodel].MtxWorld);	//	�s���P�ʍs��ɂ���

	//	�g��s������
	D3DXMatrixScaling(&m_CharInfo[cntmodel].MtxScl,	//�g��s�񂪍����
		1.0f,								//	X���g��
		1.0f,								//	Y���g��
		1.0f);								//	Z���g��

	//	��]�s������
	D3DXMatrixRotationYawPitchRoll(&m_CharInfo[cntmodel].MtxRot,	//	��]�s�񂪍����
		m_CharInfo[cntmodel].Rot.y + m_CharInfo[cntmodel].OffsetRot.y,		//	Y����]
		m_CharInfo[cntmodel].Rot.x + m_CharInfo[cntmodel].OffsetRot.x,		//	X����]
		m_CharInfo[cntmodel].Rot.z + m_CharInfo[cntmodel].OffsetRot.z);		//	Z����]

	//	���s�ړ��s������
	D3DXMatrixTranslation(&m_CharInfo[cntmodel].MtxPos,	//	���s�ړ��s�񂪍����
		m_CharInfo[cntmodel].Pos.x + m_CharInfo[cntmodel].OffsetPos.x,	//	X���ړ�
		m_CharInfo[cntmodel].Pos.y + m_CharInfo[cntmodel].OffsetPos.y,	//	Y���ړ�
		m_CharInfo[cntmodel].Pos.z + m_CharInfo[cntmodel].OffsetPos.z);	//	Z���ړ�

	//	�}�g���N�X���|����
	D3DXMatrixMultiply(&m_CharInfo[cntmodel].MtxWorld, &m_CharInfo[cntmodel].MtxWorld, &m_CharInfo[cntmodel].MtxScl);
	D3DXMatrixMultiply(&m_CharInfo[cntmodel].MtxWorld, &m_CharInfo[cntmodel].MtxWorld, &m_CharInfo[cntmodel].MtxRot);
	D3DXMatrixMultiply(&m_CharInfo[cntmodel].MtxWorld, &m_CharInfo[cntmodel].MtxWorld, &m_CharInfo[cntmodel].MtxPos);

	if(m_CharInfo[cntmodel].Parent != -1)
	{	//	�e�q�\����-1��������

		D3DXMatrixMultiply(&m_CharInfo[cntmodel].MtxWorld, &m_CharInfo[cntmodel].MtxWorld, &m_CharInfo[m_CharInfo[cntmodel].Parent].MtxWorld);
	}

	//	�f�o�C�X�Ƀ��[���h�ϊ��s���ݒ�
	Device -> SetTransform( D3DTS_WORLD, &m_CharInfo[cntmodel].MtxWorld);
}

/*-----------------------------------------------------------------------------
 �֐���:	void CMotion::SetMotionIndex(const int index)
 ����:		int index	�ԍ�
 �߂�l:	
 ����:		���[�V�����ԍ��̃Z�b�g
-----------------------------------------------------------------------------*/
void CMotion::SetMotionIndex(const int index)
{
	if(m_MotionIndex == index) return;

	m_MotionIndex = index;
	m_UpdateCount = 0;
	m_NumKey = 0;
}

/*-----------------------------------------------------------------------------
 �֐���:	void CMotion::ReadText(void)
 ����:		
 �߂�l:	
 ����:		�e�L�X�g�t�@�C���̓ǂݍ���
-----------------------------------------------------------------------------*/
void CMotion::ReadText(void)
{

	FILE *fp = CManager::GetFileManager()->OpenFile(m_TextFileName, "rt");

	while(1)
	{
		fscanf( fp , "%s" , m_Buff );

		if(strcmp( m_Buff , m_FileToken[SCRIPT] ) == 0)
		{	//	SCRIPT�̌���

			ReadNumModel(fp);		//	���f�����̓ǂݍ���
			ReadModelFileName(fp);	//	���f���t�@�C�����̓ǂݍ���
			ReadCharacterInfo(fp);	//	�L�����N�^���̓ǂݍ���
			ReadMotion(fp);			//	���[�V�������̓ǂݍ���
		}

		//	END_SCRIPT�̌���
		else if(strcmp( m_Buff , m_FileToken[LAST_WORD] ) == 0) break;
	}

	CManager::GetFileManager()->CloseFile(fp);	//	�t�@�C�������
}

/*-----------------------------------------------------------------------------
 �֐���:	void CMotion::ReadNumModel(FILE *fp)
 ����:		FILE *fp	�t�@�C���|�C���^
 �߂�l:	
 ����:		���f�����̓ǂݍ���
-----------------------------------------------------------------------------*/
void CMotion::ReadNumModel(FILE *fp)
{
	while( 1 )
	{
		fscanf( fp , "%s" , m_Buff );

		if(strcmp( m_Buff , m_FileToken[NUM_MODEL] ) == 0)
		{	//	NUM_MODEL�̌���

			fscanf( fp , "%s" , m_Buff );

			if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
			{	//	=�̌���

				fscanf( fp , "%d" , &m_NumModel );	//	���f�����̓ǂݍ���

				m_CharInfo = new CHARPARTSSET[m_NumModel];

				for(int i = 0 ; i < m_NumModel ; i++)
				{	//	������
					m_CharInfo[i].Index = 0;								//	�p�[�c�ԍ�
					m_CharInfo[i].Parent = 0;								//	�e�q�\��
					m_CharInfo[i].OffsetPos = D3DXVECTOR3(0.0f,0.0f,0.0f);	//	�������W
					m_CharInfo[i].OffsetRot = D3DXVECTOR3(0.0f,0.0f,0.0f);	//	������]
					m_CharInfo[i].MovePos = D3DXVECTOR3(0.0f,0.0f,0.0f);	//	�ړ���
					m_CharInfo[i].MoveRot = D3DXVECTOR3(0.0f,0.0f,0.0f);	//	��]��
					m_CharInfo[i].Pos = D3DXVECTOR3(0.0f,0.0f,0.0f);		//	���W
					m_CharInfo[i].Rot = D3DXVECTOR3(0.0f,0.0f,0.0f);		//	��]
/*					m_CharInfo[i].Texture = NULL;							//	�e�N�X�`���̃|�C���^
					m_CharInfo[i].Mesh = NULL;								//	���b�V�����
					m_CharInfo[i].BuffMat = NULL;							//	�}�e���A�����
*/				
				}

				break;
			}
		}
	}
}

/*-----------------------------------------------------------------------------
 �֐���:	void CMotion::ReadModelFileName(FILE *fp)
 ����:		FILE *fp	�t�@�C���|�C���^
 �߂�l:	
 ����:		���f���t�@�C�����̓ǂݍ���
-----------------------------------------------------------------------------*/
void CMotion::ReadModelFileName(FILE *fp)
{

	int nummodel = 0;
	char ModelFileName[256];

	while(nummodel != m_NumModel)
	{	//	���f������

		fscanf( fp , "%s" , m_Buff );

		if(strcmp( m_Buff , m_FileToken[MODEL_FILENAME] ) == 0)
		{	//	MODEL_FILENAME�̌���

			fscanf( fp , "%s" , m_Buff );
			if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
			{	//	=�̌���

				fscanf(fp, "%s", &ModelFileName);	//	���f���t�@�C�����̓ǂݍ���

				LoadModel(nummodel, ModelFileName);		//	���f���̃��[�h

				nummodel++;
			}
		}
	}
}

/*-----------------------------------------------------------------------------
 �֐���:	void CMotion::LoadModel(const int nummodel, char *modelfilename)
 ����:		const int nummodel		���f�����̃J�E���^
			char *modelfilename		���f���̃t�@�C����
 �߂�l:	
 ����:		���f���̃��[�h
-----------------------------------------------------------------------------*/
void CMotion::LoadModel(const int nummodel, char *modelfilename)
{

	//CModelManager* ModelManager = CManager::GetModelManager();

	//m_CharInfo[nummodel].ModelParam = ModelManager->GetModelParam(modelfilename);


	//	�f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 Device = CDirectX::GetDevice();

	HRESULT hr;

	// �ǂݍ���
	hr = D3DXLoadMeshFromX(		modelfilename,		//	�t�@�C����
								D3DXMESH_SYSTEMMEM,
								Device,				//	�f�o�C�X
								NULL,					//	�אڃo�b�t�@
								&m_CharInfo[nummodel].BuffMat,			//	�}�e���A�������i�[
								NULL,
								&m_CharInfo[nummodel].NumMat,				//	�}�e���A����
								&m_CharInfo[nummodel].Mesh );				//	���b�V��

	//	���f���̃G���[�`�F�b�N
	if(FAILED(hr))
	{
		MessageBox( NULL , modelfilename , "Motion.cpp" , MB_OK | MB_ICONHAND );
	}

	//	�}�e���A�����̃|�C���^�Ƃ��ăo�b�t�@�̃A�h���X���擾
	m_CharInfo[nummodel].Mat = ( D3DXMATERIAL* )m_CharInfo[nummodel].BuffMat->GetBufferPointer();

	//	�e�N�X�`���̓��I�m��
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

			//	�e�N�X�`���̃G���[�`�F�b�N
			if(FAILED(hr))
			{
				MessageBox( NULL , "���f���̃e�N�X�`���p�X�����������ł�" , "Motion.cpp" , MB_OK | MB_ICONHAND );
			}
		}
	}

}

/*-----------------------------------------------------------------------------
 �֐���:	void CMotion::ReadCharacterInfo(FILE *fp)
 ����:		FILE *fp	�t�@�C���|�C���^
 �߂�l:	
 ����:		�L�����N�^���̓ǂݍ���
-----------------------------------------------------------------------------*/
void CMotion::ReadCharacterInfo(FILE *fp)
{
	while( 1 )
	{
		fscanf( fp , "%s" , m_Buff );
		if(strcmp( m_Buff , m_FileToken[CHARACTERSET] ) == 0)
		{	//	CHARACTERSET�̌���

			ReadPartsSet(fp);	//	�L�����N�^�̃p�[�c���̓ǂݍ���
		}

		//	END_CHARACTERSET�̌���
		else if(strcmp( m_Buff , m_FileToken[END_CHARACTERSET] ) == 0) break;
	}
}

/*-----------------------------------------------------------------------------
 �֐���:	void CMotion::ReadPartsSet(FILE *fp)
 ����:		FILE *fp	�t�@�C���|�C���^
 �߂�l:	
 ����:		�L�����N�^�̃p�[�c���̓ǂݍ���
-----------------------------------------------------------------------------*/
void CMotion::ReadPartsSet(FILE *fp)
{
	int nummodel = 0;

	while( nummodel != m_NumModel )
	{	//	���f������

		fscanf( fp , "%s" , m_Buff );

		if(strcmp( m_Buff , m_FileToken[PARTSSET] ) == 0)
		{	//	PARTSSET�̌���

			while( 1 )
			{
				fscanf( fp , "%s" , m_Buff );

				if(strcmp( m_Buff , m_FileToken[INDEX] ) == 0)
				{	//	INDEX�̌���
					fscanf( fp , "%s" , m_Buff );
					if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
					{	//	=�̌���

						fscanf( fp , "%d" , &m_CharInfo[nummodel].Index );	//	�p�[�c�ԍ��̓ǂݍ���
					}
				}

				else if(strcmp( m_Buff , m_FileToken[PARENT] ) == 0)
				{	//	PARENT�̌���
					fscanf( fp , "%s" , m_Buff );
					if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
					{	//	=�̌���

						fscanf( fp , "%d" , &m_CharInfo[nummodel].Parent );	//	�e�q�\���̓ǂݍ���
					}
				}

				else if(strcmp( m_Buff , m_FileToken[POS] ) == 0)
				{	//	POS�̌���
					fscanf( fp , "%s" , m_Buff );
					if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
					{	//	=�̌���

						//	���W�̓ǂݍ���
						fscanf( fp , "%f" , &m_CharInfo[nummodel].OffsetPos.x );
						fscanf( fp , "%f" , &m_CharInfo[nummodel].OffsetPos.y );
						fscanf( fp , "%f" , &m_CharInfo[nummodel].OffsetPos.z );
					}
				}

				else if(strcmp( m_Buff , m_FileToken[ROT] ) == 0)
				{	//	ROT�̌���
					fscanf( fp , "%s" , m_Buff );
					if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
					{	//	=�̌���

						//	��]�̓ǂݍ���
						fscanf( fp , "%f" , &m_CharInfo[nummodel].OffsetRot.x );
						fscanf( fp , "%f" , &m_CharInfo[nummodel].OffsetRot.y );
						fscanf( fp , "%f" , &m_CharInfo[nummodel].OffsetRot.z );
					}
					break;
				}
			}
		}

		//	END_PARTSSET�̌���
		if(strcmp( m_Buff , m_FileToken[END_PARTSSET] ) == 0)
		{
			nummodel++;
		}
	}
}

/*-----------------------------------------------------------------------------
 �֐���:	void CMotion::ReadMotion(FILE *fp)
 ����:		FILE *fp	�t�@�C���|�C���^
 �߂�l:	
 ����:		���[�V�������̓ǂݍ���
-----------------------------------------------------------------------------*/
void CMotion::ReadMotion(FILE *fp)
{
	int cntmotion = 0;

	while(cntmotion != MAX_MOTION)
	{	//	���[�V�������𒴂��Ȃ�������

		fscanf( fp , "%s" , m_Buff );

		if(strcmp( m_Buff , m_FileToken[MOTIONSET] ) == 0)
		{	//	MOTIONSET�̌���

			while( 1 )
			{
				fscanf( fp , "%s" , m_Buff );

				if(strcmp( m_Buff , m_FileToken[LOOP] ) == 0)
				{	//	LOOP�̌���
					fscanf( fp , "%s" , m_Buff );
					if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
					{	//	=�̌���
						fscanf( fp , "%d" , &m_Motion[cntmotion].Loop );	//	���[�v���邩�̓ǂݍ���
					}
				}

				else if(strcmp( m_Buff , m_FileToken[NUMKEY] ) == 0)
				{	//	NUM_KEY�̌���
					fscanf( fp , "%s" , m_Buff );
					if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
					{	//	=�̌���
						fscanf( fp , "%d" , &m_Motion[cntmotion].NumKey );	//	�L�[���̓ǂݍ���

						m_Motion[cntmotion].Frame = new int[m_Motion[cntmotion].NumKey];

						m_Motion[cntmotion].Next = new KEYINFO[ m_Motion[cntmotion].NumKey ];
						for(int i = 0 ; i < m_Motion[cntmotion].NumKey ; i++ )
						{	//	�L�[����

							m_Motion[cntmotion].Next[i].Pos = new D3DXVECTOR3[m_NumModel];
							m_Motion[cntmotion].Next[i].Rot = new D3DXVECTOR3[m_NumModel];
						}
						for(int j = 0 ; j < m_Motion[cntmotion].NumKey ; j++ )
						{	//	������
							for(int k = 0 ; k < m_NumModel ; k++ )
							{	//	���f������

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
			{	//	�L�[����

				fscanf( fp , "%s" , m_Buff );

				if(strcmp( m_Buff , m_FileToken[KEYSET] ) == 0)
				{	//	KEYSET�̌���

					int nummodel = 0;

					while( nummodel != m_NumModel )
					{	//	���f������

						fscanf( fp , "%s" , m_Buff );

						if(strcmp( m_Buff , m_FileToken[FRAME] ) == 0)
						{	//	FRAME�̌���
							fscanf( fp , "%s" , m_Buff );
							if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
							{	//	=�̌���
								fscanf( fp , "%d" , &m_Motion[cntmotion].Frame[numkey] );//	�t���[�����̓ǂݍ���
							}
						}

						else if(strcmp( m_Buff , m_FileToken[POS] ) == 0)
						{	//	POS�̌���
							fscanf( fp , "%s" , m_Buff );
							if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
							{	//	=�̌���

								//	���W�̓ǂݍ���
								fscanf( fp , "%f" , &m_Motion[cntmotion].Next[numkey].Pos[nummodel].x );
								fscanf( fp , "%f" , &m_Motion[cntmotion].Next[numkey].Pos[nummodel].y );
								fscanf( fp , "%f" , &m_Motion[cntmotion].Next[numkey].Pos[nummodel].z );
							}
						}

						else if(strcmp( m_Buff , m_FileToken[ROT] ) == 0)
						{	//	ROT�̌���
							fscanf( fp , "%s" , m_Buff );
							if(strcmp( m_Buff , m_FileToken[EQUAL] ) == 0)
							{	//	=�̌���

								//	��]�̓ǂݍ���
								fscanf( fp , "%f" , &m_Motion[cntmotion].Next[numkey].Rot[nummodel].x );
								fscanf( fp , "%f" , &m_Motion[cntmotion].Next[numkey].Rot[nummodel].y );
								fscanf( fp , "%f" , &m_Motion[cntmotion].Next[numkey].Rot[nummodel].z );
							}
						}

						else if(strcmp( m_Buff , m_FileToken[END_KEY] ) == 0)
						{	//	END_KEY�̌���
							nummodel++;
						}
					}
				}

				else if(strcmp( m_Buff , m_FileToken[END_KEYSET] ) == 0)
				{	//	END_KEYSET�̌���
					numkey++;
				}
			}
		}

		//	END_MOTIONSET�̌���
		if(strcmp( m_Buff , m_FileToken[END_MOTIONSET] ) == 0) cntmotion++;

		//	END_SCRIPT�̌���
		if(strcmp( m_Buff , m_FileToken[END_SCRIPT] ) == 0) break;
	}
}
