#ifndef CENEMY2_H
#define CENEMY2_H
#include"CCharacter.h"
#include"CCollider.h"
#include"CPlayer.h"


class CEnemy2 : public CCharacter{
public:
	//�f�t�H���g�R���X�g���N�^(�����̂Ȃ��R���X�g���N�^�j
	CEnemy2(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;
	//�Փ˔���
	void Collision(CCollider*m, CCollider*y);
	void TaskCollision();
};


#endif