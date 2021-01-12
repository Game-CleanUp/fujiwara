#ifndef CPLAYER_H
#define CPLAYER_H
#include"CCharacter.h"
#include"CKey.h"
#include"CCollider.h"
#include"CHome.h"
#include"CBattery.h"
#include"CLevel.h"
#include"CTime.h"
#include"CGaugeBack.h"
#include"CMoney.h"
#include"CSound.h"
#include"CBullet.h"

#define G       9.8f/60.0f//�d�͉����x 9.8f
#define JUMPV0  2.5f	//�W�����v����
#define R		5.0f	//���a
#define RETRY	50		//���A����
#define DROP	14.0f	//�S�~�̃h���b�v�ʒu
#define DROP_RAND	rand() % 360	//�S�~�̃h���b�v����
#define FORWARD	0.7f	//�O�i
#define DASH	1.0f	//�_�b�V��
#define DIR		5.0f	//�����]��
#define BACK	-1.0f	//���



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
	static int clear;
	static int Down;

	int frame;	//���ʎ���
	int frame2;	//���A����
	int frameMax;
	static int levelNow;
	static int levelMax;
	static int PlayerLevel;
	float mVelocityJump;

	CBattery Battery;
	CTime Time;
	CLevel Level;
	CGaugeBack Back;
	CMatrix matrix;

	static CSound Sound;

	static CSound Sound2;

	static CSound Sound3;	//������
};



#endif