#ifndef CGOMI_H
#define CGOMI_H
#include"CCharacter.h"
#include"CCollider.h"
#include"CPlayer.h"
#include"CSound.h"

class CGomi : public CCharacter{
public:
	//デフォルトコンストラクタ(引数のないコンストラクタ）
	CGomi(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;
	void Update();
	//衝突判定
	void Collision(CCollider*m, CCollider*y);
	void TaskCollision();
	static int GomiCount;
	static CModel mModel;
	float mVelocityJump;

	static CSound Sound;

};



#endif