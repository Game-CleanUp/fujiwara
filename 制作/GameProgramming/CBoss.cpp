#include"CBoss.h"


CBoss::CBoss(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f),
CVector(1.0f, 1.0f, 1.0f), 4.0f)
{
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model; //���f���̐ݒ�
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�
}


void CBoss::Update(){
	//�ʒu���ړ�
	//CVector dir = CPlayer::mpPlayer->mPosition - mPosition;
	/*CVector left = CVector(1.0f, 0.0f, 0.0f)  * CMatrix().RotateY(mRotation.mY);
	CVector right = CVector(-1.0f, 0.0f, 0.0f) * CMatrix().RotateY(mRotation.mY);
	if (left.Dot(dir) > 0.0f){
		mRotation.mY += 1.0f;
	}
	else if (left.Dot(dir) < 0.0f){
		mRotation.mY -= 1.0f;
	}
*/
	mPosition = CVector(0.0f, 1.0f, 0.0f);

	//�s����X�V
	CCharacter::Update();

}



void CBoss::Collision(CCollider*m, CCollider*y){

	//���g�̃R���C�_�^�C�v�̔���
	switch (m->mType){
	case CCollider::ESPHERE://���R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (y->mType == CCollider::ETRIANGLE){
			CVector adjust;//�����l�x�N�g��
			//�O�p�`�Ƌ��̏Փ˔���
			if (CCollider::CollisionTriangleSphere(y, m, &adjust)){

			}
			//�ʒu�̍X�V
			mPosition = mPosition - adjust*-1;

			//�s��̍X�V
			CCharacter::Update();
		}
		break;
	}

	//�v���C���[�Ƃ̏Փ˔���
	if (y->mTag == CCollider::EBODY){
		if (CCollider::Collision(m, y)){
			mEnabled = false;
		}
	}

	////������
	//if (y->mTag == CCollider::ESEARCH){
	//	if (CCollider::Collision(m, y)){
	//		//�v���C���[�̕���
	//		CVector dir = y->mpParent->mPosition - mPosition;
	//		//���K���i������1�ɂ���jNormalize()
	//		mPosition = mPosition + dir.Normalize()*1.5;
	//	}
	//}
}