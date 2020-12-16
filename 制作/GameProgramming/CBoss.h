#ifndef CBOSS_H
#define CBOSS_H

#include"CPlayer.h"
#include"CCharacter.h"
#include"CCollider.h"

class CBoss : public CCharacter{
public:
	//�f�t�H���g�R���X�g���N�^(�����̂Ȃ��R���X�g���N�^�j
	CBoss(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;
	CCollider mSearch;
	//�Փ˔���
	void Collision(CCollider*m, CCollider*y);
	void Update();

	int state;
	int frame;

	float mVelocityJump;

};


#endif