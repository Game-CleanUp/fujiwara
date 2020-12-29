#include"CEnemy2.h"


//�ۑ�7
CEnemy2::CEnemy2(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f, 1.0f, 1.0f), 1.0f)
{
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model; //���f���̐ݒ�
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�
}

//�ۑ�8
void CEnemy2::Collision(CCollider*m, CCollider*y){

	//���肪�v���C���[
	if (y->mTag == CCollider::EBODY){
		//�Փ�
		if (CCollider::Collision(m, y)){
			//�Փ˂��Ă���Ƃ��͖����ɂ���
			mEnabled = false;
		}
	}
	//������
	if (y->mTag == CCollider::ESEARCH){
		if (CCollider::Collision(m, y)){
			//�v���C���[�̕���
			CVector dir = y->mpParent->mPosition - mPosition;
			//���K���i������1�ɂ���jNormalize()
			mPosition = mPosition + dir.Normalize()*0.5;
		}
	}
}

