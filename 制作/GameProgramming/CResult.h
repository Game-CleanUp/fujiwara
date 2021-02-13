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
	//Ÿ‚ÌƒV[ƒ“‚Ìæ“¾
	EScene GetNextScene();
	//‰æ–Ê“Š‰e”ÍˆÍ‚Ì•Ï”
	int mLeft, mRight, mBottom, mTop;

	static CSound SoundEnter;
	static CSound SoundResult;
};




#endif