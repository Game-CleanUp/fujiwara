#include "CResult.h"
#include "CKey.h"

CSound CResult::Sound;

void CResult::Init() {

	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);

	//シーンの設定
	mScene = ERESULT;

	//画面投影範囲の設定
	mLeft = -400;
	mRight = 400;
	mBottom = -300;
	mTop = 300;

	Sound.Load("enter.wav");

}

//更新処理のオーバーライド
void CResult::Update() {

	//画面投影範囲の変更
	//行列をプロジェクションモードへ変更
	glMatrixMode(GL_PROJECTION);
	//行列を初期化
	glLoadIdentity();
	//2Dの画面投影範囲を設定
	gluOrtho2D(mLeft, mRight, mBottom, mTop);
	//行列をモデルビューモードへ変更
	glMatrixMode(GL_MODELVIEW);
	//行列を初期化
	glLoadIdentity();

	//2D描画開始
	Start2D(0, 800, 0, 600);

	////文字列の描画
	CText::DrawString("CLEAN UP", 250, 400, 20, 20);
	CText::DrawString("PUSH ENTER KEY", 165, 200, 17, 17);

	char buf[10];
	//制限時間
	sprintf(buf, "%d", CSceneGame::mTimeNow / 60);
	CText::DrawString(buf, 15, 550, 15, 15);

	//2D描画終了
	End2D();

	//タイトルへ
	if (CKey::Once(VK_RETURN)) {
		mScene = ETITLE;
		Sound.Play();	//決定SE再生
	}
}
//次のシーンの取得
CScene::EScene CResult::GetNextScene() {
	return mScene;
}
