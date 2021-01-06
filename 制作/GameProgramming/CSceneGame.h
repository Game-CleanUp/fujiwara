#ifndef CSCENEGAME_H
#define CSCENEGAME_H
#include"CScene.h"
#include"CModel.h"
#include"CMatrix.h"
#include"CPlayer.h"
#include"CTaskManager.h"
#include"CCollisionManager.h"
#include"CFall.h"
#include"CObj.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include"CKey.h"
#include"CEnemy.h"
#include"CEnemy2.h"
#include"CImage.h"
#include"CGomi.h"
#include"CHome.h"
#include"CMoney.h"
#include"CBoss.h"
#include"CSound.h"

#define RAND rand() % 200-100	//�����_���z�u(-150~149)
#define W	5.0f	//��
#define H	5.0f //����
#define GAMECLEAR	50 //�N���A����

/*
�Q�[���̃V�[��
*/
class CSceneGame : public CScene {
public:
	//�f�X�g���N�^
	~CSceneGame();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();
	//�~�j�}�b�v�̕\��
	void RenderMiniMap();
	CModel mSky;
	CModel mRock;
	CModel mRover;
	CPlayer mPlayer;
	CModel mCube;
	CModel mPlane;
	CModel mSphere;
	CModel mSofa;
	CModel mTable;
	CModel mBed;
	CModel mDog;
	CModel mKitchen;
	//���̃V�[���̎擾
	EScene GetNextScene();
	//�X�e�[�W��
	static int StageCount;
	static int mBatteryMax;
	static int mBatteryNow;
	static int mTimeMax;
	static int mTimeNow;
	static int frame;

	static int frame2;
	static CSound Sound;
	static CSound Sound2;

	
};

#endif
