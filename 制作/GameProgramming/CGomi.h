#ifndef CGOMI_H
#define CGOMI_H
#include"CCharacter.h"
#include"CCollider.h"
#include"CPlayer.h"


class CGomi : public CCharacter{
public:
	//�f�t�H���g�R���X�g���N�^(�����̂Ȃ��R���X�g���N�^�j
	CGomi(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;
	//�Փ˔���
	void Collision(CCollider*m, CCollider*y);
	static int GomiCount;
};



#endif