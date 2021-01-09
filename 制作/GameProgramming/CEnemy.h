#ifndef CENEMY2_H
#define CENEMY2_H
#include"CCharacter.h"
#include"CCollider.h"
#include"CPlayer.h"


class CEnemy2 : public CCharacter{
public:
	//デフォルトコンストラクタ(引数のないコンストラクタ）
	CEnemy2(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;
	//衝突判定
	void Collision(CCollider*m, CCollider*y);

};


#endif