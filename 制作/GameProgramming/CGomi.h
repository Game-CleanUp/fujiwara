#ifndef CGOMI_H
#define CGOMI_H
#include"CCharacter.h"
#include"CCollider.h"
#include"CPlayer.h"
#include"CSound.h"
#include "CCollisionManager.h"

#define ATTRACT	1.5	//�����񂹂鑬�x

class CGomi : public CCharacter{
public:

	//�f�t�H���g�R���X�g���N�^(�����̂Ȃ��R���X�g���N�^�j
	CGomi(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;

	void Update();
	//�Փ˔���
	void Collision(CCollider*m, CCollider*y);
	void TaskCollision();

	static int GomiCount;	//�S�~������
	static CModel mModel;
	static CSound Sound;
	static int StageGomi;	//�X�e�[�W�ɂ���S�~�̐�

	float mVelocityJump;

};



#endif