#ifndef CFALL_H
#define CFALL_H
#include"CCharacter.h"
#include"CCollider.h"
#include "CVector.h"

#define G       (9.8f/60.0f)//重力加速度

class CFall : public CCharacter{
public:
	//デフォルトコンストラクタ(引数のないコンストラクタ）
	CFall(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;
	
	//衝突判定
	void Collision(CCollider*m, CCollider*y);
	void Update();
	float mVelocityJump;
	CVector mForward;

};



#endif