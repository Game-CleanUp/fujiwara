#ifndef CSPEED_H
#define CSPEED_H
#include"CCharacter.h"
#include"CCollider.h"
#include"CPlayer.h"


class CSpeed :public CCharacter{
public:
	//�f�t�H���g�R���X�g���N�^(�����̂Ȃ��R���X�g���N�^�j
	CSpeed(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;
	//�Փ˔���
	void Collision(CCollider*m, CCollider*y);
	static int speed;

};


#endif