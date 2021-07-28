/*=============================================================================

		�n��[ Ground.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/30
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/30
=============================================================================*/

#ifndef _GROUND_H_
#define _GROUND_H_

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CGround:public CSprite3D
{
public:
	//	�R���X�g���N�^
	CGround(int Priolity) :CSprite3D(Priolity) {
		m_Scroll = 0.0f;
		m_ScrollSpeed = 0.0f;
	}

	static CGround* Create(int Priolity);	//	����

	//	Setter
	void SetScroll(const float speed) { m_ScrollSpeed = speed; }

private:
	virtual void Init(void)override;	//	������
	virtual void Uninit(void)override;	//	�I��
	virtual void Update(void)override;	//	�X�V
	virtual void Draw(void)override;	//	�`��
	void SetUpVerTex(void);		//	���_�̐ݒ�

private:
	float m_Scroll;
	float m_ScrollSpeed;
};
#endif
