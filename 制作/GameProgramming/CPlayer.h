#ifndef CPLAYER_H
#define CPLAYER_H
#include"CCharacter.h"
#include"CKey.h"
#include"CCollider.h"
#include"CHome.h"
#include"CBattery.h"
#include"CLevel.h"
#include"CTime.h"
#include"CGaugeBack.h"
#include"CMoney.h"
#include"CSound.h"

#define G       9.8f/50.0f//重力加速度 9.8f
#define JUMPV0  1.5f	//ジャンプ初速
#define R		7.0f	//半径
#define RETRY	60		//復帰時間
#define DROP	15.0f	//ゴミのドロップ位置
#define DROP_RAND	rand() % 360	//ゴミのドロップ方向
#define FORWARD	0.7f	//前進
#define DASH	1.0f	//ダッシュ
#define DIR		5.0f	//方向転換
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
	static int levelNow;
	static int levelMax;
	static int PlayerLevel;
	float mVelocityJump;

	CBattery Battery;
	CTime Time;
	CLevel Level;
	CGaugeBack Back;
	CMatrix matrix;

	static CSound Sound;

	static CSound Sound2;

};



#endif