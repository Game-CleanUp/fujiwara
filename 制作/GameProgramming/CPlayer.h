#ifndef CPLAYER_H
#define CPLAYER_H
#include"CCharacter.h"
#include"CKey.h"
#include"CCollider.h"
#include"CInput.h"
#include"CPower.h"
#include"CHome.h"
#include"CPlayerHP.h"
#include"CGaugeBack.h"
#include"CMoney.h"

#define G       9.8f/60.0f//�d�͉����x
#define JUMPV0  1.5f	//�W�����v����
#define R		7.0f	//���a
#define RETRY	180		//���A����

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
	static int Life;
	static int clear;
	static int Dash;
	static int Jump;


	int frame;
	int frameMax;
	int level;
	float mVelocityJump;

	CPlayerHP HP;
	CGaugeBack Back;
	CMatrix matrix;

};



#endif