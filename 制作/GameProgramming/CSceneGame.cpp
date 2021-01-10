#include "CSceneGame.h"
//
#include "CCamera.h"
//
#include "CText.h"

int CSceneGame::StageCount = 0;
int CSceneGame::mBatteryMax = 60 * 60;
int CSceneGame::mBatteryNow = mBatteryNow + mBatteryMax;
int CSceneGame::mTimeMax = 60 * 60;
int CSceneGame::mTimeNow = mTimeNow + mTimeMax;
int CSceneGame::frame = 0;
int CSceneGame::frame2 = 0;

 CSound CSceneGame::Sound;
 CSound CSceneGame::Sound2;

CSceneGame::~CSceneGame(){
	
	//シーン初期化
	CTaskManager::Get()->Delete();

	//mEabledをすべてfalseにする
	CTaskManager::Get()->AllDelete();

}

void CSceneGame::Init() {

	//シーンの設定
	mScene = EGAME;

	Sound.Load("bgm.wav");
	Sound2.Load("GameOver.wav");
	//BGM再生
	Sound.Repeat();

	glMatrixMode(GL_PROJECTION);	//行列をプロジェクションモードへ変更
	glLoadIdentity();				//行列を初期化
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
	mSphere.Load("sphere.obj", "sphere.mtl");


	mSofa.Load("sofa.obj", "sofa.mtl");	//ソファ
	mBed.Load("cama.obj", "cama.mtl");	//ベッド
	mDog.Load("Dog.obj", "Dog.mtl");	//犬
	mTable.Load("Table.obj", "Table.mtl");	//テーブル
	mKitchen.Load("kitchen.obj", "kitchen.mtl");	//キッチン

	mPlayer.mpModel = &mSphere;	//プレイヤーモデル

	new CObj(&mBed, CVector(-55.0f, -6.0f, 30.0f), CVector(0.0f, 90.0f, 0.0f), CVector(20.0f, 25.0f, 20.0f));

	new CObj(&mTable, CVector(-20.0f, -1.0f, 0.0f), CVector(), CVector(30.0f, 20.0f, 20.0f));

	new CObj(&mKitchen, CVector(50.0f, -1.0f, -20.0f), CVector(0.0f, -90.0f, 0.0f), CVector(8.0f, 10.0f, 10.0f));

	//new CObj(&mSofa, CVector(-55.0f, -1.0f, 10.0f), CVector(), CVector(10.0f, 10.0f, 10.0f));

	


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
	new CObj(&mCube, CVector(100.0f, 0.0f, 0.0f), CVector(), CVector(W, H, 80.0f));
	
	//下
	new CObj(&mCube, CVector(-100.0f, 0.0f, 0.0f), CVector(), CVector(W, H, 80.0f));

	//右
	new CObj(&mCube, CVector(0.0f, 0.0f, 80.0f), CVector(), CVector(100.0f, H, W));
	
	//左
	new CObj(&mCube, CVector(0.0f, 0.0f, -80.0f), CVector(), CVector(100.0f, H, W));


	//敵(ダメージが入る)
	new CEnemy2(&mCube, CVector(-20.0f, 0.0f, 20.0f), CVector(), CVector(2.0f, 2.0f, 2.0f));
	new CEnemy2(&mCube, CVector(-30.0f, 0.0f, 20.0f), CVector(), CVector(2.0f, 2.0f, 2.0f));

	//敵(追尾)
	new CBoss(&mDog, CVector(50.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	
	//ホーム
	new CHome(&mCube, CVector(-75.0f, -0.7f, 60.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));	

	//天井
	//new CObj(&mPlane, CVector(0.0f, 90.0f, 0.0f), CVector(-180.0f, 0.0f, 0.0f), CVector(150.0f, 1.0f, 200.0f));

	//プレイヤー初期位置
	mPlayer.mPosition = CVector(-70.0f, 10.0f, 50.0f);
	mPlayer.mRotation = CVector(0.0f, -225.0f, 0.0f);
	//テクスチャ(床）
	std::shared_ptr<CTexture>yuka(new CTexture("yuka.tga"));
	//地面
	new CObj(&mPlane, CVector(0.0f, -1.5f, 0.0f), CVector(), CVector(100.0f, 1.0f, 80.0f));
	new CImage(yuka, CVector(0.0f, -1.49f, 0.0f), CVector(-90.0f, 0.0f, 0.0f), CVector(100.0f, 80.0f, 1.0f));

	//new CObj(&mPlane, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(200.0f, 1.0f, 200.0f));

	//new CBullet(&mBullet, CVector(1.0f, 0.0f, 1.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
}


void CSceneGame::RenderMiniMap(){
	glPushMatrix();
	glViewport(600, 450, 200, 150); //画面の描画エリアの指定
	glLoadIdentity();
	//視点調整必要
	gluLookAt(0, 90, 0, 0, 0, 0, 0, 0, 1);
	glDisable(GL_DEPTH_TEST);
	//描画
	CTaskManager::Get()->Render();
	glPopMatrix();
	glViewport(0, 0, 800, 600); //画面の描画エリアの指定
	glEnable(GL_DEPTH_TEST);
}


void CSceneGame::Update() {
	
	

	if (mBatteryNow >= 0 && CHome::home == 0){
		mBatteryNow -= 2;
	}
	//最大値を超えない
	else if (mBatteryMax >= mBatteryNow){
		mBatteryNow += 15;
	}
	
	//0以下にならない
	if (mBatteryNow < 0){
		mBatteryNow = 0;
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
	if (frame==300 || frame==500 || frame==700){
		new CBoss(&mDog, CVector(0.0f, 0.0f, -15.0f), CVector(), CVector(0.5f, 0.5f, 0.5f));
	}
	if (frame < 100 && frame % 10 == 0){

		//ゴミの生成
		new CGomi(&mRock, CVector(RAND, 0.0f, RAND), CVector(), CVector(1.0f, 1.0f, 1.0f));
		//new CObj(&mCube, CVector(rand() % 100 - 50, 0.0f, rand() % 100 - 50), CVector(), CVector(2.0f, 5.0f, 2.0f));
	}
	
	CTaskManager::Get()->Update();
	//カメラのパラメータを作成する
	CVector e, c, u;//視点、注視点、上方向
	if (CPlayer::Down == FALSE){
		//視点を求める
		e = CVector(0.0f, 2.0f, -1.0f)*mPlayer.mMatrix;
		//注視点を求める
		c = CVector(0.0f, 0.0f, 10.0f)*mPlayer.mMatrix;
		//上方向を求める
		u = CVector(0.0f, 1.0f, 0.0f)*mPlayer.mMatrixRotate;
	}
	//ダメージリアクション
	else{
		//視点を求める
		e = CVector(0.0f, 30.0f, -10.0f)*mPlayer.mMatrix;
		//注視点を求める
		c = CVector(0.0f, 0.0f, 10.0f)*mPlayer.mMatrix;
		//上方向を求める
		u = CVector(0.0f, 1.0f, 0.0f)*mPlayer.mMatrixRotate;
	}

	//見下ろし視点
	if (CKey::Push('I')){
		e = CVector(0.0f, 30.0f, 0.0f)*mPlayer.mMatrix;
	}

	//確認
	if (CKey::Push('P')){
		e = CVector(0.0f, 150.0f, 0.0f);
	}

	//カメラの設定
	Camera.Set(e, c, u);
	Camera.Render();

	//背景描画(カメラの後ろ2Dの前に入れる）
	//mSky.Render();

	CTaskManager::Get()->Render();
	CollisionManager.Render();

	//コリジョンマネージャーの衝突処理
	CTaskManager::Get()->TaskCollision();

	//コリジョンリストから削除
	CTaskManager::Get()->Delete();

	//ミニマップ表示
	RenderMiniMap();

	//2D描画開始
	Start2D(0, 800, 0, 600);

	//ゲームオーバー条件(バッテリー切れ）
	if (mBatteryNow <= 0 || mTimeNow <= 0){
		CText::DrawString("GAME OVER", 200, 330, 25, 25);
		
		Sound2.Play();	//ゲームオーバーSE

		//タイトル画面へ
		if (CKey::Push(VK_RETURN)){
			mScene = ETITLE;
			Sound.Stop();	//BGM終了
			mTimeNow = mTimeMax;
			mBatteryNow = mBatteryMax;
			CGomi::GomiCount = 0;
			frame = 0;
		}
	}

	//ボスとの衝突
	if (CPlayer::Down == TRUE){
		CText::DrawString("CRASH!", 285, 450, 25, 25);
	}

	////クリア条件(ゴミ全回収)
	//if (CPlayer::clear >= GAMECLEAR && CHome::home == 1){
	//	CText::DrawString("STAGE CLEAR", 155, 330, 25, 25);
	//}

	frame2++;
	if (frame2 < 40){
		CText::DrawString("WAVE1", 325, 400, 15, 15);
		//CText::DrawString("CLEAR:5", 290, 300, 15, 15);
		//frame2 = 0;
	}

	if (CPlayer::clear >= 5){
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
	CText::DrawString("BATTERY", 17, 50, 11, 11);
	CText::DrawString("[", 15, 25, 11, 11);
	CText::DrawString("]", 305, 25, 11, 11);


	char buf[10];

	//制限時間
	sprintf(buf, "%d", mTimeNow / 60);
	CText::DrawString(buf, 15, 550, 15, 15);

	//目標数
	sprintf(buf, "%d", CPlayer::PlayerLevel);
	CText::DrawString(buf, 600, 30, 15, 15);
	//目標数
	sprintf(buf, "%d", CPlayer::clear);
	CText::DrawString(buf, 700, 30, 15, 15);

	//ゴミ回収数
	sprintf(buf, "%d", CGomi::GomiCount);
	CText::DrawString(buf, 300, 50, 15, 15);

	//2D描画終了
	End2D();

	return;
}

//次のシーンの取得
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}
