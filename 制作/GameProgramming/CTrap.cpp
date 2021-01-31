#include"CTrap.h"


int CTrap::TrapCount = 10;
CTrap *CTrap::mpTrap = 0;
CModel CTrap::mModel;

CSound CTrap::Sound;

CTrap::CTrap(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 5.0f)
, trapframe(0)
{
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model; //���f���̐ݒ�
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�

	//���f���������Ƃ��͓ǂݍ���
	if (mModel.mTriangles.size() == 0)
	{
		mModel.Load("sphere.obj", "sphere.mtl");
	}
	//���f���̃|�C���^�ݒ�
	mpModel = &mModel;

	mColBody.mTag = CCollider::ETRAP;

	mpTrap = this;
}


void CTrap::TaskCollision()
{
	mColBody.ChangePriority();

	CCollisionManager::Get()->Collision(&mColBody);

}


void CTrap::Update(){

	mVelocityJump = JUMPV0;
	//�d�͉����x
	mVelocityJump -= G;
	//�ړ�
	mPosition.mY = mPosition.mY - mVelocityJump;

	CCharacter::Update();
}

void CTrap::Collision(CCollider*m, CCollider*y){


	//���g�̃R���C�_�^�C�v�̔���
	switch (m->mType){
	case CCollider::ESPHERE://���R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (y->mType == CCollider::ETRIANGLE){
			CVector adjust;//�����l�x�N�g��
			//�O�p�`�Ƌ��̏Փ˔���
			if (CCollider::CollisionTriangleSphere(y, m, &adjust)){
				//���n
				mVelocityJump = 0;

			}

			//�ʒu�̍X�V
			mPosition = mPosition - adjust*-1;

			//�s��̍X�V
			CCharacter::Update();
		}

		break;
	}

	//���肪CBoss(���ƏՓ�)
	if (y->mTag == CCollider::EBODY2){
		if (CCollider::Collision(m, y)){
			trapframe++;	//��~���ԃJ�E���g
		}
		//1�b�����
		if (trapframe > 60){
			mEnabled = false;
		}
	}
}