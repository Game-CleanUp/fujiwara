#include"CPlayerHP.h"
#include"CSceneGame.h"


void CPlayerHP::Render(){

	//モデルビュー行列の退避
	glPushMatrix();
	//モデルビュー行列の初期化
	glLoadIdentity();

	//モデルビュー行列から
	//プロジェクション行列へ切り替え
	glMatrixMode(GL_PROJECTION);
	//プロジェクション行列の退避
	glPushMatrix();
	//プロジェクション行列の初期化
	glLoadIdentity();
	//2D描画の設定
	gluOrtho2D(-400,400,-300,300);
	//Depthテストオフ
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	//緑
	glColor3f(0.0f, 1.0f, 0.0f);

	x = CSceneGame::mTimeMax - CSceneGame::mTimeNow;
	y = -280;
	w = 100 * CSceneGame::mTimeNow / CSceneGame::mTimeMax;
	h = 10;
	//mEnabled = true;
	CRectangle::Render();

	//プロジェクション行列を戻す
	glPopMatrix();
	//モデルビューモードへ切り替え
	glMatrixMode(GL_MODELVIEW);
	//モデルビュー行列を戻す
	glPopMatrix();
	//Depthテストオン
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
}