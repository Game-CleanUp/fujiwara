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
#include"CBlock.h"
#include"CGomi.h"
#include"CHome.h"
#include"CBoss.h"
#include"CSound.h"
#include"CImage.h"
#include"CTrap.h"
#include"CTexture.h"

#define RAND rand() % 100 - 50	//�����_���z�u(-150~149)
#define W	5.0f	//��
#define H	25.0f //����
#define TIME	120 * 60	//��������
#define BATTERY	60 * 60	//�o�b�e���[�ő�l
#define CHAGE	15	//�o�b�e���[����

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

	CModel mRock;
	CPlayer mPlayer;
	CModel mCube;
	CModel mPlane;
	CModel mSphere;
	CModel mSofa;
	CModel mTable;
	CModel mDog;
	CModel mBed;
	CModel mKitchen;
	CModel mChair;
	CModel mTVCabnet;
	CModel mKichenCabinet;
	CModel mBedCabinet;

	
	//���̃V�[���̎擾
	EScene GetNextScene();

	static int mBatteryMax;
	static int mBatteryNow;

	static int mTimeMax;
	static int mTimeNow;

	static int frame;	//�Q�[���v���C����
	static int frame2;

	static CSound Sound;	//BGM
	static CSound Sound2;	//�Q�[���I�[�o�[��

	static CSound Sound3;

	bool BatterySE;	//��x�����[�dSE�Đ�
	bool GameOverSE;	//��x�����Q�[���I�[�o�[SE�Đ�
};

#endif
