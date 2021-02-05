#ifndef CSCENETITLE_H
#define CSCENETITLE_H

#include "CScene.h"
#include "CText.h"
#include"CSound.h"
#include"CSceneGame.h"
#include"CUi.h"

class CSceneTitle : public CScene {
public:
	//初期化処理のオーバーライド
	void Init();
	//更新処理のオーバーライド
	void Update();

	//次のシーンの取得
	EScene GetNextScene();
	//画面投影範囲の変数
	int mLeft, mRight, mBottom, mTop;

	static CSound Sound;	//決定音

	CTitleUI Title;
};

#endif
