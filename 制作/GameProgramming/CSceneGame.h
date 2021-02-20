#ifndef CSCENEGAME_H
#define CSCENEGAME_H

#include"CScene.h"
#include"CModel.h"
#include"CMatrix.h"
#include"CPlayer.h"
#include"CTaskManager.h"
#include"CCollisionManager.h"
#include"CObj.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include"CKey.h"
#include"CGomi.h"
#include"CHome.h"
#include"CBoss.h"
#include"CSound.h"
#include"CImage.h"
#include"CTrap.h"
#include"CTexture.h"

#define RAND rand() % 100 - 50	//�����_���z�u(-50~49)
#define W	2.0f	//��
#define H	20.0f //����
#define TIME	60 * 60	//��������
#define BATTERY	50 * 60	//�o�b�e���[���
#define CHAGE	50	//�o�b�e���[����

class CSceneGame : public CScene {
public:
	//�f�X�g���N�^
	~CSceneGame();
	//�����������̃I�[�o�[���C�h
	void Init();
	//�X�V�����̃I�[�o�[���C�h
	void Update();

	void ValueReset();

	CPlayer mPlayer;

	CModel mPlayerModel;

	CModel mCube;
	CModel mPlane;
	CModel mSphere;
	CModel mSofa;
	CModel mTable;
	CModel mDog;
	CModel mBed;
	CModel mKitchenCabinet;
	CModel mKichen;
	CModel mFrige;
	CModel mChair;
	CModel mTVCabinet;
	CModel mBedCabinet;
	CModel mTrashbox;
	CModel mWall;
	CModel mDoor;
	
	//���̃V�[���̎擾
	EScene GetNextScene();

	static int mBatteryMax;
	static int mBatteryNow;

	static int mTimeMax;
	static int mTimeNow;

	static int frameGame;	//�Q�[���v���C����
	static int frameUI;	//UI�\������

	static CSound SoundBGM;	//BGM
	static CSound SoundGameOver;	//�Q�[���I�[�o�[��
	static CSound SoundCharge;	//�[�d��
	static CSound SoundTimeUp;	//�^�C���A�b�v

	bool BatterySE;	//��x�����[�dSE�Đ�
	bool GameSE;	//��x�����Q�[���I�[�o�[�A�^�C���A�b�vSE�Đ�
};

#endif
