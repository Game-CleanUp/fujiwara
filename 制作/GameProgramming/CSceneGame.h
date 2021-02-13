#ifndef CSCENEGAME_H
#define CSCENEGAME_H

#include"CScene.h"
#include"CModel.h"
#include"CMatrix.h"
#include"CPlayer.h"
#include"CTaskManager.h"
#include"CCollisionManager.h"
#include"CObj.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include"CKey.h"
#include"CGomi.h"
#include"CHome.h"
#include"CBoss.h"
#include"CSound.h"
#include"CImage.h"
#include"CTrap.h"
#include"CTexture.h"

#define RAND rand() % 100 - 50	//ランダム配置(-150~149)
#define W	5.0f	//幅
#define H	25.0f //高さ
#define TIME	60 * 60	//制限時間
#define BATTERY	60 * 60	//バッテリー上限
#define CHAGE	50	//バッテリー増加

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
	void ValueReset();

	CPlayer mPlayer;

	CModel mCube;
	CModel mPlane;
	CModel mSphere;
	CModel mSofa;
	CModel mTable;
	CModel mDog;
	CModel mBed;
	CModel mKitchenCabinet;
	CModel mKichen;
	CModel mFrige;
	CModel mChair;
	CModel mTVCabinet;
	CModel mBedCabinet;
	CModel mTrashbox;
	CModel mWall;
	CModel mDoor;
	
	//次のシーンの取得
	EScene GetNextScene();

	static int mBatteryMax;
	static int mBatteryNow;

	static int mTimeMax;
	static int mTimeNow;

	static int frame;	//ゲームプレイ時間
	static int frame2;

	static CSound SoundBGM;	//BGM
	static CSound SoundGameOver;	//ゲームオーバー音
	static CSound SoundCharge;	//充電音
	static CSound SoundTimeUp;	//タイムアップ

	bool BatterySE;	//一度だけ充電SE再生
	bool GameSE;	//一度だけゲームオーバー、タイムアップSE再生
};

#endif
