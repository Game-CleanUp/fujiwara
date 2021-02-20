#include "CSceneGame.h"

#include "CCamera.h"

#include "CText.h"


int CSceneGame::mBatteryMax = BATTERY;
int CSceneGame::mBatteryNow = mBatteryNow + mBatteryMax;
int CSceneGame::mTimeMax = TIME;
int CSceneGame::mTimeNow = mTimeNow + mTimeMax;
int CSceneGame::frameGame = 0;
int CSceneGame::frameUI = 0;

 CSound CSceneGame::SoundBGM;
 CSound CSceneGame::SoundGameOver;
 CSound CSceneGame::SoundCharge;
 CSound CSceneGame::SoundTimeUp;

 CTexture TextureTrap;
 CTexture TextureGomi;

CSceneGame::~CSceneGame(){
	
	//シーン初期化
	CTaskManager::Get()->Delete();

	//mEabledをすべてfalseにする
	CTaskManager::Get()->AllDelete();

}

void CSceneGame::Init() {

	//シーンの設定
	mScene = EGAME;

	SoundBGM.Load("BGM1.wav");
	SoundGameOver.Load("GameOver.wav");
	SoundCharge.Load("chage.wav");
	SoundTimeUp.Load("finish.wav");

	//BGM再生
	SoundBGM.Repeat();

	BatterySE = true;
	GameSE = true;

	//テクスチャの読み込み
	TextureTrap.Load("DogFood.tga");
	TextureGomi.Load("Gomi.tga");

	glMatrixMode(GL_PROJECTION);	//行列をプロジェクションモードへ変更
	glLoadIdentity();				//行列を初期化
	gluPerspective(75.0, (double)800 / (double)600, 1.0, 10000.0);	//3Dの画面を設定

	glMatrixMode(GL_MODELVIEW);		//行列をモデルビューモードへ変更
	glLoadIdentity();				//行列を初期化

	//テキストフォントの読み込みと設定
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);	//画像の横幅/1文字の横幅

	mCube.Load("cube.obj", "cube.mtl");
	mPlane.Load("plane.obj", "plane.mtl");
	mSphere.Load("sphere.obj", "sphere.mtl");

	mDog.Load("Dog.obj", "Dog.mtl");	//犬

	mPlayerModel.Load("player.obj", "player.mtl");

	mSofa.Load("loungeSofa.obj", "loungeSofa.mtl");	//ソファ
	mBed.Load("bedSingle.obj", "bedSingle.mtl");	//ベッド
	mChair.Load("stoolBarSquare.obj", "stoolBarSquare.mtl");	//椅子
	mTVCabinet.Load("cabinetTelevisionDoors.obj", "cabinetTelevisionDoors.mtl");	//テレビ台
	mBedCabinet.Load("cabinetBedDrawerTable.obj", "cabinetBedDrawerTable.mtl");
	mTable.Load("table.obj", "table.mtl");
	mTrashbox.Load("trashbox.obj", "trashbox.mtl");
	mWall.Load("wall.obj", "wall.mtl");
	mDoor.Load("wallDoor.obj", "wallDoor.mtl");
	mKichen.Load("kichen.obj", "kichen.mtl");
	mKitchenCabinet.Load("kichenCabinet.obj", "kichenCabinet.mtl");
	mFrige.Load("frige.obj", "frige.mtl");

	mPlayer.mpModel = &mPlayerModel;	//プレイヤーモデル
	CVector left = CVector(0.0f, -90.0f, 0.0f);

	new CObj(&mBed, CVector(-18.0f, -1.0f, -7.0f), CVector(0.0f, -90.0f, 0.0f), CVector(50.0f, 45.0f, 50.0f));

	new CObj(&mChair, CVector(20.0f, -5.0f, 20.0f), CVector(), CVector(50.0f, 20.0f, 50.0f));

	new CObj(&mTVCabinet, CVector(-59.0f, -1.0f, 25.0f), CVector(0.0f, -90.0f, 0.0f), CVector(50.0f, 35.0f, 65.0f));

	new CObj(&mSofa, CVector(-10.0f, -1.0f, -15.0f), CVector(0.0f, 90.0f, 0.0f), CVector(40.0f, 35.0f, 35.0f));

	new CObj(&mTable, CVector(-35.0f, -5.0f, 5.0f), CVector(0.0f, -90.0f, 0.0f), CVector(50.0f, 40.0f, 40.0f));

	new CObj(&mWall, CVector(5.0f, -1.0f, -55.0f), CVector(0.0f, 90.0f, 0.0f), CVector(90.0f, 30.0f, 40.0f));

	new CObj(&mDoor, CVector(5.0f, -1.0f, 25.0f), CVector(0.0f, 90.0f, 0.0f), CVector(35.0f, 25.0f, 40.0f));

	new CObj(&mKichen, CVector(64.0f, -1.0f, -40.0f), CVector(), CVector(90.0f, 30.0f, 50.0f));

	new CObj(&mKitchenCabinet, CVector(26.0f, -1.0f, 20.0f), CVector(0.0f, -90.0f, 0.0f), CVector(120.0f, 30.0f, 40.0f));

	new CObj(&mFrige, CVector(63.0f, -1.0f, -30.0f), CVector(0.0f, 90.0f, 0.0f), CVector(40.0f, 50.0f, 38.0f));

	/* 乱数系列の変更 */
	srand((unsigned)time(NULL));

	//上
	new CObj(&mCube, CVector(80.0f, -1.0f, 0.0f), CVector(), CVector(W, H, 60.0f));
	//下
	new CObj(&mCube, CVector(-80.0f, -1.0f, 0.0f), CVector(), CVector(W, H, 60.0f));
	//右
	new CObj(&mCube, CVector(0.0f, -1.0f, 60.0f), CVector(), CVector(80.0f, H, W));
	//左
	new CObj(&mCube, CVector(0.0f, -1.0f, -60.0f), CVector(), CVector(80.0f, H, W));

	//敵(追尾)
	new CBoss(&mDog, CVector(-20.0f, 0.0f, 50.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	new CBoss(&mDog, CVector(30.0f, 0.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));
	
	new CTrap(&mSphere, CVector(0.0f, -10.0f, 0.0f), CVector(), CVector(1.0f, 1.0f, 1.0f));

	//ホーム
	new CHome(&mTrashbox, CVector(73.0f, -1.0f, 53.0f), CVector(0.0f, 45.0f, 0.0f), CVector(15.0f, 15.0f, 15.0f));

	//プレイヤー初期位置
	mPlayer.mPosition = CVector(71.0f, 10.0f, 51.0f);
	mPlayer.mRotation = CVector(0.0f, 225.0f, 0.0f);
	
	//テクスチャ(床）
	std::shared_ptr<CTexture>floor(new CTexture("floor.tga"));

	//床
	new CObj(&mPlane, CVector(0.0f, -1.5f, 0.0f), CVector(), CVector(80.0f, 1.0f, 60.0f));
	new CImage(floor, CVector(0.0f, -1.49f, 0.0f), CVector(-90.0f, 0.0f, 0.0f), CVector(80.0f, 60.0f, 1.0f));

}

//数値リセット
void CSceneGame::ValueReset(){
	SoundBGM.Stop();	//BGM終了
	mTimeNow = mTimeMax;
	mBatteryNow = mBatteryMax;
	CPlayer::Down = false;
	CGomi::GomiCount = 0;
	CTrap::TrapCount = 10;
	frameGame = 0;
}

void CSceneGame::Update() {

	//バッテリー減少
	if (mBatteryNow >= 0 && CHome::home == false && mTimeNow > 0){
		mBatteryNow--;
	}

	//充電(最大値を超えない、バッテリー増加)
	if (mBatteryMax >= mBatteryNow && CHome::home == true){

		mBatteryNow += CHAGE;

		//バッテリーがMAX以外で効果音再生
		if (BatterySE && mBatteryNow < mBatteryMax){
			SoundCharge.Repeat();
			BatterySE = false;
		}
	}
	else{
		SoundCharge.Stop();
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

	frameGame++;
	if (frameGame < 5000 && frameGame % 250 == 0){
		//ゴミの生成
		new CGomi(NULL, CVector(RAND, 20.0f, RAND), CVector(), CVector(0.5f, 0.5, 0.5f));
	}
	
	CTaskManager::Get()->Update();

	CVector e, c, u;//視点、注視点、上方向
	if (CPlayer::Down == FALSE){
		//視点を求める
		e = CVector(0.0f, 1.5f, -3.5f)*mPlayer.mMatrix;
		//注視点を求める
		c = CVector(0.0f, 0.0f, 10.0f)*mPlayer.mMatrix;
		//上方向を求める
		u = CVector(0.0f, 1.0f, 0.0f)*mPlayer.mMatrixRotate;
	}
	//ダメージリアクション
	else{
		//視点を求める
		e = CVector(0.0f, 30.0f, -5.0f)*mPlayer.mMatrix;
		//注視点を求める
		c = CVector(0.0f, 0.0f, 10.0f)*mPlayer.mMatrix;
		//上方向を求める
		u = CVector(0.0f, 1.0f, 0.0f)*mPlayer.mMatrixRotate;
	}

	//後方視点
	if (CKey::Push('O')){
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

	//2D描画開始(UI表示)
	Start2D(0, 800, 0, 600);

	//ゲームオーバー条件(バッテリー切れ）
	if (mBatteryNow <= 0){
		if (CKey::Once(VK_RETURN)){	//タイトル画面へ
			mScene = ETITLE;
			ValueReset();
		}

		CText::DrawString("GAME OVER", 200, 330, 25, 25);
	
		if (GameSE){
			SoundGameOver.Play();
			GameSE = false;
		}
	}
	
	//タイムアップ
	if (mTimeNow <= 0){
		if (CKey::Once(VK_RETURN)){	//リザルト画面へ
			mScene = ERESULT;
			ValueReset();
		}

		CText::DrawString("TIME UP", 245, 330, 25, 25);

		if (GameSE){
			SoundTimeUp.Play();
			GameSE = false;
		}
	}

	//ボスとの衝突
	if (CPlayer::Down == TRUE){
		CText::DrawString("CRASH!", 280, 450, 25, 25);
	}

	frameUI++;
	if (frameUI < 60){
		CText::DrawString("START", 293, 400, 25, 25);
	}

	CText::DrawString("BATTERY", 17, 50, 11, 11);
	CText::DrawString("[", 15, 25, 11, 11);
	CText::DrawString("]", 305, 25, 11, 11);

	//整数を文字列に変換する
	char buf[10];

	//制限時間
	sprintf(buf, "%d", mTimeNow / 60);
	CText::DrawString(buf, 30, 550, 13, 13);

	//トラップ所持数
	sprintf(buf, "%d", CTrap::TrapCount);
	CText::DrawString(buf, 740, 30, 13, 13);

	//ゴミ所持数
	sprintf(buf, "%d", CGomi::GomiCount);
	CText::DrawString(buf, 300, 50, 13, 13);

	End2D();

	return;
}

//次のシーンの取得
CScene::EScene CSceneGame::GetNextScene() {
	return mScene;
}
