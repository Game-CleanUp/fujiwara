#ifndef CPLAYER_H
#define CPLAYER_H
#include"CCharacter.h"
#include"CKey.h"
#include"CCollider.h"
#include"CHome.h"
#include"CBattery.h"
#include"CTime.h"
#include"CUi.h"
#include"CSound.h"
#include"CBullet.h"
#include"CTrap.h"
#include"CText.h"

#define G       9.8f/60.0f//�d�͉����x 9.8f
#define JUMPV0  2.0f	//�W�����v����
#define R		5.0f	//���a
#define RETRY	80		//���A����
#define DROP	13	//�S�~�̃h���b�v�ʒu
#define DROP_DIR	rand() % 360	//�S�~�̃h���b�v����
#define FORWARD	0.6f	//�O�i
#define DIR		7.0f	//�����]��
#define BACK	-0.6f	//���
#define DASH	0.8f	//�_�b�V���X�s�[�h
#define TIMEADD	5*60	//�^�C�����Z

class CPlayer : public CCharacter{
public:
	
	void Update();
	void Render();
	void Init();
	void Collision(CCollider*m, CCollider*y);
	void TaskCollision();
	//�f�t�H���g�R���X�g���N�^
	CPlayer();
	CCollider mColBody;
	CCollider mSearch;
	static CPlayer *mpPlayer;
	static int Score;
	static int Down;

	static CSound SoundJump;	//�W�����v��
	static CSound SoundBomb;	//������
	static CSound SoundAttack;	//�U����
	static CSound SoundThrow;	//�S�~���

	int frameRetry;	//���A����

	float mVelocityJump;

	bool onlyOnce;

	CBattery Battery;
	CTime Time;
	CGaugeBack Back;
	CMatrix matrix;
	CTrapUI TrapUi;
	CGomiUI GomiUI;

};



#endif