/*=============================================================================

		�E�F�[�u[ Wave.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/30
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/30
=============================================================================*/

#ifndef _KILLCOUNT_H_
#define _KILLCOUNT_H_

/*-----------------------------------------------------------------------------
	�O���錾
-----------------------------------------------------------------------------*/
class CNumber2D;

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CKillCount:public CScene
{
public:
	CKillCount(int Priolity) :CScene(Priolity) {
		m_Number[0] = NULL;
		m_Number[1] = NULL;
		m_KillCount = 0;
	}

	static CKillCount* Create(D3DXVECTOR2 pos, D3DXVECTOR2 size);

	void AddCount(const int add) { m_KillCount += add; }	//	���Z
	void SetCount(const int count) { m_KillCount = count; }

	int GetCount(void) { return m_KillCount; }

private:
	virtual void Init(void);	//	������
	virtual void Uninit(void);	//	�I��
	virtual void Update(void);	//	�X�V
	virtual void Draw(void);	//	�`��

private:
	CNumber2D* m_Number[2];

	D3DXVECTOR2 m_Pos;
	D3DXVECTOR2 m_Size;

	int m_KillCount;	//	�E�F�[�u��
};
#endif
