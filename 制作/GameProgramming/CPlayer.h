#ifndef CPLAYER_H
#define CPLAYER_H
#include"CCharacter.h"
#include"CKey.h"
#include"CCollider.h"
#include"CHome.h"
#include"CBattery.h"
#include"CTime.h"
#include"CGaugeBack.h"
#include"CMoney.h"
#include"CSound.h"
#include"CBullet.h"
#include"CInput.h"
#include"CTrap.h"

#define G       9.8f/60.0f//�d�͉����x 9.8f
#define JUMPV0  2.0f	//�W�����v����
#define R		5.0f	//���a
#define RETRY	50		//���A����
#define DROP	rand() % 25 + 15	//�S�~�̃h���b�v�ʒu
#define DROP_RAND	rand() % 360	//�S�~�̃h���b�v����
#define FORWARD	0.5f	//�O�i
#define DIR		3.0f	//�����]��
#define BACK	-0.3f	//���



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

	//�N�����̃}�E�X�J�[�\���̍��W���o����
	int mMouseX;
	int mMouseY;

	float mVelocityJump;

	CBattery Battery;
	CTime Time;
	CGaugeBack Back;
	CMatrix matrix;

	static CSound Sound;

	static CSound Sound2;

	static CSound Sound3;	//������
};



#endif