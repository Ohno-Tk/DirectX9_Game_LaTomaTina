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

	void SetRotation(const D3DXVECTOR3 Rot) { m_Rotation = Rot; }	//	回転
	void SetScale(const D3DXVECTOR3 Scl) { m_Scale = Scl; }			//	拡大率

	D3DXVECTOR3 GetRotation(void) { return m_Rotation; }	//	回転
	D3DXVECTOR3 GetScale(void) { return m_Scale; }			//	拡大率

private:
	void SetWorld(LPDIRECT3DDEVICE9 Device);	//	ワールド座標変換

	D3DXVECTOR3	m_Rotation;				//	回転
	D3DXVECTOR3	m_Scale;				//	拡大率

	D3DXVECTOR3	m_offset;

	char* m_FileName;	//	ファイル名

	CModelManager::MODEL_PARAM m_ModelParam;	//	モデル構造体

	static int m_HP;
};

#endif	//_PLAYER_H_
