#ifndef CPLAYER_H
#define CPLAYER_H
#include"CCharacter.h"
#include"CKey.h"
#include"CCollider.h"
#include"CInput.h"
#include"CPower.h"
#include"CHome.h"
#include"CPlayerHP.h"
#include"CBattery.h"
#include"CTime.h"
#include"CGaugeBack.h"
#include"CMoney.h"
#include"CSound.h"

#define G       9.8f/60.0f//�d�͉����x
#define JUMPV0  1.5f	//�W�����v����
#define R		7.0f	//���a
#define RETRY	60		//���A����
#define DROP	15.0f	//�S�~�̃h���b�v�ʒu
#define DROP_RAND	rand() % 360	//�S�~�̃h���b�v����

class CPlayer : public CCharacter{
public:
	
	void Update();
	void Render();
	void Init();
	void Collision(CCollider*m, CCollider*y);
	//�f�t�H���g�R���X�g���N�^
	CPlayer();
	CCollider mColBody;
	CCollider mSearch;
	static CPlayer *mpPlayer;
	static int mHPNow;
	static int mHPMax;
	static int clear;
	static int Dash;
	static int Jump;
	static int Down;

	int frame;
	int frame2;	//���A����
	int frameMax;
	int level;
	float mVelocityJump;

	CPlayerHP HP;
	CBattery Battery;
	CTime Time;
	CGaugeBack Back;
	CMatrix matrix;
	CSound Sound;

};



#endif