#include"CBlock.h"

CBlock::CBlock(CModel*model, CVector position, CVector rotation, CVector scale)
:mColBody(this, CVector(0.0f, 2.0f, 0.0f), CVector(0.0f, 0.0f, 0.0f), CVector(1.0f, 1.0f, 1.0f), 5.0f)
{
	//���f���A�ʒu�A��]�A�g�k��ݒ肷��
	mpModel = model; //���f���̐ݒ�
	mPosition = position; //�ʒu�̐ݒ�
	mRotation = rotation; //��]�̐ݒ�
	mScale = scale; //�g�k�̐ݒ�

	//���f���̎O�p�`�̐����A�R���C�_�̔z����쐬����
	mpCollider = new CCollider[model->mTriangles.size()];

	//���f���̎O�p�`�̐����A�R���C�_�̔z����쐬����
	BlockTriangle = model->mTriangles.size();
	for (int i = 0; i < model->mTriangles.size(); i++){
		//�R���C�_���O�p�`�R���C�_�Őݒ肵�Ă���
		mpCollider[i].SetTriangle(this,
			model->mTriangles[i].mV[0],
			model->mTriangles[i].mV[1],
			model->mTriangles[i].mV[2]);
		mpCollider[i].ChangePriority();
	}

	mColBody.mTag = CCollider::EBLOCK;
}

void CBlock::TaskCollision()
{
	mColBody.ChangePriority();
	for (int i = 0; i < BlockTriangle; i++){
		mpCollider[i].ChangePriority();
	}
	CCollisionManager::Get()->Collision(&mColBody);

}

void CBlock::Update(){
	
	//mVelocityJump = JUMPV0;
	////�d�͉����x
	//mVelocityJump -= G;
	////�ړ�
	//mPosition.mY = mPosition.mY - mVelocityJump;

	//CCharacter::Update();
}

void CBlock::Collision(CCollider*m, CCollider*y){

	if (y->mTag == CCollider::EBULLET){
		if (CCollider::Collision(m, y)){
			//�v���C���[�e�̕���
			CVector dir = y->mpParent->mPosition - mPosition;
			//���K���i������1�ɂ���jNormalize()
			mPosition = mPosition + dir.Normalize()*1.0;
		}
	}

	switch (m->mType){
	case CCollider::ESPHERE://���R���C�_
		//����̃R���C�_���O�p�R���C�_�̎�
		if (y->mType == CCollider::ETRIANGLE){
			CVector adjust;//�����l�x�N�g��
			//�O�p�`�Ƌ��̏Փ˔���
			if (CCollider::CollisionTriangleSphere(y, m, &adjust)){
				//���n
				//mVelocityJump = 0;
			}

			//�ʒu�̍X�V
			mPosition = mPosition - adjust*-1;

			//�s��̍X�V
			CCharacter::Update();
		}

		break;
	}
}