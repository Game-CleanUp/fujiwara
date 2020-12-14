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
#include"CInput.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include"CKey.h"
#include"CEnemy.h"
#include"CImage.h"
#include"CGomi.h"
#include"CPower.h"
#include"CSpeed.h"
#include"CHome.h"
#include"CMoney.h"

#define RAND (rand() % 300-150)	//ランダム配置(-150~149)
#define W	(5.0f)	//幅
#define H	(10.0f) //高さ

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
	CModel mSky;
	CModel mRock;
	CModel mRover;
	CPlayer mPlayer;
	CModel mCube;
	CModel mPlane;
	CModel ModelEnemy;	//エネミーモデル
	CModel mSphere;
	//次のシーンの取得
	EScene GetNextScene();
	//ステージ数
	static int StageCount;
	static int mTimeMax;
	static int mTimeNow;
	static int frame;
	
};

#endif
