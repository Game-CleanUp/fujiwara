#ifndef CRESULT_H
#define CRESULT_H

#include "CScene.h"
#include "CText.h"
#include "CSound.h"
#include "CSceneGame.h"
#include "CPlayer.h"

class CResult : public CScene{
public:
	void Init();
	void Update();
	//次のシーンの取得
	EScene GetNextScene();
	//画面投影範囲の変数
	int mLeft, mRight, mBottom, mTop;

	static CSound SoundEnter;
	static CSound SoundResult;
};




#endif