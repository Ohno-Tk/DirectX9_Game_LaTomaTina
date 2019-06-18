#ifndef _BULLET_H_
#define _BULLET_H_

#include "SpriteModeX.h"

class CBullet : public CSpriteModeLX {
public:
	CBullet(int Priolity = 3) : CSpriteModeLX(Priolity) {}
	~CBullet() {}

	static CBullet* Create(D3DXVECTOR3 pos, D3DXVECTOR3 vec);

	void Init();
	void Uninit();
	void Update();
	void Draw();

private:

	D3DXVECTOR3 m_Move;
};

#endif	//_BULLET_H_
