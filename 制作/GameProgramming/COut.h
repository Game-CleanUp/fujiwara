#ifndef COUT_H
#define COUT_H

#include"CCharacter.h"
#include"CCollider.h"

class COut :public CCharacter{
public:
	//�R���C�_�̒ǉ�
	CCollider*mpCollider;
	//�R���X�g���N�^�ŏ����ݒ�
	COut(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale);
	~COut();

};


#endif