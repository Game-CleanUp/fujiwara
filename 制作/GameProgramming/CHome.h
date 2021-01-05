#ifndef CHOME_H
#define CHOME_H

#include"CCharacter.h"
#include"CCollider.h"
#include"CGomi.h"
#include "CCollisionManager.h"

class CHome : public CCharacter{
public:
	//デフォルトコンストラクタ(引数のないコンストラクタ）
	CHome(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;
	//衝突判定
	void Collision(CCollider*m, CCollider*y);
	void TaskCollision();
	static int home;
};



#endif