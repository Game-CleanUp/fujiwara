#ifndef CENEMY_H
#define CENEMY_H
#include"CCharacter.h"
#include"CCollider.h"
#include "CVector.h"
#include"CSceneGame.h"
#include"CHome.h"

class CEnemy : public CCharacter{
public:
	//�f�t�H���g�R���X�g���N�^(�����̂Ȃ��R���X�g���N�^�j
	CEnemy(CModel*model, CVector position, CVector rotation, CVector scale);
	CCollider mColBody;

	//�Փ˔���
	void Collision(CCollider*m, CCollider*y);
	void Update();

	CHome *mpHome;

	int state;
	int frame;

};



#endif