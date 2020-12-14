#ifndef CFALL_H
#define CFALL_H
#include"CCharacter.h"
#include"CCollider.h"
#include "CVector.h"

#define G       (9.8f/60.0f)//�d�͉����x

class CFall : public CCharacter{
public:
	//�f�t�H���g�R���X�g���N�^(�����̂Ȃ��R���X�g���N�^�j
	CFall(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;
	
	//�Փ˔���
	void Collision(CCollider*m, CCollider*y);
	void Update();
	float mVelocityJump;
	CVector mForward;

};



#endif