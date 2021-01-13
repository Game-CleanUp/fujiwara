#include "CSceneTitle.h"
#include "CKey.h"

void CSceneTitle::Init() {

	//テキストフォントの読み込みと設定
	CText::mFont.Load("FontG.tga");
	CText::mFont.SetRowCol(1, 4096 / 64);

	//シーンの設定
	mScene = ETITLE;

	//画面投影範囲の設定
	mLeft = -400;
	mRight = 400;
	mBottom = -300;
	mTop = 300;
}

//更新処理のオーバーライド
void CSceneTitle::Update() {

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

	//2D描画終了
	End2D();

	if (CKey::Once(VK_RETURN)) {
		//次のシーンはゲーム
		mScene = EGAME;
	}
	if (CKey::Once('N')) {
		//次のシーンはゲーム3
		mScene = EGAME3;
	}
	if (CKey::Once('B')) {
		//次のシーンはゲーム2
		mScene = EGAME2;
	}
}
//次のシーンの取得
CScene::EScene CSceneTitle::GetNextScene() {
	return mScene;
}
