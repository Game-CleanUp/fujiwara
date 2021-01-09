#ifndef CENEMY_H
#define CENEMY_H
#include"CCharacter.h"
#include"CCollider.h"
#include "CVector.h"
#include"CSceneGame.h"

class CEnemy : public CCharacter{
public:
	//デフォルトコンストラクタ(引数のないコンストラクタ）
	CEnemy(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;

	//衝突判定
	void Collision(CCollider*m, CCollider*y);
	void Update();
	int state;
	int frame;

};



#endif