/*=============================================================================

		�V�[���`��( ���X�g�\�� )[ Scene.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/04/26
-------------------------------------------------------------------------------
	���@�X�V��
		2017/08/24
=============================================================================*/

#ifndef _SCENE_H_
#define _SCENE_H_

/*-----------------------------------------------------------------------------
	�萔��`
-----------------------------------------------------------------------------*/
#define PRIOLITY_MAX (6)	//	�D�揇��

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CScene
{
public:
	typedef enum	//	�I�u�W�F�N�g�̎��
	{
		OBJTYPE_NONE = 0,	//	�Ȃ�
		OBJTYPE_BULLET,	//	�e
		OBJTYPE_ENEMY,
		OBJTYPE_TARGET,
		OBJTYPE_MAX			//	�ő吔
	}OBJTYPE;

	CScene(int Priolity);	//	�R���X�g���N�^

	virtual void Init(void) = 0;	//	������
	virtual void Uninit(void) = 0;	//	�I��
	virtual void Update(void) = 0;	//	�X�V
	virtual void Draw(void) = 0;	//	�`��

	static void UpdateAll(void);	//	�S�I�u�W�F�N�g�̍X�V
	static void DrawAll(void);		//	�S�I�u�W�F�N�g�̕`��
	static void ReleaseAll(void);	//	�S�I�u�W�F�N�g�̉��

	//	Setter
	void SetPosition(const D3DXVECTOR3 Position) { m_Position = Position; }	//	���W
	void SetObjeType(const OBJTYPE objType) { m_objType = objType; }		//	�I�u�W�F�N�g���


	//	Getter
	D3DXVECTOR3 GetPosition(void) { return m_Position; }		//	���W
	D3DXVECTOR3* GetPositionPointer(void) { return &m_Position; }//	���W�̃|�C���^
	const OBJTYPE GetObjType(void)const { return m_objType; }	//	�I�u�W�F�N�g���
	static CScene *GetList(int Priority) { return m_Top[Priority]; }	//	���X�g�̐擪
	CScene *GetNext(void) { return m_Next; }	//	���̃��X�g

private:
	bool m_Delete;	//	�폜�t���O

	OBJTYPE m_objType;	//	�I�u�W�F�N�g�̎��

	static CScene *m_Top[PRIOLITY_MAX];	//	�擪�̃|�C���^
	CScene *m_Next;			//	���̃|�C���^

protected:
	D3DXVECTOR3 m_Position;	//	���W

	void Release(void) { m_Delete = true; }	//	�����[�X

};
#endif