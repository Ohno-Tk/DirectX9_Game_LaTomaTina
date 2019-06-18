#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Scene.h"

class CPlayer : public CScene {
public:
	CPlayer(int Priolity) : CScene(Priolity) {}
	~CPlayer() {}

	static CPlayer* Create(void);

	virtual void Init(void)override;
	virtual void Uninit(void)override;
	virtual void Update(void)override;
	virtual void Draw(void)override;

	void SubHp(void);

	void SetRotation(const D3DXVECTOR3 Rot) { m_Rotation = Rot; }	//	��]
	void SetScale(const D3DXVECTOR3 Scl) { m_Scale = Scl; }			//	�g�嗦

	D3DXVECTOR3 GetRotation(void) { return m_Rotation; }	//	��]
	D3DXVECTOR3 GetScale(void) { return m_Scale; }			//	�g�嗦

private:
	void SetWorld(LPDIRECT3DDEVICE9 Device);	//	���[���h���W�ϊ�

	D3DXVECTOR3	m_Rotation;				//	��]
	D3DXVECTOR3	m_Scale;				//	�g�嗦

	D3DXVECTOR3	m_offset;

	char* m_FileName;	//	�t�@�C����

	CModelManager::MODEL_PARAM m_ModelParam;	//	���f���\����

	static int m_HP;
};

#endif	//_PLAYER_H_
