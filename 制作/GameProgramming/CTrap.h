#ifndef CTRAP_H
#define CTRAP_H
#include"CCharacter.h"
#include"CCollider.h"
#include"CPlayer.h"
#include"CSound.h"
#include "CCollisionManager.h"

class CTrap : public CCharacter{
public:

	//デフォルトコンストラクタ(引数のないコンストラクタ）
	CTrap(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;

	void Update();
	//衝突判定
	void Collision(CCollider*m, CCollider*y);
	void TaskCollision();

	int trapframe;

	static int TrapCount;	//罠を持っている数
	static CModel mModel;
	static CSound Sound;

	float mVelocityJump;

};



#endif