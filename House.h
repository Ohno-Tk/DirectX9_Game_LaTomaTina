/*=============================================================================

		��[ House.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/30
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/30
=============================================================================*/

#ifndef _HOUSE_H_
#define _HOUSE_H_

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CHouse:public CSpriteModeLX
{
public:
	CHouse(int Priolity = 2):CSpriteModeLX(Priolity){
		m_Speed = 0.05f;
	}

	static CHouse* Create(void);	//	����

	//	Setter
	void SetSpeed(const float speed) { m_Speed = speed; }

private:
	virtual void Init(void)override {}	//	������
	virtual void Uninit(void)override;	//	�I��
	virtual void Update(void)override;	//	�X�V
	virtual void Draw(void)override;	//	�`��

private:
	float m_Speed;
};
#endif
