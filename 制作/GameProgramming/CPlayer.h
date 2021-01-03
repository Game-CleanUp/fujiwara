#ifndef CPLAYER_H
#define CPLAYER_H
#include"CCharacter.h"
#include"CKey.h"
#include"CCollider.h"
#include"CInput.h"
#include"CPower.h"
#include"CHome.h"
#include"CBattery.h"
#include"CTime.h"
#include"CGaugeBack.h"
#include"CMoney.h"
#include"CSound.h"

#define G       9.8f/60.0f//重力加速度
#define JUMPV0  1.8f	//ジャンプ初速
#define R		7.0f	//半径
#define RETRY	30		//復帰時間
#define DROP	15.0f	//ゴミのドロップ位置
#define DROP_RAND	rand() % 360	//ゴミのドロップ方向
#define FORWARD	1.5f	//前進
#define DASH	2.0f	//ダッシュ
#define DIRECTION	8.0f	//方向転換
#define BACK	-1.0f	//後退

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
	static int clear;
	static int Dash;
	static int Jump;
	static int Down;

	int frame;	//効果時間
	int frame2;	//復帰時間
	int frameMax;
	int level;
	float mVelocityJump;

	CBattery Battery;
	CTime Time;
	CGaugeBack Back;
	CMatrix matrix;

	static CSound Sound;

	static CSound Sound2;

};



#endif