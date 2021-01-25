#ifndef CBOSS_H
#define CBOSS_H

#include"CPlayer.h"
#include"CCharacter.h"
#include"CCollider.h"
#include"CSound.h"
#include"math.h"
#include"CTrap.h"

#define TURN 13		//����
#define SPEED 0.3f	//�ړ����x
#define STATERAND	5	//�p�^�[��

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

    int tracking;
	int traptracking;
	
	float mVelocityJump;

	static CSound Sound;

	CMatrix matrix;
};


#endif