#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CText.h"

int CSceneGame::StageCount = 0;
int CSceneGame::mTimeMax = 30 * 60;
int CSceneGame::mTimeNow = mTimeNow + mTimeMax;
int CSceneGame::frame = 0;

CSceneGame::~CSceneGame() {
	
	//シーン初期化
	CTaskManager::Get()->Delete();

	//mEabledをすべてfalseにする
	CTaskManager::Get()->AllDelete();
	//CTaskManager::Get()->Delete();

}


void CSceneGame::Init() {

	//シーンの設定
	mScene = EGAME;

	glMatrixMode(GL_PROJECTION);	//行列をプロジェクションモードへ変更
	glLoadIdentity();				//行列を初期化
	//	gluOrtho2D(-width / 2, width / 2, -height / 2, height / 2);	//2Dの画面を設定
	gluPerspective(75.0, (double)800 / (double)600, 1.0, 10000.0);	//3Dの画面を設定

	glMatrixMode(GL_MODELVIEW);		//行列をモデルビューモードへ変更
	glLoadIdentity();				//行列を初期化



	//テキストフォントの読み込みと設定
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);

	mSky.Load("sky.obj", "sky.mtl");
	mRock.Load("Rock1.obj", "Rock1.mtl");
	mRover.Load("Rover1.obj", "Rover1.mtl");
	mCube.Load("cube.obj", "cube.mtl");
	mPlane.Load("plane.obj", "plane.mtl");
	ModelEnemy.Load("f16.obj", "f16.mtl");
	mSphere.Load("sphere.obj", "sphere.mtl");
	mPlayer.mpModel = &mCube;

	/* 乱数系列の変更 */
	srand((unsigned)time(NULL));

	/*
	rand() % 100 - 50
	%100は100で割った余りを求める。0~99までになる。
	-50引くことで、-50~49までのランダム値になる。
	*/

	//上
	new CObj(&mCube, CVector(150.0f, 0.0f, 0.0f), CVector(), CVector(W, H, 180.0f));
	//下
	new CObj(&mCube, CVector(-150.0f, 0.0f, 35.0f), CVector(), CVector(W, H, 150.0f));
	new CObj(&mCube, CVector(-145.0f, 0.0f, 35.0f), CVector(), CVector(W, H, 150.0f));

	//右
	new CObj(&mCube, CVector(0.0f, 0.0f, 180.0f), CVector(), CVector(150.0f, H, W));
	//左
	new CObj(&mCube, CVector(75.0f, 0.0f, -180.0f), CVector(), CVector(75.0f, H, W));
	//左2
	new CObj(&mCube, CVector(-120.0f, 0.0f, -100.0f), CVector(), CVector(30.0f, H, 10.0f));

	//廊下前
	new CObj(&mCube, CVector(-80.0f, 0.0f, -110.0f), CVector(), CVector(75.0f, H, W));

	//左横向き
	new CObj(&mCube, CVector(0.0f, 0.0f, -100.0f), CVector(), CVector(W, H, 80.0f));
	//右横向き
	new CObj(&mCube, CVector(60.0f, 0.0f, 100.0f), CVector(), CVector(W, H, 75.0f));
	new CObj(&mCube, CVector(55.0f, 0.0f, 100.0f), CVector(), CVector(W, H, 75.0f));

	new CObj(&mCube, CVector(115.0f, 0.0f, -20.0f), CVector(), CVector(30.0f, H, W));
	new CObj(&mCube, CVector(25.0f, 0.0f, -20.0f), CVector(), CVector(30.0f, H, W));
	new CObj(&mCube, CVector(15.0f, 0.0f, 20.0f), CVector(), CVector(50.0f, H, W));
	new CObj(&mCube, CVector(15.0f, 0.0f, 25.0f), CVector(), CVector(50.0f, H, W));


	//枠
	new CObj(&mCube, CVector(-95.0f, 0.0f, -150.0f), CVector(), CVector(90.0f, H, W));

	new CObj(&mCube, CVector(-190.0f, 0.0f, -115.0f), CVector(), CVector(W, H, 40.0f));

	//左
	new CObj(&mCube, CVector(-235.0f, 0.0f, -70.0f), CVector(), CVector(50.0f, H, W));

	//下
	new CObj(&mCube, CVector(-290.0f, 0.0f, -15.0f), CVector(), CVector(W, H, 60.0f));

	//右
	new CObj(&mCube, CVector(-235.0f, 0.0f, 40.0f), CVector(), CVector(50.0f, H, W));

	//入口左
	new CObj(&mCube, CVector(-190.0f, 0.0f, -45.0f), CVector(), CVector(W, H, 20.0f));

	//入口右
	new CObj(&mCube, CVector(-190.0f, 0.0f, 20.0f), CVector(), CVector(W, H, 20.0f));

	new CObj(&mCube, CVector(-250.0f, 0.0f, 105.0f), CVector(), CVector(W, H, 60.0f));

	new CObj(&mCube, CVector(-200.0f, 0.0f, 160.0f), CVector(), CVector(45.0f, H, W));


	//敵(ダメージが入る)
	/*new CEnemy2(&mSphere, CVector(20.0f, 0.0f, 0.0f), CVector(), CVector(2.0f, 2.0f, 2.0f));
	new CEnemy2(&mSphere, CVector(30.0f, 0.0f, 0.0f), CVector(), CVector(2.0f, 2.0f, 2.0f));*/

	//ゴミ
	new CGomi(NULL, CVector(20.0f, 0.0f, 10.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	new CGomi(NULL, CVector(80.0f, 0.0f, -50.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	new CGomi(NULL, CVector(30.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));

	//敵(追尾)
	new CBoss(&mRover, CVector(100.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));


	//パワー
	//new CPower(&mCube, CVector(80.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));

	//ホーム
	new CHome(&mCube, CVector(-50.0f, -0.7f, 0.0f), CVector(), CVector(0.05f, 0.05f, 0.05f));

	//地面
	new CObj(&mPlane, CVector(0.0f, -1.5f, 0.0f), CVector(), CVector(300.0f, 1.0f, 200.0f));
	//天井
	//new CObj(&mPlane, CVector(0.0f, 100.0f, 0.0f), CVector(), CVector(150.0f, 1.0f, 200.0f));

	mPlayer.mPosition = CVector(-50.0f, 10.0f, 0.0f);
	mPlayer.mRotation = CVector(0.0f, 90.0f, 0.0f);
	

	////障害物テクスチャ(しゃがみ）
	//std::shared_ptr<CTexture>grass(new CTexture("grass.tga"));
	//new CImage(grass, CVector(0.0f, 28.0f, 9.0f),
	//	CVector(180.0f, 0.0f, 0.0f), CVector(69.0f, 13.0f, 1.0f));
}


void CSceneGame::RenderMiniMap(){
	glPushMatrix();
	glViewport(600, 450, 200, 150); //画面の描画エリアの指定
	glLoadIdentity();
	//視点調整必要
	gluLookAt(0, 150, 0, 0, 0, 0, 0, 0, 1);
	glDisable(GL_DEPTH_TEST);
	//描画
	CTaskManager::Get()->Render();
	glPopMatrix();
	glViewport(0, 0, 800, 600); //画面の描画エリアの指定
	glEnable(GL_DEPTH_TEST);
}


void CSceneGame::Update() {
	
	if (mTimeNow >= 0 && CHome::home == 0){
		mTimeNow--;
	}
	//最大値を超えない
	else if (mTimeMax >= mTimeNow){
		mTimeNow += 15;
	}
	
	//0以下にならない
	if (mTimeNow < 0){
		mTimeNow = 0;
	}
	//ダッシュ時
	if (CPlayer::Dash == 1){
		mTimeNow -= 3;
	}
	//ジャンプ時
	if (CPlayer::Jump > 0){
		mTimeNow -= 10;
	}

	CTaskManager::Get()->Update();
	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	//視点を求める
	e = CVector(0.0f, 30.0f, -30.0f)*mPlayer.mMatrix;
	//注視点を求める
	c = CVector(0.0f, 0.0f, 10.0f)*mPlayer.mMatrix;
	//上方向を求める
	u = CVector(0.0f, 1.0f, 0.0f)*mPlayer.mMatrixRotate;

	//見下ろし視点
	if (CKey::Push('I')){
		e = CVector(0.0f, 100.0f, 0.0f)*mPlayer.mMatrix;
	}

	//確認
	if (CKey::Push('P')){
		e = CVector(0.0f, 300.0f, 0.0f);
	}

	//一人称視点
	if (CKey::Push('O')){
		e = CVector(0.0f, 3.0f, -3.0f)*mPlayer.mMatrix;
	}

	//カメラの設定
	Camera3D(e.mX, e.mY, e.mZ, c.mX, c.mY, c.mZ, u.mX, u.mY, u.mZ);

	//背景描画(カメラの後ろ2Dの前に入れる）
	//mSky.Render();

	CTaskManager::Get()->Render();
	CollisionManager.Render();

	
	frame++;
	if (frame < 1000 && frame % 100 == 0){

		//ゴミの生成
		//new CGomi(&mRock, CVector(RAND, 1.0f, RAND), CVector(), CVector(1.0f, 1.0f, 1.0f));
	}

	//コリジョンマネージャーの衝突処理
	CollisionManager.Collision();

	//コリジョンリストから削除
	CTaskManager::Get()->Delete();

	//ミニマップ表示
	RenderMiniMap();

	//2D描画開始
	Start2D(0, 800, 0, 600);

	if (CKey::Push(VK_RETURN)){
		mScene = ETITLE;
	}

	//CText::DrawString("3D PROGRAMMING", 20, 20, 10, 12);

	//ゲームオーバー条件(バッテリー切れ）
	if (mTimeNow == 0){
		CText::DrawString("GAME OVER", 200, 330, 25, 25);
	}

	//ゲームオーバー条件(ライフゼロ)
	if (CPlayer::Life <= 0){
		CText::DrawString("GAME OVER", 200, 330, 25, 25);
	}

	//クリア条件
	if (CPlayer::clear >= 2 && CHome::home == 1){
		CText::DrawString("STAGE CLEAR", 155, 330, 25, 25);
	}

	char buf[10];

	sprintf(buf, "%d", mTimeNow / 60);
	CText::DrawString(buf, 30, 550, 20, 20);

	//アイテム数(パワー）
	sprintf(buf, "%d", CPower::power);
	CText::DrawString(buf, 750, 30, 15, 15);

	//目標数
	sprintf(buf, "%d", CPlayer::clear);
	CText::DrawString(buf, 650, 30, 15, 15);

	//ゴミ回収数
	sprintf(buf, "%d", CGomi::GomiCount);
	CText::DrawString(buf, 140, 50, 15, 15);

	//プレイヤーライフ
	sprintf(buf, "%d", CPlayer::Life);
	CText::DrawString(buf, 20, 50, 15, 15);

	//2D描画終了
	End2D();

	return;
}

//次のシーンの取得
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}
