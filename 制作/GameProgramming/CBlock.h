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
	//�Փ˔���
	void Collision(CCollider*m, CCollider*y);
	void TaskCollision();
	void Update();

	float mVelocityJump;
};

#endif

//#include"CCharacter.h"
//#include"CCollider.h"
//
//class CBlock :public CCharacter{
//public:
//	//�R���C�_�̒ǉ�
//	CCollider*mpCollider;
//	//�R���X�g���N�^�ŏ����ݒ�
//	CBlock(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale);
//	~CBlock();
//};
//
//
//#endif