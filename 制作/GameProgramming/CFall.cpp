#include"CFall.h"


int FallLife = 0;

//�ۑ�7
CFall::CFall(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 0.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f, 1.0f, 1.0f), 5.0f)
{
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model; //���f���̐ݒ�
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�
}
//�ۑ�8
void CFall::Collision(CCollider*m, CCollider*y){
	
	//���g�̃R���C�_�^�C�v�̔���
	switch (m->mType){
	case CCollider::ESPHERE://���R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (y->mType == CCollider::ETRIANGLE){
			CVector adjust;//�����l�x�N�g��
			//�O�p�`�Ƌ��̏Փ˔���
			if (CCollider::CollisionTriangleSphere(y, m, &adjust)){

				//���˕���
				//mForward = CVector(0.0f, 3.0f, 0.0f);
				if (rand() % 3 - 1 >= 0){
					mForward = CVector(0.5f, 5.0f, 0.0f);
				}
				else{
					mForward = CVector(-0.5f, 5.0f, 0.0f);
				}
			}
			//�ʒu�̍X�V
			mPosition = mPosition - adjust*-1;

			//�s��̍X�V
			CCharacter::Update();
		}
		break;

		if (y->mType == CCollider::ETRIANGLE){
			if (CCollider::Collision(y, m)){
				mForward.mY += 0.5;
			}
		}
	}
	//�v���C���[�Ƃ̏Փ˔���
	if (m->mType == CCollider::ESPHERE && y->mType == CCollider::ESPHERE){
		if (y->mpParent->mTag == CCharacter::EPLAYER){
			if (CCollider::Collision(m, y)){
				mEnabled = false;
				
			}
		}
	}
}
void CFall::Update(){
	//�������x
	mForward.mY -= G;
	mPosition = mPosition + mForward;
}