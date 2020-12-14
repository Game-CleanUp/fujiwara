#ifndef COUT_H
#define COUT_H

#include"CCharacter.h"
#include"CCollider.h"

class COut :public CCharacter{
public:
	//コライダの追加
	CCollider*mpCollider;
	//コンストラクタで初期設定
	COut(CModel*model, const CVector &position, const CVector &rotation, const CVector &scale);
	~COut();

};


#endif