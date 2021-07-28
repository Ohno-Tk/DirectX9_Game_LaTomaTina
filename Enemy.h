/*=============================================================================

		[ Enemy.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/30
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/30
=============================================================================*/

#ifndef _ENEMY_H_
#define _ENEMY_H_

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CEnemy:public CMotion
{
public:
	CEnemy(int Priolity = 3):CMotion(Priolity){}

	static CEnemy* Create(D3DXVECTOR3 pos ,float speed);

	virtual void Init(void)override;	//	������
	virtual void Uninit(void)override;	//	�I��
	virtual void Update(void)override;	//	�X�V
	virtual void Draw(void)override;	//	�`��

private:
	D3DXVECTOR3 m_Pos;
	float m_Speed;
};
#endif
