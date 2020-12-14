#ifndef CSPEED_H
#define CSPEED_H
#include"CCharacter.h"
#include"CCollider.h"
#include"CPlayer.h"


class CSpeed :public CCharacter{
public:
	//デフォルトコンストラクタ(引数のないコンストラクタ）
	CSpeed(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;
	//衝突判定
	void Collision(CCollider*m, CCollider*y);
	static int speed;

};


#endif