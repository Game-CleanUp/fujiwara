#ifndef CBOSS_H
#define CBOSS_H

#include"CPlayer.h"
#include"CCharacter.h"
#include"CCollider.h"
#include"CSound.h"
#include"math.h"
#include"CTrap.h"

#define TURN rand() % 5 + 1		//向き
#define SPEED 0.3f	//移動速度
#define STATERAND	5	//パターン

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

	bool onlyOnce = true;	//一度だけ実行

	float mVelocityJump;

	static CSound Sound;

	CMatrix matrix;
};


#endif