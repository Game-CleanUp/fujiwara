#ifndef CBOSS_H
#define CBOSS_H

#include"CPlayer.h"
#include"CCharacter.h"
#include"CCollider.h"

class CBoss : public CCharacter{
public:
	//デフォルトコンストラクタ(引数のないコンストラクタ）
	CBoss(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;

	//衝突判定
	void Collision(CCollider*m, CCollider*y);
	void Update();
};


#endif