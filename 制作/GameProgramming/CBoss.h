#ifndef CBOSS_H
#define CBOSS_H

#include"CPlayer.h"
#include"CCharacter.h"
#include"CCollider.h"

#define TURN 25 //向き

class CBoss : public CCharacter{
public:
	//デフォルトコンストラクタ(引数のないコンストラクタ）
	CBoss(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;
	CCollider mSearch;
	//衝突判定
	void Collision(CCollider*m, CCollider*y);
	void Update();
	void TaskCollision();

	int state;
	int frame;

	static int tracking;

	float mVelocityJump;

};


#endif