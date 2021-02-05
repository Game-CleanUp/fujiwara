#ifndef CSCENETITLE_H
#define CSCENETITLE_H

#include "CScene.h"
#include "CText.h"
#include"CSound.h"
#include"CSceneGame.h"
#include"CUi.h"

class CSceneTitle : public CScene {
public:
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();

	//���̃V�[���̎擾
	EScene GetNextScene();
	//��ʓ��e�͈͂̕ϐ�
	int mLeft, mRight, mBottom, mTop;

	static CSound Sound;	//���艹

	CTitleUI Title;
};

#endif
