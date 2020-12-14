#ifndef CGOMI_H
#define CGOMI_H
#include"CCharacter.h"
#include"CCollider.h"
#include"CPlayer.h"


class CGomi : public CCharacter{
public:
	//デフォルトコンストラクタ(引数のないコンストラクタ）
	CGomi(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;
	//衝突判定
	void Collision(CCollider*m, CCollider*y);
	static int GomiCount;
};



#endif