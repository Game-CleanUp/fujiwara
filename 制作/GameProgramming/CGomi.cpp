#include"CGomi.h"

int CGomi::GomiCount = 0;

//�ۑ�7
CGomi::CGomi(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f, 1.0f, 1.0f), 1.0f)
{
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model; //���f���̐ݒ�
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�
}

//�ۑ�8
void CGomi::Collision(CCollider*m, CCollider*y){

	if (GomiCount < 5){
		//���肪�v���C���[
		if (y->mTag == CCollider::EBODY){
			//�Փ�
			if (CCollider::Collision(m, y)){
				//�Փ˂��Ă���Ƃ��͖����ɂ���
				mEnabled = false;
				GomiCount += 1;
			}
		}
		//������(�v���C���[�̃T�[�`�ɓ���������)
		if (y->mTag == CCollider::ESEARCH){
			if (CCollider::Collision(m, y)){
				//�v���C���[�̕���
				CVector dir = y->mpParent->mPosition - mPosition;
				//���K���i������1�ɂ���jNormalize()
				mPosition = mPosition + dir.Normalize()*1.0;
			}
		}
	}
}