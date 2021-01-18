#ifndef CBLOCK_H
#define CBLOCK_H
#include"CCharacter.h"
#include"CCollider.h"
#include"CPlayer.h"


class CBlock : public CCharacter{
public:
	//�f�t�H���g�R���X�g���N�^(�����̂Ȃ��R���X�g���N�^�j
	CBlock(CModel*model, CVector position, CVector rotation, CVector scale);

	CCollider mColBody;
	CCollider *mpCollider;

	//�Փ˔���
	void Collision(CCollider*m, CCollider*y);
	void TaskCollision();
	void Update();

	float mVelocityJump;

	int BlockTriangle;	//�O�p�`�̐�
};

#endif