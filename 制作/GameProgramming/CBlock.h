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
	//衝突判定
	void Collision(CCollider*m, CCollider*y);
	void TaskCollision();
	void Update();

	float mVelocityJump;
};

#endif

//#include"CCharacter.h"
//#include"CCollider.h"
//
//class CBlock :public CCharacter{
//public:
//	//コライダの追加
//	CCollider*mpCollider;
//	//コンストラクタで初期設定
//	CBlock(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale);
//	~CBlock();
//};
//
//
//#endif