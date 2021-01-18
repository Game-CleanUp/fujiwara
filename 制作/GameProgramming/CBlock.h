#ifndef CBLOCK_H
#define CBLOCK_H
#include"CCharacter.h"
#include"CCollider.h"
#include"CPlayer.h"


class CBlock : public CCharacter{
public:
	//デフォルトコンストラクタ(引数のないコンストラクタ）
	CBlock(CModel*model, CVector position, CVector rotation, CVector scale);

	CCollider mColBody;
	CCollider *mpCollider;

	//衝突判定
	void Collision(CCollider*m, CCollider*y);
	void TaskCollision();
	void Update();

	float mVelocityJump;

	int BlockTriangle;	//三角形の数
};

#endif