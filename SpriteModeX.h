/*=============================================================================

		X���f���`��[ SpriteModeX.h ]

-------------------------------------------------------------------------------

	���@�쐬��
		2017/08/25
------------------------------------------------------------------------------- 
	���@�X�V��
		2017/08/27
=============================================================================*/

#ifndef _SPRITEMODELX_H_
#define _SPRITEMODELX_H_

/*-----------------------------------------------------------------------------
	�N���X
-----------------------------------------------------------------------------*/
class CSpriteModeLX:public CScene
{
public:
	CSpriteModeLX(int Priolity);	//	�R���X�g���N�^

	//	����
	static CSpriteModeLX* Create(int Priolity);

	virtual void Init(void)override {}	//	������
	virtual void Uninit(void)override { CScene::Release(); }	//	�I��
	virtual void Update(void)override {}	//	�X�V
	virtual void Draw(void)override;	//	�`��

	//	Setter
	void SetRotation(const D3DXVECTOR3 Rot) { m_Rotation = Rot; }	//	��]
	void SetScale(const D3DXVECTOR3 Scl) { m_Scale = Scl; }			//	�g�嗦
	void SetModel(char *FileName) { m_FileName = FileName; }	//	�t�@�C����

	//	Getter
	D3DXVECTOR3 GetRotation(void) { return m_Rotation; }	//	��]
	D3DXVECTOR3 GetScale(void) { return m_Scale; }			//	�g�嗦

private:
	void SetWorld(LPDIRECT3DDEVICE9 Device);	//	���[���h���W�ϊ�

private:
	D3DXVECTOR3	m_Rotation;				//	��]
	D3DXVECTOR3	m_Scale;				//	�g�嗦

	char *m_FileName;	//	�t�@�C����

	CModelManager::MODEL_PARAM m_ModelParam;	//	���f���\����
};
#endif
