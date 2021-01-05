#ifndef CHOME_H
#define CHOME_H

#include"CCharacter.h"
#include"CCollider.h"
#include"CGomi.h"
#include "CCollisionManager.h"

class CHome : public CCharacter{
public:
	//�f�t�H���g�R���X�g���N�^(�����̂Ȃ��R���X�g���N�^�j
	CHome(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;
	//�Փ˔���
	void Collision(CCollider*m, CCollider*y);
	void TaskCollision();
	static int home;
};



#endif