#ifndef CPLAYER_H
#define CPLAYER_H
#include"CCharacter.h"
#include"CKey.h"
#include"CCollider.h"
#include"CHome.h"
#include"CBattery.h"
#include"CTime.h"
#include"CUi.h"
#include"CSound.h"
#include"CBullet.h"
#include"CTrap.h"
#include"CText.h"

#define G       9.8f/60.0f//重力加速度 9.8f
#define JUMPV0  2.0f	//ジャンプ初速
#define R		5.0f	//半径
#define RETRY	80		//復帰時間
#define DROP	13	//ゴミのドロップ位置
#define DROP_DIR	rand() % 360	//ゴミのドロップ方向
#define FORWARD	0.6f	//前進
#define DIR		7.0f	//方向転換
#define BACK	-0.6f	//後退
#define DASH	0.8f	//ダッシュスピード
#define TIMEADD	5*60	//タイム加算

class CPlayer : public CCharacter{
public:
	
	void Update();
	void Render();
	void Init();
	void Collision(CCollider*m, CCollider*y);
	void TaskCollision();
	//デフォルトコンストラクタ
	CPlayer();
	CCollider mColBody;
	CCollider mSearch;
	static CPlayer *mpPlayer;
	static int Score;
	static int Down;

	static CSound SoundJump;	//ジャンプ音
	static CSound SoundBomb;	//爆発音
	static CSound SoundAttack;	//攻撃音
	static CSound SoundThrow;	//ゴミ回収

	int frameRetry;	//復帰時間

	float mVelocityJump;

	bool onlyOnce;

	CBattery Battery;
	CTime Time;
	CGaugeBack Back;
	CMatrix matrix;
	CTrapUI TrapUi;
	CGomiUI GomiUI;

};



#endif