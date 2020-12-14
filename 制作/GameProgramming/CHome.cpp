#include"CHome.h"

int CHome::home = 0;

CHome::CHome(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f, 1.0f, 1.0f), 10.0f)
{
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model; //���f���̐ݒ�
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�
}
//�ۑ�8
void CHome::Collision(CCollider*m, CCollider*y){
	//�[�d
	if (y->mTag == CCollider::EBODY){
		if (CCollider::Collision(m, y)){
			home = 1;
			}

		else{
			home = 0;
		}
	}
}