#ifndef CBOSS_H
#define CBOSS_H

#include"CPlayer.h"
#include"CCharacter.h"
#include"CCollider.h"
#include"CSound.h"
#include"math.h"
#include"CTrap.h"
#include"CScene.h"

#define TURN rand() % 5 + 1		//����
#define SPEED 0.3f	//�ړ����x
#define STATERAND	4	//�p�^�[��
#define STOPTIME	rand() % 60 + 30	//��~����
#define TRACKSPEED	0.3	//�ǔ����x
#define DAMAGETIME	180	//�_���[�W����


class CBoss : public CCharacter{
public:

	enum STATE
	{
		Move_Stop,
		Move_Left,
		Move_Right,
		Move_Gomi,
		Move_TrapTracking,
		Move_PlayerTracking,
		Move_Damage,

	};

	//�f�t�H���g�R���X�g���N�^(�����̂Ȃ��R���X�g���N�^�j
	CBoss(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;
	CCollider mSearch;

	//�Փ˔���
	void Collision(CCollider*m, CCollider*y);
	void Update();
	void TaskCollision();
	void Render();

    int state;
	int ActFrame;	//�s������

	float mVelocityJump;

	bool onlyOnce;

	CSound SoundTrack;	//�ǔ���
	CSound SoundDamage;	//�_���[�W��

	CMatrix matrix;
};


#endif