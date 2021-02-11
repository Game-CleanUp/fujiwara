#include"CHome.h"

int CHome::home = 0;

CHome::CHome(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(0.2f, 0.2f, 0.2f), 2.0f)
{
	mpModel = model; //���f���̐ݒ�
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�

	mColBody.mTag = CCollider::EHOME;
}

void CHome::TaskCollision()
{
	mColBody.ChangePriority();

	CCollisionManager::Get()->Collision(&mColBody);

}

void CHome::Collision(CCollider*m, CCollider*y){
	//�[�d
	if (y->mTag == CCollider::EBODY){
		if (CCollider::Collision(m, y)){
			home = true;
			}

		else{
			home = false;
		}
	}
}