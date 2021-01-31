#include"CGomi.h"


int CGomi::GomiCount = 0;
CModel CGomi::mModel;

CSound CGomi::Sound;

CGomi::CGomi(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 1.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 3.0f)
{
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model; //���f���̐ݒ�
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�

	//���f���������Ƃ��͓ǂݍ���
	if (mModel.mTriangles.size() == 0)
	{
		mModel.Load("Rock1.obj", "Rock1.mtl");
	}
	//���f���̃|�C���^�ݒ�
	mpModel = &mModel;

	Sound.Load("gomi.wav");

}


void CGomi::TaskCollision()
{
	mColBody.ChangePriority();

	CCollisionManager::Get()->Collision(&mColBody);

}


void CGomi::Update(){

	mVelocityJump = JUMPV0;
	//�d�͉����x
	mVelocityJump -= 9.8f / 30.0f;
	//�ړ�
	mPosition.mY = mPosition.mY - mVelocityJump;

	CCharacter::Update();
}

void CGomi::Collision(CCollider*m, CCollider*y){


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

	//�S�~�ۗL������Ŗ���
	if (GomiCount < 5){
		//���肪�v���C���[
		if (y->mTag == CCollider::EBODY){
			if (CCollider::Collision(m, y)){
				//�Փ˂��Ă���Ƃ��͖����ɂ���
				mEnabled = false;
				Sound.Play();
				GomiCount += 1;
			}
		}
		//������(�v���C���[�̃T�[�`�ɓ���������)
		if (y->mTag == CCollider::ESEARCH){
			if (CCollider::Collision(m, y)){
				//�v���C���[�̕���
				CVector dir = y->mpParent->mPosition - mPosition;
				//���K���i������1�ɂ���jNormalize()
				mPosition = mPosition + dir.Normalize()*1.5;
				
			}
		}
	}
}
