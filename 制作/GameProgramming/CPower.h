#ifndef CPOWER_H
#define CPOWER_H
#include"CCharacter.h"
#include"CCollider.h"
#include"CPlayer.h"


class CPower :public CCharacter{
public:
	//デフォルトコンストラクタ(引数のないコンストラクタ）
	CPower(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;
	//衝突判定
	void Collision(CCollider*m, CCollider*y);
	static int power;

};


#endif