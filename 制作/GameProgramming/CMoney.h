#ifndef CMONEY_H
#define CMONEY_H
#include"CCharacter.h"
#include"CCollider.h"
#include"CPlayer.h"


class CMoney : public CCharacter{
public:
	//デフォルトコンストラクタ(引数のないコンストラクタ）
	CMoney(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;
	//衝突判定
	void Collision(CCollider*m, CCollider*y);
	static int exp;
};


#endif