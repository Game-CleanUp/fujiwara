#include "CResult.h"
#include "CKey.h"

CSound CResult::SoundEnter;
CSound CResult::SoundResult;

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

	SoundEnter.Load("enter.wav");
	SoundResult.Load("result.wav");

	SoundResult.Play();

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
	CText::DrawString("RESULT", 200, 500, 40, 40);
	//CText::DrawString("PUSH ENTER KEY", 165, 100, 17, 17);
	CText::DrawString("RANK", 350, 400, 15, 15);

	CText::DrawString("SCORE", 280, 150, 15, 15);

	char buf[10];
	//スコア表示
	sprintf(buf, "%d", CPlayer::Score);
	CText::DrawString(buf, 480, 150, 15, 15);

	if (CPlayer::Score <= 5){
		CText::DrawString("D", 400, 300, 60, 60);
	}
	else if (CPlayer::Score <= 10){
		CText::DrawString("C", 400, 300, 60, 60);
	}
	else if (CPlayer::Score <= 20){
		CText::DrawString("B", 400, 300, 60, 60);
	}
	else if (CPlayer::Score <= 25){
		CText::DrawString("A", 400, 300, 60, 60);
	}
	else{
		CText::DrawString("S", 400, 300, 60, 60);
	}

	//2D描画終了
	End2D();

	//タイトルへ
	if (CKey::Once(VK_RETURN)) {
		mScene = ETITLE;
		CPlayer::Score = 0;
		SoundEnter.Play();	//決定SE再生
		SoundResult.Stop();
	}
}
//次のシーンの取得
CScene::EScene CResult::GetNextScene() {
	return mScene;
}
