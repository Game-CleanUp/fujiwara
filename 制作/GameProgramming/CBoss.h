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
#define STATERAND	4	//パターン
#define STOPTIME	rand() % 60 + 30	//停止時間
#define TRACKSPEED	0.3	//追尾速度


class CBoss : public CCharacter{
public:

	enum STATE
	{
		Move_Stop,
		Move_Left,
		Move_Right,
		Move_Gomi,
		Move_TrapTracking,
		Move_PlayerTracking,
		Move_Damage,

	};

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

	float mVelocityJump;

	bool onlyOnce;

	CSound SoundTrack;	//追尾音
	CSound SoundDamage;	//ダメージ音

	CMatrix matrix;
};


#endif