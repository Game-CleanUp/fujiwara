#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CText.h"

int CSceneGame::StageCount = 0;
int CSceneGame::mBatteryMax = 50 * 60;
int CSceneGame::mBatteryNow = mBatteryNow + mBatteryMax;
int CSceneGame::mTimeMax = 60 * 60;
int CSceneGame::mTimeNow = mTimeNow + mTimeMax;
int CSceneGame::frame = 0;

//外部変数
extern CSound Sound;


CSceneGame::~CSceneGame() {
	
	//シーン初期化
	CTaskManager::Get()->Delete();

	//mEabledをすべてfalseにする
	CTaskManager::Get()->AllDelete();

}


void CSceneGame::Init() {

	//シーンの設定
	mScene = EGAME;

	Sound.Load("bgm.wav");
	//BGM再生
//	Sound.Repeat();

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
	//mTana.Load("tana.obj", "cube.mtl");
	mSphere.Load("sphere.obj", "sphere.mtl");
	mPlayer.mpModel = &mCube;

	/* 乱数系列の変更 */
	srand((unsigned)time(NULL));

	/*
	rand() % 100 - 50
	%100は100で割った余りを求める。0~99までになる。
	-50引くことで、-50~49までのランダム値になる。
	*/
	//テクスチャ(壁紙)
	std::shared_ptr<CTexture>kabe(new CTexture("kabe.tga"));
	

	//上
	new CObj(&mCube, CVector(120.0f, 0.0f, 0.0f), CVector(), CVector(W, H, 200.0f));
	new CImage(kabe, CVector(114.9f, 0.0f, -150.0f), CVector(180.0f, 90.0f, -90.0f), CVector(50.0f, 50.0f, 0.0f));
	new CImage(kabe, CVector(114.9f, 0.0f, -50.0f), CVector(180.0f, 90.0f, -90.0f), CVector(50.0f, 50.0f, 0.0f));
	new CImage(kabe, CVector(114.9f, 0.0f, 50.0f), CVector(180.0f, 90.0f, -90.0f), CVector(50.0f, 50.0f, 0.0f));
	new CImage(kabe, CVector(114.9f, 0.0f, 150.0f), CVector(180.0f, 90.0f, -90.0f), CVector(50.0f, 50.0f, 0.0f));


	//下
	new CObj(&mCube, CVector(-130.0f, 0.0f, 0.0f), CVector(), CVector(W, H, 200.0f));
	new CImage(kabe, CVector(-124.9f, 0.0f, -150.0f), CVector(180.0f, -90.0f, -90.0f), CVector(50.0f, 50.0f, 0.0f));
	new CImage(kabe, CVector(-124.9f, 0.0f, -50.0f), CVector(180.0f, -90.0f, -90.0f), CVector(50.0f, 50.0f, 0.0f));
	new CImage(kabe, CVector(-124.9f, 0.0f, 50.0f), CVector(180.0f, -90.0f, -90.0f), CVector(50.0f, 50.0f, 0.0f));
	new CImage(kabe, CVector(-124.9f, 0.0f, 150.0f), CVector(180.0f, -90.0f, -90.0f), CVector(50.0f, 50.0f, 0.0f));

	//右
	new CObj(&mCube, CVector(0.0f, 0.0f, 190.0f), CVector(), CVector(140.0f, H, W));
	new CImage(kabe, CVector(70.0f, 0.0f, 184.9f), CVector(-180.0f, 0.0f, 0.0f), CVector(70.0f, 50.0f, 0.0f));
	new CImage(kabe, CVector(-70.0f, 0.0f, 184.9f), CVector(180.0f, 0.0f, 0.0f), CVector(70.0f, 50.0f, 0.0f));

	//左
	new CObj(&mCube, CVector(0.0f, 0.0f, -180.0f), CVector(), CVector(140.0f, H, W));
	new CImage(kabe, CVector(70.0f, 0.0f, -174.9f), CVector(180.0f, -180.0f, -90.0f), CVector(50.0f, 70.0f, 0.0f));
	new CImage(kabe, CVector(-70.0f, 0.0f, -174.9f), CVector(180.0f, -180.0f, -90.0f), CVector(50.0f, 70.0f, 0.0f));

	//①
	new CObj(&mCube, CVector(-20.0f, 0.0f, -120.0f), CVector(), CVector(W, H, 75.0f));
	new CImage(kabe, CVector(-25.1f, 0.0f, -120.0f), CVector(180.0f, 90.0f, -90.0f), CVector(50.0f, 75.0f, 0.0f));
	new CImage(kabe, CVector(-14.9f, 0.0f, -115.0f), CVector(180.0f, -90.0f, -90.0f), CVector(50.0f, 80.0f, 0.0f));


	//②
	new CObj(&mCube, CVector(-60.0f, 0.0f, -40.0f), CVector(), CVector(45.0f, H, W));
	new CImage(kabe, CVector(-60.0f, 0.0f, -45.1f), CVector(180.0f, 0.0f, 0.0f), CVector(45.0f, 50.0f, 0.0f));
	new CImage(kabe, CVector(-60.0f, 0.0f, -34.9f), CVector(180.0f, -180.0f, -90.0f), CVector(50.0f, 45.0f, 0.0f));


	//③
	new CObj(&mCube, CVector(-75.0f, 0.0f, 80.0f), CVector(), CVector(60.0f, H, W));
	new CImage(kabe, CVector(-75.0f, 0.0f, 74.9f), CVector(180.0f, 0.0f, 0.0f), CVector(60.0f, 50.0f, 0.0f));
	new CImage(kabe, CVector(-75.0f, 0.0f, 85.1f), CVector(180.0f, -180.0f, -90.0f), CVector(50.0f, 60.0f, 0.0f));


	//④
	new CObj(&mCube, CVector(40.0f, 0.0f, -120.0f), CVector(), CVector(W, H, 75.0f));
	new CImage(kabe, CVector(34.9f, 0.0f, -115.0f), CVector(180.0f, 90.0f, -90.0f), CVector(50.0f, 80.0f, 0.0f));
	new CImage(kabe, CVector(45.1f, 0.0f, -115.0f), CVector(180.0f, -90.0f, -90.0f), CVector(50.0f, 80.0f, 0.0f));



	//⑤
	new CObj(&mCube, CVector(65.0f, 0.0f, -40.0f), CVector(), CVector(30.0f, H, W));
	new CImage(kabe, CVector(65.0f, 0.0f, -45.1f), CVector(180.0f, 0.0f, 0.0f), CVector(30.0f, 50.0f, 0.0f));
	new CImage(kabe, CVector(65.0f, 0.0f, -34.9f), CVector(180.0f, -180.0f, -90.0f), CVector(50.0f, 30.0f, 0.0f));


	//⑥
	new CObj(&mCube, CVector(35.0f, 0.0f, 80.0f), CVector(), CVector(25.0f, H, W));
	new CImage(kabe, CVector(35.0f, 0.0f, 74.9f), CVector(180.0f, 0.0f, 0.0f), CVector(25.0f, 50.0f, 0.0f));
	new CImage(kabe, CVector(35.0f, 0.0f, 85.1f), CVector(180.0f, -180.0f, -90.0f), CVector(50.0f, 25.0f, 0.0f));

	//⑦
	new CObj(&mCube, CVector(110.0f, 0.0f, 80.0f), CVector(), CVector(25.0f, H, W));
	new CImage(kabe, CVector(110.0f, 0.0f, 74.9f), CVector(180.0f, 0.0f, 0.0f), CVector(25.0f, 50.0f, 0.0f));
	new CImage(kabe, CVector(110.0f, 0.0f, 85.1f), CVector(180.0f, -180.0f, -90.0f), CVector(50.0f, 25.0f, 0.0f));

	//⑧
	new CObj(&mCube, CVector(25.0f, 0.0f, 120.0f), CVector(), CVector(W, H, 45.0f));
	new CImage(kabe, CVector(19.9f, 0.0f, 120.0f), CVector(180.0f, 90.0f, -90.0f), CVector(50.0f, 45.0f, 0.0f));
	new CImage(kabe, CVector(30.1f, 0.0f, 120.0f), CVector(180.0f, -90.0f, -90.0f), CVector(50.0f, 45.0f, 0.0f));

	//キッチン
	new CObj(&mCube, CVector(30.0f, 0.0f, 45.0f), CVector(), CVector(10.0f, 5.0f, 30.0f));

	/*
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
	*/

	//敵(ダメージが入る)
	/*new CEnemy2(&mSphere, CVector(-20.0f, 0.0f, 0.0f), CVector(), CVector(2.0f, 2.0f, 2.0f));
	new CEnemy2(&mSphere, CVector(-30.0f, 0.0f, 0.0f), CVector(), CVector(2.0f, 2.0f, 2.0f));
*/
	//敵(追尾)
	new CBoss(&mRover, CVector(100.0f, 0.0f, 0.0f), CVector(), CVector(0.5f, 0.5f, 0.5f));

	//ホーム
	new CHome(&mCube, CVector(-50.0f, -0.7f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));


	//天井
	//new CObj(&mPlane, CVector(0.0f, 90.0f, 0.0f), CVector(-180.0f, 0.0f, 0.0f), CVector(150.0f, 1.0f, 200.0f));

	//プレイヤー初期位置
	mPlayer.mPosition = CVector(-50.0f, 10.0f, 0.0f);
	mPlayer.mRotation = CVector(0.0f, 90.0f, 0.0f);

	//テクスチャ(床）
	std::shared_ptr<CTexture>yuka(new CTexture("yuka.tga"));
	//地面
	new CObj(&mPlane, CVector(0.0f, -1.5f, 0.0f), CVector(), CVector(140.0f, 1.0f, 200.0f));
	new CImage(yuka, CVector(0.0f, -1.49f, 0.0f), CVector(-90.0f, 0.0f, 0.0f), CVector(140.0f, 200.0f, 1.0f));

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
	
	

	if (mBatteryNow >= 0 && CHome::home == 0){
		mBatteryNow--;
	}
	//最大値を超えない
	else if (mBatteryMax >= mBatteryNow){
		mBatteryNow += 15;
	}
	
	//0以下にならない
	if (mBatteryNow < 0){
		mBatteryNow = 0;
	}
	//ダッシュ時
	if (CPlayer::Dash == 1){
		mBatteryNow -= 3;
	}
	//ジャンプ時
	if (CPlayer::Jump > 0){
		mBatteryNow -= 10;
	}

	//制限時間
	if (mBatteryNow > 0){
		mTimeNow--;
	}

	//0以下にならない
	if (mTimeNow < 0){
		mTimeNow = 0;
	}

	frame++;
	if (frame < 1000 && frame % 100 == 0){

		//ゴミの生成
		new CGomi(&mRock, CVector(RAND, 0.0f, RAND), CVector(), CVector(1.0f, 1.0f, 1.0f));
	}

	CTaskManager::Get()->Update();
	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	if (CPlayer::Down == FALSE){
		//視点を求める
		e = CVector(0.0f, 10.0f, -20.0f)*mPlayer.mMatrix;
		//注視点を求める
		c = CVector(0.0f, 0.0f, 10.0f)*mPlayer.mMatrix;
		//上方向を求める
		u = CVector(0.0f, 1.0f, 0.0f)*mPlayer.mMatrixRotate;
	}
	//ダメージリアクション
	else{
		//視点を求める
		e = CVector(0.0f, 10.0f, -15.0f)*mPlayer.mMatrix;
		//注視点を求める
		c = CVector(0.0f, 0.0f, 10.0f)*mPlayer.mMatrix;
		//上方向を求める
		u = CVector(0.0f, 1.0f, 0.0f)*mPlayer.mMatrixRotate;
	}


	//見下ろし視点
	if (CKey::Push('I')){
		e = CVector(0.0f, 50.0f, 0.0f)*mPlayer.mMatrix;
	}

	//確認
	if (CKey::Push('P')){
		e = CVector(0.0f, 350.0f, 0.0f);
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

	//ゲームオーバー条件(バッテリー切れ）
	if (mBatteryNow == 0 || mTimeNow <= 0){
		CText::DrawString("GAME OVER", 200, 330, 25, 25);
	}

	//ボスとの衝突
	if (CPlayer::Down == TRUE){
		CText::DrawString("OUT!", 330, 450, 25, 25);
	}

	////クリア条件(ゴミ全回収)
	//if (CPlayer::clear >= GAMECLEAR && CHome::home == 1){
	//	CText::DrawString("STAGE CLEAR", 155, 330, 25, 25);
	//}

	
	if (frame < 120){
		CText::DrawString("WAVE1", 325, 400, 15, 15);
	}

	if (CPlayer::clear >= 10){
		CText::DrawString("WAVE2", 325, 400, 15, 15);
		
	}
	//if (CPlayer::clear >= 10){
	//	CText::DrawString("WAVE3", 325, 400, 15, 15);

	//}
	//if (CPlayer::clear >= 10){
	//	CText::DrawString("WAVE4", 325, 400, 15, 15);

	//}
	//if (CPlayer::clear >= 10){
	//	CText::DrawString("WAVE5", 325, 400, 15, 15);

	//}
	CText::DrawString("BATTERY", 17, 40, 13, 13);

	char buf[10];

	//制限時間
	sprintf(buf, "%d", mTimeNow / 60);
	CText::DrawString(buf, 15, 550, 15, 15);

	//アイテム数(パワー）
	sprintf(buf, "%d", CPower::power);
	CText::DrawString(buf, 750, 30, 15, 15);

	//目標数
	sprintf(buf, "%d", CPlayer::clear);
	CText::DrawString(buf, 650, 30, 15, 15);

	////ゴミ回収数
	//sprintf(buf, "%d", CGomi::GomiCount);
	//CText::DrawString(buf, 140, 50, 15, 15);

	//2D描画終了
	End2D();

	return;
}

//次のシーンの取得
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}
