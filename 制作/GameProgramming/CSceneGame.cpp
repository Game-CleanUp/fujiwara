#include "CSceneGame.h"

#include "CCamera.h"

#include "CText.h"


CTexture Texture;

int CSceneGame::mBatteryMax = BATTERY;
int CSceneGame::mBatteryNow = mBatteryNow + mBatteryMax;
int CSceneGame::mTimeMax = TIME;
int CSceneGame::mTimeNow = mTimeNow + mTimeMax;
int CSceneGame::frame = 0;
int CSceneGame::frame2 = 0;

 CSound CSceneGame::Sound;
 CSound CSceneGame::Sound2;
 CSound CSceneGame::Sound3;

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
	Sound3.Load("chage.wav");

	//BGM再生
	//Sound.Repeat();

	bool BatterySE = true;
	bool GameOverSE = true;

	//テクスチャの読み込み
	Texture.Load("DogFood.tga");

	glMatrixMode(GL_PROJECTION);	//行列をプロジェクションモードへ変更
	glLoadIdentity();				//行列を初期化
	gluPerspective(75.0, (double)800 / (double)600, 1.0, 10000.0);	//3Dの画面を設定

	glMatrixMode(GL_MODELVIEW);		//行列をモデルビューモードへ変更
	glLoadIdentity();				//行列を初期化

	//テキストフォントの読み込みと設定
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);	//画像の横幅/1文字の横幅

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

	//new CObj(&mBed, CVector(-55.0f, -6.0f, 30.0f), CVector(0.0f, 90.0f, 0.0f), CVector(20.0f, 25.0f, 20.0f));

	//new CObj(&mTable, CVector(-20.0f, -1.0f, 0.0f), CVector(), CVector(30.0f, 20.0f, 20.0f));

	//new CObj(&mKitchen, CVector(50.0f, -1.0f, -20.0f), CVector(0.0f, -90.0f, 0.0f), CVector(8.0f, 10.0f, 10.0f));

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
	new CObj(&mCube, CVector(100.0f, -1.0f, 0.0f), CVector(), CVector(W, H, 80.0f));
	
	//下
	new CObj(&mCube, CVector(-100.0f, -1.0f, 0.0f), CVector(), CVector(W, H, 80.0f));

	//右
	new CObj(&mCube, CVector(0.0f, -1.0f, 80.0f), CVector(), CVector(100.0f, H, W));
	
	//左
	new CObj(&mCube, CVector(0.0f, -1.0f, -80.0f), CVector(), CVector(100.0f, H, W));

	//中央
	new CObj(&mCube, CVector(0.0f, -1.0f, 0.0f), CVector(), CVector(5.0f, 10.0f, 5.0f));

	
	//ブロック(移動させることができる)
	//new CBlock(&mCube, CVector(-20.0f, 3.0f, 40.0f), CVector(), CVector(2.0f, 2.0f, 5.0f));
	//new CBlock(&mCube, CVector(-80.0f, 5.0f, 75.0f), CVector(), CVector(5.0f, 5.0f, 2.0f));

	//敵(追尾)
	new CBoss(&mDog, CVector(-20.0f, 0.0f, 50.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));


	new CTrap(&mSphere, CVector(0.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	
	//ホーム
	new CHome(&mCube, CVector(-90.0f, -0.7f, 75.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));


	//プレイヤー初期位置
	mPlayer.mPosition = CVector(-90.0f, 10.0f, 75.0f);
	mPlayer.mRotation = CVector(0.0f, -225.0f, 0.0f);
	
	//テクスチャ(床）
	std::shared_ptr<CTexture>yuka(new CTexture("yuka.tga"));

	//床
	new CObj(&mPlane, CVector(0.0f, -1.5f, 0.0f), CVector(), CVector(100.0f, 1.0f, 80.0f));
	new CImage(yuka, CVector(0.0f, -1.49f, 0.0f), CVector(-90.0f, 0.0f, 0.0f), CVector(100.0f, 80.0f, 1.0f));

}

//ミニマップ
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

	//バッテリー減少
	if (mBatteryNow >= 0 && CHome::home == false && mTimeNow > 0){
		mBatteryNow--;
	}

	//充電(最大値を超えない、バッテリー増加)
	if (mBatteryMax >= mBatteryNow && CHome::home == 1){

		mBatteryNow += CHAGE;

		if (BatterySE && mBatteryNow < mBatteryMax){
			Sound3.Repeat();	//充電中SE
			BatterySE = false;
		}
	}
	else{
		Sound3.Stop();
		BatterySE = true;
	}
	
	//0以下にならない(バッテリー)
	if (mBatteryNow < 0){
		mBatteryNow = 0;
	}
	
	//制限時間減少
	if (mBatteryNow > 0){
		mTimeNow--;
	}

	//0以下にならない(タイム)
	if (mTimeNow < 0){
		mTimeNow = 0;
	}

	frame++;
	if (frame==1000 || frame==2000 || frame==3000){
		//new CBoss(&mDog, CVector(0.0f, 0.0f, -15.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	}

	if (frame < 1000 && frame % 100 == 0){
		//ゴミの生成
		//new CGomi(&mRock, CVector(RAND, 0.0f, RAND), CVector(), CVector(1.0f, 1.0f, 1.0f));
	}
	
	CTaskManager::Get()->Update();

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
		e = CVector(0.0f, 25.0f, -15.0f)*mPlayer.mMatrix;
		//注視点を求める
		c = CVector(0.0f, 0.0f, 10.0f)*mPlayer.mMatrix;
		//上方向を求める
		u = CVector(0.0f, 1.0f, 0.0f)*mPlayer.mMatrixRotate;
	}

	//後方視点
	if (CKey::Push('O')){
		c = CVector(0.0f, 0.0f, -10.0f)*mPlayer.mMatrix;
	}

	//見下ろし視点
	if (CKey::Push('I')){
		e = CVector(0.0f, 30.0f, 0.0f)*mPlayer.mMatrix;
	}

	//カメラの設定
	Camera.Set(e, c, u);
	Camera.Render();

	CTaskManager::Get()->Render();
	CCollisionManager::Get()->Render();

	//コリジョンマネージャーの衝突処理
	CTaskManager::Get()->TaskCollision();

	//コリジョンリストから削除
	CTaskManager::Get()->Delete();

	//ミニマップ表示
	//RenderMiniMap();

	//2D描画開始(UI表示)
	Start2D(0, 800, 0, 600);

	//ゲームオーバー条件(バッテリー切れ）
	if (mBatteryNow <= 0){
		if (CKey::Once(VK_RETURN)){	//タイトル画面へ
			mScene = ETITLE;
			Sound.Stop();	//BGM終了
			mTimeNow = mTimeMax;
			mBatteryNow = mBatteryMax;
			CGomi::GomiCount = 0;
			frame = 0;
		}

		CText::DrawString("GAME OVER", 200, 330, 25, 25);
	
		if (GameOverSE){
			Sound2.Play();	//ゲームオーバーSE
			GameOverSE = false;
		}
	}
	
	//タイムアップ
	if (mTimeNow <= 0){
		if (CKey::Once(VK_RETURN)){
			mScene = ERESULT;
			Sound.Stop();
			mTimeNow = mTimeMax;
			mBatteryNow = mBatteryMax;
			CGomi::GomiCount = 0;
			frame = 0;
		}

		CText::DrawString("TIME UP", 245, 330, 25, 25);
	}

	//ボスとの衝突
	if (CPlayer::Down == TRUE){
		CText::DrawString("CRASH!", 280, 450, 25, 25);
	}

	frame2++;
	if (frame2 < 60){
		CText::DrawString("START", 293, 400, 25, 25);
	}

	CText::DrawString("BATTERY", 17, 50, 11, 11);
	CText::DrawString("[", 15, 25, 11, 11);
	CText::DrawString("]", 305, 25, 11, 11);

	//整数を文字列に変換する
	char buf[10];

	//制限時間
	sprintf(buf, "%d", mTimeNow / 60);
	CText::DrawString(buf, 15, 550, 15, 15);

	//トラップ数
	sprintf(buf, "%d", CTrap::TrapCount);
	CText::DrawString(buf, 700, 30, 15, 15);

	//ゴミ保有数
	sprintf(buf, "%d", CGomi::GomiCount);
	CText::DrawString(buf, 300, 50, 15, 15);

	End2D();

	return;
}

//次のシーンの取得
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}
