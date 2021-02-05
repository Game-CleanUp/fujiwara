#ifndef CTRAP_H
#define CTRAP_H
#include"CCharacter.h"
#include"CCollider.h"
#include"CPlayer.h"
#include"CSound.h"
#include "CCollisionManager.h"

#define INIT_TRAP	10	//�����g���b�v������

class CTrap : public CCharacter{
public:

	//�f�t�H���g�R���X�g���N�^(�����̂Ȃ��R���X�g���N�^�j
	CTrap(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;

	void Update();
	//�Փ˔���
	void Collision(CCollider*m, CCollider*y);
	void TaskCollision();

	int trapframe;

	static int TrapCount;	//㩂������Ă��鐔
	static CModel mModel;
	static CSound Sound;
	static CTrap *mpTrap;	//�g���b�v�̃|�C���^

	float mVelocityJump;

};



#endif