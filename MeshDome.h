/*=============================================================================

		���b�V������[ MeshDome.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/05/12
-------------------------------------------------------------------------------
	���@�X�V��
		2017/08/18
=============================================================================*/

#ifndef _MESHDOME_H_
#define _MESHDOME_H_

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CMeshDome : public CScene
{
public:
	typedef enum
	{	//	�ǂ�������ŕ`�悳���邩

		IDXBACK_DRAW_CLOCKWISE = 0,	//	���v���
		IDXBACK_DRAW_INV_CLOCKWISE	//	�t���v���

	}IDXBACK_DRAW;

	CMeshDome(int Priolity = 1);		//	�R���X�g���N�^
	~CMeshDome(){}	//	�f�X�X�g���N�^

	static CMeshDome *Create(D3DXVECTOR3 Pos, UINT NumBlock_X, UINT NumBlock_Y, float Radius, IDXBACK_DRAW IdxBack, CTextureManager::TEXTURE_ID TextureID);

	virtual void Init(void)override;		//	������
	virtual void Uninit(void)override;	//	�I��
	virtual void Update(void)override;	//	�X�V
	virtual void Draw(void)override;		//	�`��

	void SetRot(const D3DXVECTOR3 Rot) { m_Rot = Rot; };		//	��]�̃Z�b�g
															//	�c���̖����̃Z�b�g
	void SetNumBlock(const UINT NumBlock_X, const UINT NumBlock_Y) { m_NumBlock_X = NumBlock_X; m_NumBlock_Y = NumBlock_Y; };

	//	���_���̌v�Z
	void SetVertexCount(const UINT NumBlock_X, const UINT NumBlock_Y) { m_Vertex = (NumBlock_X + 1) * (NumBlock_Y + 1); };

	//	�C���f�b�N�X�o�b�t�@�̌v�Z
	void SetIdxVerTex(const UINT NumBlock_X, const UINT NumBlock_Y) { m_IdxVerTex = (2 + 2 * NumBlock_X) * NumBlock_Y + (NumBlock_Y - 1) * 2; };

	//	�ǂ�������ŕ`�悳���邩
	void SetIdxBackDraw(const IDXBACK_DRAW IdxBackDraw) { m_IdxBackDraw = IdxBackDraw; };

	//	�e�N�X�`����ID�̃Z�b�g
	void SetTextureID(const CTextureManager::TEXTURE_ID Id) { m_TextureId = Id; }

private:
	void MakeIndex(void);	//	�C���f�b�N�X�o�b�t�@�̍쐬
	void SetWorld(LPDIRECT3DDEVICE9 Device);		//	���[���h���W�ϊ�
	void MakeVerTex(void);	//	���_�̍쐬

	static LPDIRECT3DTEXTURE9 m_Texture;	// �e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_VtxBuff;		// ���_�o�b�t�@�ւ̃|�C���^
	LPDIRECT3DINDEXBUFFER9	m_IdxBuff;		//	�C���f�b�N�X�o�b�t�@�C���^�t�F�[�X�ւ̃|�C���^�̃A�h���X

	D3DXVECTOR3	m_Rot;			// ��]
	D3DXVECTOR3	m_Scl;			// �g�嗦

	D3DXVECTOR2 m_UVSet;		//	�e�N�X�`�����W

	D3DXMATRIX	m_MtxWorld;		// ���[���h�}�g���b�N�X


	UINT m_NumBlock_X;	//	���̖���
	UINT m_NumBlock_Y;	//	�c�̖���

	int m_Vertex;		//	���_��
	int m_IdxVerTex;	//	�C���f�b�N�X�o�b�t�@��

	float m_Radius;	//	���a

	IDXBACK_DRAW m_IdxBackDraw;	//	�ǂ�������ŕ`�悳���邩

	CTextureManager::TEXTURE_ID m_TextureId;	//	�e�N�X�`����ID

};
#endif