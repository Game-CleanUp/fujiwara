#include"CUi.h"
#include"CSceneGame.h"

extern CTexture TextureTrap;
extern CTexture TextureGomi;

void CGaugeBack::Render(){

	//モデルビュー行列の退避
	glPushMatrix();
	//モデルビュー行列の初期化
	glLoadIdentity();
	//プロジェクション行列へ切り替え
	glMatrixMode(GL_PROJECTION);
	//プロジェクション行列の退避
	glPushMatrix();
	//プロジェクション行列の初期化
	glLoadIdentity();
	//2D描画の設定
	gluOrtho2D(-400, 400, -300, 300);
	//Depthテストオフ
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);

	x = -240;
	y = -275;
	w = 152;
	h = 7;
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

void CTrapUI::Render(){

	//モデルビュー行列の退避
	glPushMatrix();
	//モデルビュー行列の初期化
	glLoadIdentity();
	//プロジェクション行列へ切り替え
	glMatrixMode(GL_PROJECTION);
	//プロジェクション行列の退避
	glPushMatrix();
	//プロジェクション行列の初期化
	glLoadIdentity();
	//2D描画の設定
	gluOrtho2D(0, 800, 0, 600);
	//Depthテストオフ
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	x = 690;
	y = 40;
	w = 20;
	h = 25;
	CRectangle::Render(TextureTrap, 0, 1800, 2770, 0);

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

void CTitleUI::Render(){

	//モデルビュー行列の退避
	glPushMatrix();
	//モデルビュー行列の初期化
	glLoadIdentity();
	//プロジェクション行列へ切り替え
	glMatrixMode(GL_PROJECTION);
	//プロジェクション行列の退避
	glPushMatrix();
	//プロジェクション行列の初期化
	glLoadIdentity();
	//2D描画の設定
	gluOrtho2D(0, 800, 0, 600);
	//Depthテストオフ
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	glColor3f(1.0f, 1.0f, 1.0f);

	x = 0;
	y = 0;
	w = 800;
	h = 600;
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

void CGomiUI::Render(){

	//モデルビュー行列の退避
	glPushMatrix();
	//モデルビュー行列の初期化
	glLoadIdentity();
	//プロジェクション行列へ切り替え
	glMatrixMode(GL_PROJECTION);
	//プロジェクション行列の退避
	glPushMatrix();
	//プロジェクション行列の初期化
	glLoadIdentity();
	//2D描画の設定
	gluOrtho2D(0, 800, 0, 600);
	//Depthテストオフ
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);

	x = 250;
	y = 60;
	w = 25;
	h = 25;
	CRectangle::Render(TextureGomi, 0, 2770, 2314, 0);

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