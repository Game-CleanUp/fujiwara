#ifndef CPLAYER_H
#define CPLAYER_H
#include"CCharacter.h"
#include"CKey.h"
#include"CCollider.h"
#include"CHome.h"
#include"CBattery.h"
#include"CTime.h"
#include"CGaugeBack.h"
#include"CMoney.h"
#include"CSound.h"
#include"CBullet.h"
#include"CInput.h"
#include"CTrap.h"
#include"CText.h"

#define G       9.8f/60.0f//重力加速度 9.8f
#define JUMPV0  2.0f	//ジャンプ初速
#define R		5.0f	//半径
#define RETRY	60		//復帰時間
#define DROP	rand() % 20 + 10	//ゴミのドロップ位置
#define DROP_DIR	rand() % 360	//ゴミのドロップ方向
#define FORWARD	0.5f	//前進
#define DIR		2.0f	//方向転換
#define BACK	-0.3f	//後退



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
	static int Down;

	int frame;	//効果時間
	int frame2;	//復帰時間
	int frameMax;

	//起動時のマウスカーソルの座標を覚える
	int mMouseX;
	int mMouseY;

	float mVelocityJump;

	CBattery Battery;
	CTime Time;
	CGaugeBack Back;
	CMatrix matrix;
	CUI Ui;

	static CSound Sound;

	static CSound Sound2;	//爆発音
};



#endif