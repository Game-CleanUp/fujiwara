#ifndef CBOSS_H
#define CBOSS_H

#include"CPlayer.h"
#include"CCharacter.h"
#include"CCollider.h"
#include"CSound.h"
#include"math.h"

#define TURN 13		//向き
#define SPEED 0.1f	//移動速度

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
	int ActFrame;	//行動時間
	int EnemyDown; //敵ダウン判定
	int DownFrame;	//気絶時間

    int tracking;
	int traptracking;

	float mVelocityJump;

	static CSound Sound;
};


#endif