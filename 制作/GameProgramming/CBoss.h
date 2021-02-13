#ifndef CBOSS_H
#define CBOSS_H

#include"CPlayer.h"
#include"CCharacter.h"
#include"CCollider.h"
#include"CSound.h"
#include"math.h"
#include"CTrap.h"

#define TURN rand() % 5 + 1		//����
#define SPEED 0.3f	//�ړ����x
#define STATERAND	5	//�p�^�[��
#define STOP	rand() % 60 + 30	//��~����
#define TRACKSPEED	0.3	//�ǔ����x


class CBoss : public CCharacter{
public:
	//�f�t�H���g�R���X�g���N�^(�����̂Ȃ��R���X�g���N�^�j
	CBoss(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;
	CCollider mSearch;

	//�Փ˔���
	void Collision(CCollider*m, CCollider*y);
	void Update();
	void TaskCollision();

	int state;
	int ActFrame;	//�s������
	int EnemyDown; //�G�_�E������
	int DownFrame;	//�C�⎞��

	float mVelocityJump;

	bool onlyOnce;

	CSound SoundTrack;	//�ǔ���
	CSound SoundDamage;	//�_���[�W��

	CMatrix matrix;
};


#endif