#ifndef CSCENEGAME_H
#define CSCENEGAME_H

#include"CScene.h"
#include"CModel.h"
#include"CMatrix.h"
#include"CPlayer.h"
#include"CTaskManager.h"
#include"CCollisionManager.h"
#include"CFall.h"
#include"CObj.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include"CKey.h"
#include"CEnemy.h"
#include"CEnemy2.h"
#include"CImage.h"
#include"CGomi.h"
#include"CHome.h"
#include"CMoney.h"
#include"CBoss.h"
#include"CSound.h"

#define RAND rand() % 100 - 50	//ランダム配置(-150~149)
#define W	5.0f	//幅
#define H	25.0f //高さ
#define GAMECLEAR	50 //クリア条件

/*
ゲームのシーン
*/
class CSceneGame : public CScene {
public:
	//デストラクタ
	~CSceneGame();
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();
	//ミニマップの表示
	void RenderMiniMap();
	CModel mSky;
	CModel mRock;
	CModel mRover;
	CPlayer mPlayer;
	CModel mCube;
	CModel mPlane;
	CModel mSphere;
	CModel mSofa;
	CModel mTable;
	CModel mBed;
	CModel mDog;
	CModel mKitchen;

	//次のシーンの取得
	EScene GetNextScene();
	//ステージ数
	static int StageCount;
	static int mBatteryMax;
	static int mBatteryNow;
	static int mTimeMax;
	static int mTimeNow;
	static int frame;

	static int frame2;

	static CSound Sound;	//BGM
	static CSound Sound2;	//ゲームオーバー音

	static CSound Sound3;	//
};

#endif
