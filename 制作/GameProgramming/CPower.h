#ifndef CPOWER_H
#define CPOWER_H
#include"CCharacter.h"
#include"CCollider.h"
#include"CPlayer.h"


class CPower :public CCharacter{
public:
	//�f�t�H���g�R���X�g���N�^(�����̂Ȃ��R���X�g���N�^�j
	CPower(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;
	//�Փ˔���
	void Collision(CCollider*m, CCollider*y);
	static int power;

};


#endif