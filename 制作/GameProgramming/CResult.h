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
	//���̃V�[���̎擾
	EScene GetNextScene();
	//��ʓ��e�͈͂̕ϐ�
	int mLeft, mRight, mBottom, mTop;

	static CSound SoundEnter;
	static CSound SoundResult;
};




#endif