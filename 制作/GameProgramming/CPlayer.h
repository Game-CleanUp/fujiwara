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
#define DROP	rand() % 20 + 10	//�S�~�̃h���b�v�ʒu
#define DROP_DIR	rand() % 360	//�S�~�̃h���b�v����
#define FORWARD	0.3f	//�O�i
#define DIR		3.0f	//�����]��
#define BACK	-0.3f	//���
#define DASH	0.5f	//�_�b�V���X�s�[�h


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

	static CSound Sound;	//�W�����v��
	static CSound Sound2;	//������
	static CSound Sound3;	//�U����
	static CSound Sound4;	//�S�~���

	int frame;	//���ʎ���
	int frame2;	//���A����
	int frameMax;
	int state;

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